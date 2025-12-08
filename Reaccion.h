/*
    Descripción:
    Clase Reaccion, modela una ecuación química completa.
    - Implementa Agregación: Contiene punteros a objetos Formula (reactivos y productos).
    - Almacena el estado de balanceo y el nombre de la reacción.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [03/12/2025]
    Última modificación: [04/12/2025]
*/
#ifndef REACCION_H
#define REACCION_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm> // Para usar std::find
#include "formula.h" // para la agregación de Formula

using namespace std;

// Definición de un alias para el tipo de dato que almacenará los reactivos/productos
typedef pair<Formula*, int> TerminoReaccion;

class Reaccion {

private:
    string nombre;
    // Lista de pares (Fórmula*, Coeficiente)
    vector<TerminoReaccion> reactivos; 
    vector<TerminoReaccion> productos;
    bool balanceada; 

public:
    /* ======================= Constructores ======================= */
    Reaccion();
    Reaccion(string n);

    /* ----------------------- Setters ----------------------- */
    void setNombre(string n);
    void setBalanceada(bool b);

    // Métodos para agregar componentes a la reacción (Agregación)
    void agregarReactivo(Formula* formula, int coeficiente); 
    void agregarProducto(Formula* formula, int coeficiente);

    // Permite modificar el coeficiente de un reactivo por su índice
    void setCoeficienteReactivo(size_t index, int coeficiente); 
    // Permite modificar el coeficiente de un producto por su índice
    void setCoeficienteProducto(size_t index, int coeficiente);

    /* ----------------------- Getters ----------------------- */
    string getNombre() const;
    bool esBalanceada() const;

    // Obtiene las listas de reactivos y productos (útil para Balanceador)
    vector<TerminoReaccion> getReactivos() const;
    vector<TerminoReaccion> getProductos() const;
    // Obtiene el coeficiente estequiométrico de una fórmula dada. Devuelve 0 si no existe.
    int getCoeficiente(Formula* formula) const;

    /* ----------------------- Métodos ----------------------- */
    // Muestra la reacción completa en formato textual (ej: H2 + O2 -> H2O)
    void mostrarReaccion() const;

    // Obtiene la lista de elementos únicos que participan en la reacción
    vector<string> getElementosParticipantes() const;

    // Métodos para verificar el balanceo (útil para Balanceador)
    int getTotalAtomosReactivo(string simbolo) const;
    int getTotalAtomosProducto(string simbolo) const;
};


#endif

