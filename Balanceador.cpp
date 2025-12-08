#include "balanceador.h"
#include <algorithm>
#include <iomanip> // NECESARIO para fixed, setprecision

/* ======================= Constructores ======================= */

Balanceador::Balanceador() {
    // La matriz se inicializa vacía
}

/* ----------------------- Métodos Auxiliares Matemáticos ----------------------- */

// Calcula el Máximo Común Divisor (MCD)
int Balanceador::calcularMCD(int a, int b) const {
    // Usamos el algoritmo de Euclides
    return std::abs(std::gcd(a, b));
}

// Calcula el Mínimo Común Múltiplo (MCM)
int Balanceador::calcularMCM(int a, int b) const {
    if (a == 0 || b == 0) return 0;
    return std::abs(a * b) / calcularMCD(a, b);
}

/* ----------------------- Métodos Privados de Proceso ----------------------- */

// 1. Construye la matriz de coeficientes
void Balanceador::construirMatriz(Reaccion* reaccion) {
    matrizBalanceo.clear();

    if (!reaccion) return;

    // 1. Obtener lista ÚNICA de elementos y de términos
    vector<string> elementos = reaccion->getElementosParticipantes();
    size_t numElementos = elementos.size();
    
    vector<TerminoReaccion> terminos;
    for (const auto& r : reaccion->getReactivos()) terminos.push_back(r);
    for (const auto& p : reaccion->getProductos()) terminos.push_back(p);
    
    size_t numTerminos = terminos.size(); // Número de incógnitas (coeficientes)
    
    // La matriz será de tamaño: numElementos x numTerminos (A X = 0)
    matrizBalanceo.resize(numElementos, vector<float>(numTerminos, 0.0f));

    // 2. Llenar la matriz
    for (size_t i = 0; i < numElementos; ++i) { // Filas: Elementos (Ecuaciones)
        string simbolo = elementos[i];
        
        for (size_t j = 0; j < numTerminos; ++j) { // Columnas: Términos (Incógnitas)
            Formula* formula = terminos[j].first;
            
            // Cantidad del elemento en la fórmula
            map<string, int> elementosUnicos = formula->getElementosUnicos();
            int cantidadAtomos = elementosUnicos.count(simbolo) ? elementosUnicos.at(simbolo) : 0;
            
            // En el balanceo algebraico, los productos se pasan al otro lado del igual, 
            // por lo que tienen signo negativo.
            if (j >= reaccion->getReactivos().size()) {
                // Producto: coeficiente negativo
                matrizBalanceo[i][j] = -static_cast<float>(cantidadAtomos); 
            } else {
                // Reactivo: coeficiente positivo
                matrizBalanceo[i][j] = static_cast<float>(cantidadAtomos);
            }
        }
    }
}

// 2. Resuelve el sistema matricial (Eliminación Gaussiana Simplificada)
vector<int> Balanceador::resolverSistemaMatricial(Reaccion* reaccion) {
    
    // Copia de la matriz para trabajar (para no modificar la matrizBalanceo original)
    vector<vector<float>> M = matrizBalanceo;
    size_t numFilas = M.size(); // Número de elementos (ecuaciones)
    size_t numCols = M[0].size(); // Número de términos (incógnitas)
    
    if (numCols <= numFilas) {
        // El sistema es cuadrado o tiene más ecuaciones que incógnitas (caso raro o sin solución única no trivial).
        // Para este nivel, forzamos que haya al menos una variable libre, asignando la última como tal.
        // Si hay más elementos que términos, el balanceo es imposible o el sistema está mal planteado.
        cout << "Error: Sistema de ecuaciones no tiene variable libre o es inconsistente.\n";
        return vector<int>(numCols, 1); // Solución trivial
    }
    
    // 1. ELIMINACIÓN GAUSSIANA SIMPLIFICADA (Triangulación)
    int pivotRow = 0;
    for (size_t j = 0; j < numCols; ++j) { // Columna
        if (pivotRow >= numFilas) break;

        // Buscar el pivote (el primer elemento no cero en la columna)
        size_t i_max = pivotRow;
        for (size_t i = pivotRow + 1; i < numFilas; ++i) {
            if (std::abs(M[i][j]) > std::abs(M[i_max][j])) i_max = i;
        }

        // Si se encuentra un pivote, intercambiar filas
        if (M[i_max][j] != 0) {
            std::swap(M[pivotRow], M[i_max]);

            // Normalizar el pivote a 1 (aunque no es estrictamente necesario, ayuda)
            float pivot = M[pivotRow][j];
            for (size_t k = j; k < numCols; ++k) {
                M[pivotRow][k] /= pivot;
            }

            // Eliminar otras filas
            for (size_t i = 0; i < numFilas; ++i) {
                if (i != pivotRow) {
                    float factor = M[i][j];
                    for (size_t k = j; k < numCols; ++k) {
                        M[i][k] -= factor * M[pivotRow][k];
                    }
                }
            }
            pivotRow++;
        }
    }

    // 2. SUSTITUCIÓN REGRESIVA Y ASIGNACIÓN DE VARIABLE LIBRE
    
    // Siempre hay una variable libre: asignamos la última incógnita (x_n) el valor 1 para obtener fracciones.
    vector<float> solucionFraccionaria(numCols);
    solucionFraccionaria[numCols - 1] = 1.0f; // Asignamos x_n = 1 (variable libre)

    // Iteramos hacia atrás sobre las filas (ecuaciones)
    for (int i = numFilas - 1; i >= 0; --i) {
        float suma = 0.0f;
        int pivot_col = -1;

        // Encontrar la columna pivote (primer elemento no cero) en esta fila
        for (size_t j = 0; j < numCols; ++j) {
            if (std::abs(M[i][j]) > 1e-6) { // Usar tolerancia para flotantes
                pivot_col = j;
                break;
            }
        }

        if (pivot_col != -1 && pivot_col < (int)numCols - 1) { // No resolver si es la variable libre
            for (size_t j = pivot_col + 1; j < numCols; ++j) {
                suma += M[i][j] * solucionFraccionaria[j];
            }
            // La matriz ya fue normalizada a 1.0 en el pivote, por lo que: x_pivot = -suma
            // (La matriz representa la ecuación: 1*x_pivot + M[i, j]*x_j + ... = 0)
            solucionFraccionaria[pivot_col] = -suma; 
        }
    }
    
    // 3. CONVERSIÓN A ENTEROS MÁS PEQUEÑOS
    return simplificarASolucionEntera(solucionFraccionaria);
}

