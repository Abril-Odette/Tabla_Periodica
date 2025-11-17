#include "atomo.h"

/* ======================= Constructotes ======================= */

Atomo::Atomo() 
    : elemento(), carga(0)
{
    numeroAtomico = elemento.getNumeroAtomico();

    // Asumir un isótopo estable simple: A = Z + 1
    numeroMasa = numeroAtomico + 1;

    actualizarNeutrones();
    calcularEValencia();
    actualizarEstabilidad();
}

Atomo::Atomo(Elemento _elemento, int masa)
    : elemento(_elemento), carga(0)
{
    numeroAtomico = elemento.getNumeroAtomico();

    // Si no se especifica A, usar A ≈ Z + 1
    numeroMasa = (masa <= 0) ? numeroAtomico + 1 : masa;

    actualizarNeutrones();
    calcularEValencia();
    actualizarEstabilidad();
}

/* ----------------------- Setters ----------------------- */

void Atomo::setCarga(int _carga) {
    carga = _carga;
    calcularEValencia();
    actualizarEstabilidad();
}

void Atomo::setA(int nuevoMasa) {
    // Evita valores físicamente imposibles
    if (nuevoMasa <= numeroAtomico) {
        numeroMasa = numeroAtomico + 1;
    } else {
        numeroMasa = nuevoMasa;
    }
    actualizarNeutrones();
}

/* ----------------------- Getters ----------------------- */

int Atomo::getEValencia() const { 
    return eValencia; 
}

int Atomo::getCarga() const { 
    return carga; 
}

bool Atomo::esEstable() const { 
    return estable; 
}

int Atomo::getZ() const { 
    return numeroAtomico; 
}

int Atomo::getA() const { 
    return numeroMasa; 
}

int Atomo::getN() const { 
    return neutrones; 
}

Elemento Atomo::getElemento() const { 
    return elemento; 
}

/* ----------------------- Métodos ----------------------- */

// Calcula el número de neutrones restando el número atómico al número de masa.
void Atomo::actualizarNeutrones() {
    neutrones = numeroMasa - numeroAtomico;
    if (neutrones < 0) neutrones = 0;
}

// Calcula los electrones de valencia considerando la valencia del elemento y los ajustes por carga.
void Atomo::calcularEValencia() {
    eValencia = elemento.getValencia();

    // Ajuste por carga
    eValencia -= carga;
    if (eValencia < 0) eValencia = 0;
    if (eValencia > 8) eValencia = 8;
}

// Determina si el átomo es estable aplicando la regla del dueto (H, He) u octeto.
void Atomo::actualizarEstabilidad() {
    if (numeroAtomico == 1 || numeroAtomico == 2) {
        estable = (eValencia == 2); // Dueto
    }
    else {
        estable = (eValencia == 8); // Octeto
    }
}

// Evalúa si dos átomos pueden enlazarse verificando si la suma de sus electrones de valencia completa dueto u octeto.
bool Atomo::puedeEnlazarCon(const Atomo &otro) const {
    int suma = eValencia + otro.eValencia;

    // Dueto u octeto
    return (suma == 2 || suma == 8);
}

// Muestra en consola las propiedades nucleares y electrónicas del átomo.
void Atomo::mostrarInfo() const {
    cout << "\nAtomo de " << elemento.getNombre()
         << " (" << elemento.getSimbolo() << ")\n";

    cout << "Numero atomico (Z): " << numeroAtomico << endl;
    cout << "Numero de masa (A): " << numeroMasa << endl;
    cout << "Neutrones (N): " << neutrones << endl;

    cout << "Electrones de valencia: " << eValencia << endl;
    cout << "Carga: " << carga << endl;

    cout << "Estable (octeto): " << (estable ? "Si" : "No") << endl;
}