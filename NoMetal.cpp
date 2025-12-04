#include "nometal.h"
#include <sstream>

/* ======================= Constructores ======================= */
// Constructor por defecto, llama al constructor por defecto de Elemento
NoMetal::NoMetal() : Elemento() {
    electronegatividad = 0.0f;
}

// Constructor con parámetros
NoMetal::NoMetal(int _numeroAtomico, string _nombre, string _simbolo, int _numeroMasa, vector<int> _estadosOxidacion, float _electronegatividad)
    : Elemento(_numeroAtomico, _nombre, _simbolo, _numeroMasa, _estadosOxidacion)
{
    electronegatividad = _electronegatividad;
}

/* ----------------------- Getters ----------------------- */
float NoMetal::getElectronegatividad() const {
    return electronegatividad;
}

/* ----------------------- Setters ----------------------- */
void NoMetal::setElectronegatividad(float _electronegatividad) {
    electronegatividad = _electronegatividad;
}

/* ----------------------- Métodos de Herencia ----------------------- */

// Sobreescribe el método virtual para añadir información específica de NoMetal
string NoMetal::obtenerInformacion() const {
    // Reutilizamos la información base y añadimos lo propio de NoMetal
    stringstream ss;
    ss << Elemento::obtenerInformacion() << "\n";
    ss << "Tipo: No Metal\n";
    ss << "Electronegatividad: " << electronegatividad;
    return ss.str();
}

/* ----------------------- Métodos ----------------------- */

// Calcula un punto de ebullición
float NoMetal::calcularPuntoEbullicion() const {
    // Lógica simple: Un punto de ebullición estimado basado en la electronegatividad
    // Usamos una fórmula sencilla para ilustrar el método.
    return 100.0f * (electronegatividad - 1.0f); 

}

