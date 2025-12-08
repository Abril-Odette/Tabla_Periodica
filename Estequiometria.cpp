#include "estequiometria.h"
#include <cmath> 

/* ======================= Constructores ======================= */
Estequiometria::Estequiometria() {
    // No hay inicialización de atributos ya que no tiene.
}

/* ----------------------- Métodos de Conversión Molar (Básicos) ----------------------- */

// Calcula los moles (n = masa / MM)
double Estequiometria::calcularMoles(float masaGramos, Formula* formula) const {
    if (formula != nullptr && formula->getMasaMolar() > 1e-6) { // Usamos tolerancia para evitar divisiones por cero
        // Se realiza la conversión de float a double para el cálculo de alta precisión
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

/* ----------------------- Métodos de Reacción (Robusto y Genérico) ----------------------- */

// Calcula la masa relacionada entre dos fórmulas de una reacción balanceada
float Estequiometria::calcularMasaRelacionada(Reaccion* reaccion, float masaPartida, Formula* formulaPartida, Formula* formulaLlegada) const {
    
    // --- 1. Verificación y Coeficientes ---
    if (reaccion == nullptr || !reaccion->esBalanceada() || formulaPartida == nullptr || formulaLlegada == nullptr) {
        cout << "Error Estequiometria: Reaccion invalida o desbalanceada.\n";
        return 0.0f;
    }
    
    int coefPartida = reaccion->getCoeficiente(formulaPartida);
    int coefLlegada = reaccion->getCoeficiente(formulaLlegada);

    if (coefPartida <= 0 || coefLlegada <= 0) {
        cout << "Error Estequiometria: Las formulas de partida o llegada no son parte de la reaccion.\n";
        return 0.0f;
    }
    
    // --- 2. Moles de Partida (Masa -> Moles) ---
    // n_partida = masa_partida / MM_partida
    double molesPartida = calcularMoles(masaPartida, formulaPartida);
    
    if (molesPartida <= 0.0) {
        cout << "Error Estequiometria: La masa molar de la formula de partida es cero o invalida.\n";
        return 0.0f;
    }

    // --- 3. Relación Molar (Moles Partida -> Moles Llegada) ---
    // n_llegada = n_partida * (Coef_Llegada / Coef_Partida)
    
    double relacionMolar = (double)coefLlegada / (double)coefPartida;
    double molesLlegada = molesPartida * relacionMolar;
    
    // --- 4. Gramos de Llegada (Moles -> Masa) ---
    // Masa_llegada = n_llegada * MM_llegada
    return calcularGramos(molesLlegada, formulaLlegada);
}
