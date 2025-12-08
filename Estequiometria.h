/*
    Descripción:
    Clase Estequiometria. Clase de servicio o utilidad enfocada en la lógica
    matemática de conversiones molares y cálculos de reacción (masa -> moles -> masa).
    - Utiliza los coeficientes balanceados de la clase Reaccion.
    - No almacena atributos, solo métodos de acción (servicio).

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [03/12/2025]
    Última modificación: [07/12/2025]
*/
#ifndef ESTEQUIOMETRIA_H
#define ESTEQUIOMETRIA_H

#include <iostream>
#include <string>
#include "formula.h"
#include "reaccion.h"

using namespace std;

class Estequiometria {

// Esta clase no tiene atributos, ya que es una clase de servicio.

public:
    /* ======================= Constructores ======================= */
    Estequiometria();

    /* ----------------------- Métodos de Conversión Molar (Básicos) ----------------------- */
    
    // Calcula los moles (n = masa / MM) a partir de una masa dada de una fórmula.
    double calcularMoles(float masaGramos, Formula* formula) const;

    // Calcula la masa en gramos (masa = n * MM) a partir de un número de moles de una fórmula.
    float calcularGramos(double moles, Formula* formula) const;

    /* ----------------------- Métodos de Reacción (Robusto y Genérico) ----------------------- */

    // Método principal: Calcula la masa requerida/producida de una sustancia (Llegada)
    // a partir de una masa conocida de otra sustancia (Partida) en una reacción balanceada.
    float calcularMasaRelacionada(Reaccion* reaccion, float masaPartida, Formula* formulaPartida, Formula* formulaLlegada) const;
};


#endif
