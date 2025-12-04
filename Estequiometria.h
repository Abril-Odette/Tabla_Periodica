/*
    Descripción:
    Clase Estequiometria. Clase de servicio o utilidad.
    - Se enfoca en la lógica matemática de conversiones (masa a moles, moles a masa).
    - Utiliza los datos (masa molar) de los objetos Formula y Reaccion que recibe como parámetros.
    - No almacena atributos, solo métodos de acción.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [03/12/2025]
    Última modificación: [04/12/2025]
*/
#ifndef ESTEQUIOMETRIA_H
#define ESTEQUIOMETRIA_H

#include <iostream>
#include "formula.h"
#include "reaccion.h"

using namespace std;

class Estequiometria {

// Esta clase no tiene atributos, ya que es una clase de servicio.

public:
    /* ======================= Constructores ======================= */
    Estequiometria();

    /* ----------------------- Métodos de Conversión Molar ----------------------- */
    
    // Calcula los moles a partir de una masa dada de una fórmula.
    double calcularMoles(float masaGramos, Formula* formula) const;

    // Calcula la masa en gramos a partir de un número de moles de una fórmula.
    float calcularGramos(double moles, Formula* formula) const;

    /* ----------------------- Métodos de Reacción ----------------------- */

    // Calcula los gramos de un producto producido a partir de gramos de un reactivo en una reacción balanceada.
    // Nota: La lógica del balanceo se maneja de forma simplificada aquí.
    float calcularGramosProducto(Reaccion* reaccion, float gramosReactivo) const;

    // Calcula la masa necesaria de un reactivo para obtener una cantidad deseada de producto.
    float calcularMasaReactivoNecesaria(Reaccion* reaccion, float productoDeseado) const;
};


#endif
