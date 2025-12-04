#include "reaccion.h"

/* ======================= Constructores ======================= */

// Constructor por defecto
Reaccion::Reaccion() {
    nombre = "";
    balanceada = false;
}

// Constructor con parámetros
Reaccion::Reaccion(string n) {
    nombre = n;
    balanceada = false;
}

/* ----------------------- Setters ----------------------- */
void Reaccion::setNombre(string n) {
    nombre = n;
}

// Establece el estado de balanceo
void Reaccion::setBalanceada(bool b) {
    balanceada = b;
}

// Agrega un término al lado de los reactivos
void Reaccion::agregarReactivo(Formula* formula, int coeficiente) {
    if (formula != nullptr && coeficiente >= 0) {
        reactivos.push_back(make_pair(formula, coeficiente));
    }
}

// Agrega un término al lado de los productos
void Reaccion::agregarProducto(Formula* formula, int coeficiente) {
    if (formula != nullptr && coeficiente >= 0) {
        productos.push_back(make_pair(formula, coeficiente));
    }
}

/* ----------------------- Getters ----------------------- */

string Reaccion::getNombre() const {
    return nombre;
}

bool Reaccion::esBalanceada() const {
    return balanceada;
}

// Obtiene la lista de reactivos
vector<TerminoReaccion> Reaccion::getReactivos() const {
    return reactivos;
}

// Obtiene la lista de productos
vector<TerminoReaccion> Reaccion::getProductos() const {
    return productos;
}

/* ----------------------- Métodos ----------------------- */

// Muestra la reacción completa
void Reaccion::mostrarReaccion() const {
    cout << "\n--- REACCION QUIMICA: " << nombre << " ---\n";
    
    // Imprime Reactivos
    for (size_t i = 0; i < reactivos.size(); ++i) {
        const auto& termino = reactivos[i];
        if (termino.second > 1) {
            cout << termino.second; // Coeficiente
        }
        cout << termino.first->getFormula(); // Fórmula
        
        if (i < reactivos.size() - 1) {
            cout << " + ";
        }
    }

    cout << " -> ";
    
    // Imprime Productos
    for (size_t i = 0; i < productos.size(); ++i) {
        const auto& termino = productos[i];
        if (termino.second > 1) {
            cout << termino.second; // Coeficiente
        }
        cout << termino.first->getFormula(); // Fórmula
        
        if (i < productos.size() - 1) {
            cout << " + ";
        }
    }
    
    cout << endl;
    cout << "Estado: " << (balanceada ? "Balanceada" : "Desbalanceada") << endl;
    cout << "--------------------------------------\n";
}

// Obtiene la lista de elementos únicos que participan en la reacción
vector<string> Reaccion::getElementosParticipantes() const {
    vector<string> simbolos;
    map<string, bool> yaIncluido;

    // Procesar Reactivos
    for (const auto& termino : reactivos) {
        // Obtenemos los elementos de la fórmula (ej: {"H": 2, "O": 1})
        map<string, int> elementosEnFormula = termino.first->getElementosUnicos();
        for (const auto& par : elementosEnFormula) {
            if (!yaIncluido[par.first]) {
                simbolos.push_back(par.first);
                yaIncluido[par.first] = true;
            }
        }
    }
    
    // Procesar Productos (por si hay elementos que solo aparecen en productos, aunque es raro)
    for (const auto& termino : productos) {
        map<string, int> elementosEnFormula = termino.first->getElementosUnicos();
        for (const auto& par : elementosEnFormula) {
            if (!yaIncluido[par.first]) {
                simbolos.push_back(par.first);
                yaIncluido[par.first] = true;
            }
        }
    }

    return simbolos;
}

// Calcula el total de átomos de un símbolo en el lado de los reactivos
int Reaccion::getTotalAtomosReactivo(string simbolo) const {
    int total = 0;
    
    for (const auto& termino : reactivos) {
        int coeficiente = termino.second;
        Formula* formula = termino.first;
        
        // Obtenemos la lista de elementos de la fórmula
        map<string, int> elementos = formula->getElementosUnicos();
        
        // Buscamos el símbolo deseado
        auto it = elementos.find(simbolo);
        
        if (it != elementos.end()) {
            // Se suma: Coeficiente * Cantidad del elemento en la fórmula
            total += coeficiente * it->second;
        }
    }
    return total;
}

// Calcula el total de átomos de un símbolo en el lado de los productos
int Reaccion::getTotalAtomosProducto(string simbolo) const {
    int total = 0;
    
    for (const auto& termino : productos) {
        int coeficiente = termino.second;
        Formula* formula = termino.first;
        
        // Obtenemos la lista de elementos de la fórmula
        map<string, int> elementos = formula->getElementosUnicos();
        
        // Buscamos el símbolo deseado
        auto it = elementos.find(simbolo);
        
        if (it != elementos.end()) {
            // Se suma: Coeficiente * Cantidad del elemento en la fórmula
            total += coeficiente * it->second;
        }
    }
    return total;

}
