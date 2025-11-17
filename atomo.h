/*
    Descripción:
    Clase Atomo que modela un átomo a partir de un Elemento.
    - Integra datos electrónicos (valencia, carga, estabilidad)
    - Integra datos nucleares (Z, A, N)
    - Ajusta la estabilidad según dueto/octeto
    - Permite verificar compatibilidad de enlace entre átomos

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [16/11/25]
    Última modificación: [16/11/25]
*/
#ifndef ATOMO_H
#define ATOMO_H

#include <iostream>
#include "elemento.h"
using namespace std;

class Atomo {

private:
    Elemento elemento;
    int eValencia;
    int carga;
    bool estable;
    int numeroAtomico;
    int numeroMasa;
    int neutrones;

    // Calcula la cantidad de neutrones a partir del número de masa y el número atómico.
    void actualizarNeutrones();

    // Calcula los electrones de valencia considerando la valencia del elemento y la carga del átomo.
    void calcularEValencia();

    // Determina si el átomo es estable aplicando la regla del octeto o del dueto.
    void actualizarEstabilidad();

public:
    // Constructores
    Atomo();
    Atomo(Elemento _elemento, int masa = -1);

    // Setters
    void setCarga(int _carga);
    void setA(int nuevoMasa);

     // Getters
    int getEValencia() const;
    int getCarga() const;
    bool esEstable() const;
    int getZ() const;
    int getA() const;
    int getN() const;
    Elemento getElemento() const;

    // Verifica si el átomo puede enlazarse con otro según la compatibilidad de sus electrones de valencia.
    bool puedeEnlazarCon(const Atomo &otro) const;

    // Muestra en pantalla toda la información relevante del átomo.
    void mostrarInfo() const;
};

#endif