/*
    Descripción:
    Clase Balanceador. Clase de servicio que realiza el balanceo de una Reaccion.
    - Utiliza lógica matemática (sistema de ecuaciones) sobre los datos de la Reaccion.
    - Contiene métodos para construir y resolver la matriz de balanceo.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [2025]
    Última modificación: [2025]
*/
#ifndef BALANCEADOR_H
#define BALANCEADOR_H

#include <iostream>
#include <vector>
#include <map>
#include "reaccion.h"

using namespace std;

class Balanceador {

private:
    // Matriz interna para la resolución del sistema de ecuaciones (se usará float para fracciones)
    vector<vector<float>> matrizBalanceo;

    // Métodos privados para el proceso de balanceo
    // Construye la matriz de coeficientes a partir de la Reaccion
    void construirMatriz(Reaccion* reaccion);
    
    // Resuelve el sistema matricial (lógica simplificada)
    vector<int> resolverSistemaMatricial();
    
    // Asigna los coeficientes enteros resueltos a la Reaccion
    void asignarCoeficientes(Reaccion* reaccion, const vector<int>& coeficientes);

public:
    /* ======================= Constructores ======================= */
    // Constructor por defecto
    Balanceador();

    /* ----------------------- Métodos de Servicio ----------------------- */
    
    // Método principal: Ejecuta todo el proceso de balanceo
    bool balancear(Reaccion* reaccion);

    /* ----------------------- Getters (Debugging) ----------------------- */
    
    // Obtiene la matriz de balanceo (útil para mostrar al usuario o para depuración)
    vector<vector<float>> getMatrizBalanceo() const;
};

#endif