#include "metal.h"
#include <sstream> // Necesario para construir strings complejos de forma eficiente

/* ======================= Constructores ======================= */

// Constructor por defecto, llama al constructor por defecto de Elemento
Metal::Metal() : Elemento() {
    conductividadElectrica = 0.0f;
}

// Constructor con parámetros
Metal::Metal(int _numeroAtomico, string _nombre, string _simbolo, int _numeroMasa, vector<int> _estadosOxidacion, float _conductividadElectrica)
    : Elemento(_numeroAtomico, _nombre, _simbolo, _numeroMasa, _estadosOxidacion)
{
    conductividadElectrica = _conductividadElectrica;
}

/* ----------------------- Getters ----------------------- */

// Obtiene la conductividad eléctrica
float Metal::getConductividadElectrica() const {
    return conductividadElectrica;
}

/* ----------------------- Setters ----------------------- */

// Establece la conductividad eléctrica
void Metal::setConductividadElectrica(float _conductividadElectrica) {
    conductividadElectrica = _conductividadElectrica;
}

/* ----------------------- Métodos de Herencia ----------------------- */

// Sobreescribe el método virtual para añadir información específica de Metal
string Metal::obtenerInformacion() const {
    // Reutilizamos la información base y añadimos lo propio de Metal
    stringstream ss;
    ss << Elemento::obtenerInformacion() << "\n";
    ss << "Tipo: Metal\n";
    ss << "Conductividad Electrica: " << conductividadElectrica << " S/m";
    return ss.str();
}

/* ----------------------- Métodos ----------------------- */

// Determina si el metal reacciona con ácido (ejemplo de lógica simple)
bool Metal::reaccionaConAcido() const {
    // Si la conductividad es alta, asumimos que es más reactivo
    return conductividadElectrica > 1000.0f;
}