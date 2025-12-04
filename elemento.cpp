#include "elemento.h"

/* ======================= Constructores ======================= */

// Constructor por defecto
Elemento::Elemento() {
    numeroAtomico = 0;
    numeroMasa = 0;
    neutrones = 0;
    nombre = "";
    simbolo = "";
    tipoElemento = "Desconocido";
    valencia = 0;
    valenciaModificada = false;
    // estadosOxidacion se inicializa como vector vacío por defecto
}

// Constructor con parámetros
Elemento::Elemento(int _numeroAtomico, string _nombre, string _simbolo, int _numeroMasa, vector<int> _estadosOxidacion) {
    numeroAtomico = _numeroAtomico;
    nombre = _nombre;
    simbolo = _simbolo;
    numeroMasa = _numeroMasa;
    estadosOxidacion = _estadosOxidacion;

    valenciaModificada = false; // Se reinicia para usar la automática
    actualizarPropiedades();
    actualizarNeutrones();
}

// Método virtual para polimorfismo (implementación base)
string Elemento::obtenerInformacion() const {
    return "Elemento: " + nombre + " (" + simbolo + ")";
}

/* ----------------------- Getters ----------------------- */

int Elemento::getNumeroAtomico() const {
    return numeroAtomico;
}

string Elemento::getNombre() const {
    return nombre;
}

string Elemento::getSimbolo() const {
    return simbolo;
}

string Elemento::getTipoElemento() const {
    return tipoElemento;
}

int Elemento::getValencia() const {
    // Nota: Se usa valencia (el atributo) porque se actualiza en actualizarPropiedades
    return valencia;
}

vector<int> Elemento::getEstadosOxidacion() const {
    return estadosOxidacion;
}

bool Elemento::getValenciaModificada() const {
    return valenciaModificada;
}

int Elemento::getA() const {
    return numeroMasa;
}

int Elemento::getN() const {
    return neutrones;
}

/* ----------------------- Setters ----------------------- */

// Establece el número atómico y actualiza propiedades dependientes
void Elemento::setNumeroAtomico(int _numeroAtomico) {
    numeroAtomico = _numeroAtomico;
    actualizarPropiedades();
    actualizarNeutrones();
}

void Elemento::setNombre(string _nombre) {
    nombre = _nombre;
}

void Elemento::setSimbolo(string _simbolo) {
    simbolo = _simbolo;
}

void Elemento::setValenciaManual(int _valencia) {
    valencia = _valencia;
    valenciaModificada = true;
}

void Elemento::setNumeroMasa(int _numeroMasa) {
    numeroMasa = _numeroMasa;
    actualizarNeutrones();
}

void Elemento::setEstadosOxidacion(vector<int> _estadosOxidacion) {
    estadosOxidacion = _estadosOxidacion;
}

/* ----------------------- Métodos Privados de Cálculo ----------------------- */

// Calcula la cantidad de neutrones
void Elemento::actualizarNeutrones() {
    neutrones = numeroMasa - numeroAtomico;
    if (neutrones < 0) neutrones = 0;
}

// Determina tipo químico según categorías generales (lógica simplificada)
void Elemento::determinarTipo() {
    int z = numeroAtomico;

    if (z == 1 || z == 6 || z == 7 || z == 8 || z == 15 || z == 16) {
        tipoElemento = "No metal";
    }
    else if (z == 2 || z == 10 || z == 18 || z == 36 || z == 54 || z == 86) {
        tipoElemento = "Gas noble";
    }
    else if (z == 3 || z == 11 || z == 19 || z == 37 || z == 55) {
        tipoElemento = "Metal alcalino";
    }
    else if (z == 4 || z == 12 || z == 20 || z == 38 || z == 56) {
        tipoElemento = "Metal alcalinotérreo";
    }
    else if (z == 9 || z == 17 || z == 35 || z == 53 || z == 85) {
        tipoElemento = "Halogeno";
    }
    else if (z == 5 || z == 14 || z == 32 || z == 33 || z == 51 || z == 52) {
        tipoElemento = "Metaloide";
    }
    else if ((z >= 21 && z <= 30) || (z >= 39 && z <= 48) || 
             (z >= 72 && z <= 80) || (z >= 104 && z <= 112)) {
        tipoElemento = "Metal de transicion";
    }
    else {
        tipoElemento = "Metal";
    }
}

// Calcula valencia automática mediante reglas periódicas simples.
int Elemento::calcularValenciaAutomatica() const {
    int z = numeroAtomico;

    if (z == 2 || z == 10 || z == 18 || z == 36 || z == 54 || z == 86 || z == 118) {
        return 0; // Gases nobles
    }

    if (z % 18 == 1) return 1;
    if (z % 18 == 2) return 2;

    if ((z >= 21 && z <= 30) || (z >= 39 && z <= 48) || 
        (z >= 72 && z <= 80)) {
        return 2; // Simplificación para metales de transición
    }

    if (z % 18 == 13) return 3;
    if (z % 18 == 14) return 4;
    if (z % 18 == 15) return 3;
    if (z % 18 == 16) return 2;
    if (z % 18 == 17) return 1;

    return 1; // Default
}

// Actualiza todas las propiedades dependientes
void Elemento::actualizarPropiedades() {
    determinarTipo();
    valencia = calcularValenciaAutomatica();
}

/* ----------------------- Métodos ----------------------- */

// Imprime información del elemento
void Elemento::mostrarInfo() const {
    cout << "Elemento: " << nombre << " (" << simbolo << ")\n";
    cout << "Numero atomico: " << numeroAtomico << "\n";
    cout << "Tipo: " << tipoElemento << "\n";
    cout << "Valencia: " << valencia << "\n";
    cout << "Masa: " << numeroMasa << "\n";
    cout << "Neutrones: " << neutrones << "\n\n";

}