// Simplifica los coeficientes fraccionarios a la solución entera más pequeña
vector<int> Balanceador::simplificarASolucionEntera(const vector<float>& coeficientesFraccionarios) const {
    vector<int> solucionEntera;
    int denominadorComun = 1;
    
    // 1. Encontrar el Mínimo Común Múltiplo (MCM) de los denominadores (implícitamente)
    for (float c : coeficientesFraccionarios) {
        // Solo procesamos coeficientes positivos y no cero
        if (c > 1e-6) {
            // Convertir el float a una fracción (aproximadamente)
            // Multiplicamos por un factor grande (ej. 1000) y encontramos el MCD
            // Esta aproximación es necesaria debido a la imprecisión de los flotantes.
            int num = static_cast<int>(std::round(c * 1000.0f));
            int den = 1000;
            
            // Simplificar la fracción
            int divisor = calcularMCD(num, den);
            den /= divisor;
            
            // Actualizar el denominador común (MCM de todos los denominadores)
            denominadorComun = calcularMCM(denominadorComun, den);
        }
    }

    // Si el denominador común es 0 o 1, lo dejamos en 1.
    if (denominadorComun == 0) denominadorComun = 1;

    // 2. Multiplicar todos los coeficientes por el MCM para obtener enteros
    for (float c : coeficientesFraccionarios) {
        int coeficiente = static_cast<int>(std::round(c * (float)denominadorComun));
        
        // El coeficiente debe ser positivo (ajustamos el signo si es necesario, aunque no debería ser negativo)
        solucionEntera.push_back(std::abs(coeficiente)); 
    }
    
    // 3. Simplificar la solución entera final (dividir por el MCD de todos los resultados)
    int mcdFinal = 0;
    for (int c : solucionEntera) {
        if (c > 0) {
            mcdFinal = (mcdFinal == 0) ? c : calcularMCD(mcdFinal, c);
        }
    }
    
    if (mcdFinal > 1) {
        for (int& c : solucionEntera) {
            c /= mcdFinal;
        }
    }
    
    return solucionEntera;
}


// 3. Asigna los coeficientes enteros resueltos a la Reaccion
void Balanceador::asignarCoeficientes(Reaccion* reaccion, const vector<int>& coeficientes) {
    if (reaccion == nullptr) return;
    
    size_t numReactivos = reaccion->getReactivos().size();
    size_t numProductos = reaccion->getProductos().size();

    // Asignar a Reactivos
    for (size_t i = 0; i < numReactivos; ++i) {
        if (i < coeficientes.size()) {
            reaccion->setCoeficienteReactivo(i, coeficientes[i]); 
        }
    }

    // Asignar a Productos
    size_t offset = numReactivos;
    for (size_t j = 0; j < numProductos; ++j) {
        if (offset + j < coeficientes.size()) {
            reaccion->setCoeficienteProducto(j, coeficientes[offset + j]);
        }
    }
}


/* ----------------------- Métodos de Servicio ----------------------- */

bool Balanceador::balancear(Reaccion* reaccion) {
    if (reaccion == nullptr) return false;

    // 1. Construir la matriz de átomos
    construirMatriz(reaccion);

    // 2. Resolver el sistema para obtener coeficientes enteros
    vector<int> coeficientes = resolverSistemaMatricial(reaccion);

    // 3. Asignar los coeficientes a la Reacción
    asignarCoeficientes(reaccion, coeficientes);

    // 4. Verificar Balanceo Riguroso
    bool esBalanceada = true;
    vector<string> elementos = reaccion->getElementosParticipantes();
    
    cout << "\n--- Verificacion de Balanceo ---\n";
    for (const string& simbolo : elementos) {
        int atomosR = reaccion->getTotalAtomosReactivo(simbolo);
        int atomosP = reaccion->getTotalAtomosProducto(simbolo);
        
        cout << simbolo << " | Reactivos: " << atomosR << " | Productos: " << atomosP << endl;
        
        if (atomosR != atomosP) {
            esBalanceada = false;
        }
    }
    
    // 5. Establecer el estado final y devolver la reacción completa (mediante mostrarReaccion)
    reaccion->setBalanceada(esBalanceada);
    
    // Requisito extra: regresar la reacción completa con los nuevos coeficientes
    reaccion->mostrarReaccion(); 

    return esBalanceada;
}

/* ----------------------- Getters  ----------------------- */

// Muestra la matriz de coeficientes (para depuración)
void Balanceador::mostrarMatriz() const {
    cout << "\n--- Matriz de Coeficientes (Algebraico) ---\n";
    for (const auto& fila : matrizBalanceo) {
        for (float val : fila) {
            // Muestra con dos decimales para flotantes
            cout.width(8); 
            cout << fixed << setprecision(2) << val << " ";
        }
        cout << endl;
    }
    cout << "------------------------------------------\n";
}
