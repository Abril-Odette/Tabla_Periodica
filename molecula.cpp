#include "molecula.h"

/* ======================= IMPLEMENTACIÓN ======================= */

Molecula::Molecula() {
    nombre = "";
    formula = "";
    totalElementos = 0;
    estable = false;
}

/* ----------------------------- SETTERS ----------------------------- */

void Molecula::setNombre(string n) {
    nombre = n;
}

void Molecula::agregarElemento(string simbolo, int cantidad) {
    if (totalElementos < 20) {
        elementos[totalElementos] = simbolo;
        cantidades[totalElementos] = cantidad;
        totalElementos++;

        construirFormula();
        evaluarEstabilidad();
    }
}

/* ----------------------------- GETTERS ----------------------------- */

string Molecula::getNombre() const {
    return nombre;
}

string Molecula::getFormula() const {
    return formula;
}

int Molecula::getCantidadElementos() const {
    return totalElementos;
}

bool Molecula::esEstable() const {
    return estable;
}

/* ----------------------------- MÉTODOS ----------------------------- */

// Construye fórmula simple: ejemplo H2 + O1 → H2O
void Molecula::construirFormula() {
    formula = "";
    std::stringstream ss;

    for (int i = 0; i < totalElementos; i++) {
        ss << elementos[i];  // Agregar símbolo

        if (cantidades[i] > 1)
            ss << cantidades[i];  // Agregar número sin usar to_string
    }

    formula = ss.str();
}


// Criterio simple: si tiene más de 1 elemento, se considera estable
void Molecula::evaluarEstabilidad() {
    estable = (totalElementos >= 2);
}

// Muestra info básica
void Molecula::mostrarInfo() const {
    cout << "INFORMACION MOLECULA     \n";
    cout << "Nombre: " << nombre << endl;
    cout << "Formula: " << formula << endl;
    cout << "Numero de elementos: " << totalElementos << endl;
    cout << "Estabilidad: " << (estable ? "Estable" : "Inestable") << endl;
    cout << "\n--- Componentes ---\n";
    for (int i = 0; i < totalElementos; i++) {
        cout << elementos[i] << ": " << cantidades[i] << endl;
    }
}
