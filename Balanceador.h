/*
    Descripción:
    Clase Balanceador. Implementa el balanceo de reacciones químicas usando el 
    Método de Coeficientes Indeterminados (Algebraico).
    - Convierte la reacción en un sistema lineal de ecuaciones.
    - Calcula los coeficientes estequiométricos enteros más pequeños.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [03/12/2025]
    Última modificación: [07/12/2025]
*/
#ifndef BALANCEADOR_H
#define BALANCEADOR_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <numeric> // Para std::lcm, std::gcd
#include "reaccion.h"

using namespace std;

class Balanceador {

private:
    // Matriz interna para la resolución del sistema de ecuaciones (se usará float para fracciones)
    vector<vector<float>> matrizBalanceo;

    // Métodos auxiliares matemáticos
    int calcularMCD(int a, int b) const;
    int calcularMCM(int a, int b) const;

    // Métodos privados para el proceso de balanceo Algebraico
    
    // Construye la matriz de coeficientes del sistema de ecuaciones
    void construirMatriz(Reaccion* reaccion);
    
    // Resuelve el sistema matricial (Eliminación Gaussiana simplificada + Sustitución)
    vector<int> resolverSistemaMatricial(Reaccion* reaccion);
    
    // Asigna los coeficientes enteros resueltos a la Reaccion
    void asignarCoeficientes(Reaccion* reaccion, const vector<int>& coeficientes);
    
    // Simplifica los coeficientes fraccionarios a la solución entera más pequeña
    vector<int> simplificarASolucionEntera(const vector<float>& coeficientesFraccionarios) const;

public:
    /* ======================= Constructores ======================= */
    Balanceador();

    /* ----------------------- Métodos de Servicio ----------------------- */
    
    // Método principal: Ejecuta todo el proceso de balanceo
    bool balancear(Reaccion* reaccion);

    /* ----------------------- Getters ----------------------- */
    // Muestra la matriz de coeficientes (para depuración)
    void mostrarMatriz() const;
    
};

#endif
