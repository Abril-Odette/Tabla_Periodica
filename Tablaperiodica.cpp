#include "tablaperiodica.h"

/* ======================= Constructores y Destructor ======================= */

// Constructor por defecto
TablaPeriodica::TablaPeriodica() {
    // Carga los elementos al inicializar la tabla
    cargarElementos();
}

// Destructor: Libera la memoria de todos los objetos Elemento creados
TablaPeriodica::~TablaPeriodica() {
    // Itera sobre el mapa y elimina cada puntero
    for (auto const& [key, val] : elementosRegistrados) {
        delete val;
    }
    elementosRegistrados.clear();
}

/* ----------------------- Métodos ----------------------- */

// Carga los elementos iniciales (solo algunos ejemplos para fines didácticos)
void TablaPeriodica::cargarElementos() {
    // Ejemplo de NoMetal: Hidrógeno (H)
    elementosRegistrados["H"] = new NoMetal(1, "Hidrogeno", "H", 1, {1, -1}, 2.20f);
    
    // Ejemplo de NoMetal: Carbono (C)
    elementosRegistrados["C"] = new NoMetal(6, "Carbono", "C", 12, {4, 2, -4}, 2.55f);

    // Ejemplo de NoMetal: Oxígeno (O)
    elementosRegistrados["O"] = new NoMetal(8, "Oxigeno", "O", 16, {-2}, 3.44f);
    
    // Ejemplo de Metal: Sodio (Na)
    elementosRegistrados["Na"] = new Metal(11, "Sodio", "Na", 23, {1}, 21000000.0f); 
    
    // Ejemplo de Metal: Hierro (Fe)
    elementosRegistrados["Fe"] = new Metal(26, "Hierro", "Fe", 56, {3, 2}, 9930000.0f);
}

// Busca un elemento por su símbolo
Elemento* TablaPeriodica::buscarElemento(string simbolo) const {
    // Busca el elemento en el mapa
    auto it = elementosRegistrados.find(simbolo);
    
    // Verifica si el elemento fue encontrado
    if (it != elementosRegistrados.end()) {
        return it->second; // Retorna el puntero al objeto Elemento
    }
    
    // Si no se encuentra, retorna nullptr
    return nullptr;
}

// Muestra todos los elementos filtrados por un tipo
void TablaPeriodica::mostrarElementosPorTipo(string tipo) const {
    cout << "\n--- Elementos de tipo: " << tipo << " ---\n";
    bool encontrado = false;
    
    for (auto const& [simbolo, elemento] : elementosRegistrados) {
        if (elemento->getTipoElemento() == tipo) {
            cout << elemento->obtenerInformacion() << "\n";
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        cout << "No se encontraron elementos de ese tipo.\n";
    }
    cout << "------------------------------------\n";
}