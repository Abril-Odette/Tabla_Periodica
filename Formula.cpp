#include "formula.h"

/* ======================= Constructores ======================= */

// Constructor por defecto
Formula::Formula() {
    nombre = "";
    formula = "";
    totalElementos = 0;
    estable = false;
    masaMolar = 0.0f;
    // El vector 'elementos' se inicializa vacío por defecto
}

// Constructor con parámetros
Formula::Formula(string n) {
    nombre = n;
    formula = "";
    totalElementos = 0;
    estable = false;
    masaMolar = 0.0f;
}

/* ----------------------- Setters ----------------------- */
void Formula::setNombre(string n) {
    nombre = n;
}

// Establece el estado de estabilidad
void Formula::setEstable(bool e) {
    estable = e;
}

// Agrega un elemento a la fórmula (Agregación)
void Formula::agregarElemento(Elemento* e, int cantidad) {
    // Solo si el puntero es válido y la cantidad es positiva
    if (e != nullptr && cantidad > 0) {
        // Almacena el puntero al Elemento y la cantidad
        elementos.push_back(make_pair(e, cantidad)); 
        totalElementos = elementos.size();

        // Recalcular propiedades al agregar un nuevo componente
        construirFormula();
        evaluarEstabilidad();
        calcularMasaMolar();
    }
}

/* ----------------------- Getters ----------------------- */

string Formula::getNombre() const {
    return nombre;
}

string Formula::getFormula() const {
    return formula;
}

int Formula::getCantidadElementos() const {
    return totalElementos;
}

bool Formula::esEstable() const {
    return estable;
}

float Formula::getMasaMolar() const {
    return masaMolar;
}

// Obtiene la lista de componentes de la fórmula
vector<Componente> Formula::getElementosFormula() const {
    return elementos;
}

/* ----------------------- Métodos Privados de Cálculo ----------------------- */

// Construye la fórmula simple (ej: H2O)
void Formula::construirFormula() {
    stringstream ss;

    for (const auto& componente : elementos) {
        // componente.first es el puntero a Elemento*
        // componente.second es la cantidad (int)
        
        ss << componente.first->getSimbolo();
        
        // Si la cantidad es mayor a 1, se añade el subíndice
        if (componente.second > 1) {
            ss << componente.second;
        }
    }
    formula = ss.str();
}

// Criterio simple: si tiene más de 1 elemento UNICO, se considera estable
void Formula::evaluarEstabilidad() {
    estable = (elementos.size() >= 2);
}

// Calcula la masa molar
void Formula::calcularMasaMolar() {
    masaMolar = 0.0f;
    
    for (const auto& componente : elementos) {
        // Se multiplica la masa atómica (A) por la cantidad
        // Se usa float(componente.first->getA()) para asegurar que la multiplicación sea float
        masaMolar += float(componente.first->getA()) * float(componente.second);
    }
}

/* ----------------------- Métodos ----------------------- */

// Devuelve un mapa de símbolos y cantidades (ej: {"H": 2, "O": 1})
map<string, int> Formula::getElementosUnicos() const {
    map<string, int> unicos;
    
    for (const auto& componente : elementos) {
        string simbolo = componente.first->getSimbolo();
        int cantidad = componente.second;
        
        // Suma las cantidades si el elemento ya existe (ej. en un compuesto complejo)
        unicos[simbolo] += cantidad;
    }
    return unicos;
}

// Muestra información completa de la fórmula
void Formula::mostrarInfo() const {
    cout << "INFORMACION FORMULA\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Formula: " << formula << endl;
    cout << "Masa Molar: " << masaMolar << " u.m.a." << endl;
    cout << "Numero de elementos unicos: " << totalElementos << endl;
    cout << "Estabilidad: " << (estable ? "Estable" : "Inestable") << endl;
    cout << "\n--- Componentes ---\n";
    for (const auto& componente : elementos) {
        cout << componente.first->getSimbolo() << ": " << componente.second << endl;
    }
    cout << "---------------------\n";

}
