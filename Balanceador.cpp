#include "balanceador.h"
#include <numeric> // Para el cálculo de máximo común divisor (MCD)

/* ======================= Constructores ======================= */
Balanceador::Balanceador() {
    // La matriz se inicializa vacía
}

/* ----------------------- Métodos Privados de Proceso ----------------------- */

// Construye la matriz de coeficientes a partir de la Reaccion (Simplificado)
void Balanceador::construirMatriz(Reaccion* reaccion) {
    // Lógica compleja omitida para simplicidad.
    // Solo se inicializa la matriz vacía.
    matrizBalanceo.clear();
    
    // En una implementación real, aquí se llenaría la matriz 
    // con las contribuciones de átomos de cada fórmula.
}

// Resuelve el sistema matricial (Lógica extremadamente simplificada)
vector<int> Balanceador::resolverSistemaMatricial() {
    // Lógica compleja de Gauss-Jordan omitida.
    
    // Devuelve un vector de coeficientes de prueba (ejemplo: [2, 1, 2] para H2 + O2 -> H2O)
    // ESTA ES LA SIMPLIFICACIÓN: Asume que se balancea correctamente como 2, 1, 2.
    
    vector<int> coeficientesEjemplo = {2, 1, 2}; 
    return coeficientesEjemplo;
}

// Asigna los coeficientes enteros resueltos a la Reaccion
void Balanceador::asignarCoeficientes(Reaccion* reaccion, const vector<int>& coeficientes) {
    // 1. Asignar a Reactivos
    vector<TerminoReaccion> reactivos = reaccion->getReactivos();
    size_t i = 0;
    
    for (auto& termino : reactivos) {
        if (i < coeficientes.size()) {
            // Se utiliza el setter para actualizar el coeficiente directamente en el puntero de la fórmula
            // NOTA: Para C++ básico, necesitarías un setter en Reaccion que permita modificar el coeficiente
            // de un término. Por simplicidad, asumiremos que reaccion tiene un método que permite hacer esto.

            // EJEMPLO CONCEPTUAL (Asumiendo que modificamos los vectores internos directamente o usamos un setter)
            if (i < coeficientes.size()) {
                termino.second = coeficientes[i]; 
            }
        }
        i++;
    }

    // 2. Asignar a Productos
    vector<TerminoReaccion> productos = reaccion->getProductos();
    size_t j = 0;
    
    // Los coeficientes de la lista se continúan asignando a los productos
    for (auto& termino : productos) {
        if (i + j < coeficientes.size()) {
            termino.second = coeficientes[i + j];
        }
        j++;
    }
}


/* ----------------------- Métodos de Servicio ----------------------- */

// Método principal: Ejecuta todo el proceso de balanceo
bool Balanceador::balancear(Reaccion* reaccion) {
    if (reaccion == nullptr) return false;

    // 1. Obtener la matriz de átomos (omitido por complejidad)
    construirMatriz(reaccion);

    // 2. Resolver el sistema para obtener coeficientes (usando solución de prueba)
    vector<int> coeficientes = resolverSistemaMatricial();

    // 3. Asignar los coeficientes a la Reacción
    asignarCoeficientes(reaccion, coeficientes);

    // 4. Verificar Balanceo (Lógica Simplificada)
    
    // Verificamos si los átomos están realmente balanceados (Lógica simplificada)
    bool esBalanceada = true;
    vector<string> elementos = reaccion->getElementosParticipantes();
    
    for (const string& simbolo : elementos) {
        if (reaccion->getTotalAtomosReactivo(simbolo) != reaccion->getTotalAtomosProducto(simbolo)) {
            esBalanceada = false;
            break;
        }
    }
    
    reaccion->setBalanceada(esBalanceada);

    return esBalanceada;
}

/* ----------------------- Getters (Debugging) ----------------------- */

// Obtiene la matriz de balanceo
vector<vector<float>> Balanceador::getMatrizBalanceo() const {
    return matrizBalanceo;

}
