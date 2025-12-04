#include "estequiometria.h"
#include <cmath> // Necesario para funciones matemáticas como fmod o similares si se usaran.

/* ======================= Constructores ======================= */

// Constructor por defecto
Estequiometria::Estequiometria() {
    // No hay inicialización de atributos ya que no tiene.
}

/* ----------------------- Métodos de Conversión Molar ----------------------- */

// Calcula los moles (n = masa / MM)
double Estequiometria::calcularMoles(float masaGramos, Formula* formula) const {
    if (formula != nullptr && formula->getMasaMolar() > 0.0f) {
        // Se realiza la conversión de float a double para el cálculo final
        return (double)masaGramos / (double)formula->getMasaMolar();
    }
    return 0.0;
}

// Calcula la masa en gramos (masa = n * MM)
float Estequiometria::calcularGramos(double moles, Formula* formula) const {
    if (formula != nullptr) {
        // El resultado se devuelve como float
        return (float)(moles * (double)formula->getMasaMolar());
    }
    return 0.0f;
}

/* ----------------------- Métodos de Reacción ----------------------- */

// Calcula gramos de producto (se asume que el primer reactivo y el primer producto son los términos relevantes)
float Estequiometria::calcularGramosProducto(Reaccion* reaccion, float gramosReactivo) const {
    if (reaccion == nullptr || !reaccion->esBalanceada() || reaccion->getReactivos().empty() || reaccion->getProductos().empty()) {
        cout << "Error: Reaccion invalida o no balanceada para calculos estequiometricos.\n";
        return 0.0f;
    }

    // --- Lógica Simplificada Estequiométrica ---
    // 1. Obtener la información del primer Reactivo (R1) y primer Producto (P1)
    TerminoReaccion R1 = reaccion->getReactivos()[0];
    TerminoReaccion P1 = reaccion->getProductos()[0];
    
    // 2. Calcular Moles del reactivo (R1)
    double molesR1 = calcularMoles(gramosReactivo, R1.first);
    
    // 3. Aplicar la relación molar (Moles R1 * (Coef. P1 / Coef. R1))
    // Usamos el coeficiente estequiométrico para la conversión
    double relacionMolar = (double)P1.second / (double)R1.second;
    double molesP1 = molesR1 * relacionMolar;
    
    // 4. Convertir Moles de producto (P1) a Gramos
    return calcularGramos(molesP1, P1.first);
}

// Calcula la masa necesaria de reactivo (inverso del cálculo anterior)
float Estequiometria::calcularMasaReactivoNecesaria(Reaccion* reaccion, float productoDeseado) const {
    if (reaccion == nullptr || !reaccion->esBalanceada() || reaccion->getReactivos().empty() || reaccion->getProductos().empty()) {
        cout << "Error: Reaccion invalida o no balanceada para calculos estequiometricos.\n";
        return 0.0f;
    }

    // --- Lógica Simplificada Estequiométrica (Inversa) ---
    TerminoReaccion R1 = reaccion->getReactivos()[0];
    TerminoReaccion P1 = reaccion->getProductos()[0];

    // 1. Calcular Moles del producto deseado (P1)
    double molesP1 = calcularMoles(productoDeseado, P1.first);

    // 2. Aplicar la relación molar inversa (Moles P1 * (Coef. R1 / Coef. P1))
    double relacionMolarInversa = (double)R1.second / (double)P1.second;
    double molesR1 = molesP1 * relacionMolarInversa;

    // 3. Convertir Moles de reactivo (R1) a Gramos
    return calcularGramos(molesR1, R1.first);
}