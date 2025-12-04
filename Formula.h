/*
    Descripción:
    Clase Formula, modela un compuesto químico.
    - Implementa Agregación: Contiene punteros a objetos Elemento (símbolos).
    - Contiene lógica para construir la fórmula química textual y calcular la masa molar.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [2025]
    Última modificación: [2025]
*/
#ifndef FORMULA_H
#define FORMULA_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "elemento.h" // Necesario para la agregación de Elemento

using namespace std;

// Definición de un alias para el tipo de dato que almacenará los elementos
typedef pair<Elemento*, int> Componente;

class Formula {

private:
    string nombre;
    string formula; // Fórmula textual (ej: "H2O")
    // Almacena punteros a Elemento y la cantidad de ese elemento
    vector<Componente> elementos; 
    int totalElementos; // Conteo de cuántos elementos UNICOS hay (H, O = 2)
    bool estable;
    float masaMolar; // Usamos float para sencillez

    // --- Métodos Privados de Cálculo ---
    // Construye la fórmula química usando los símbolos y cantidades
    void construirFormula();

    // Evalúa estabilidad: si la molécula tiene al menos 2 elementos únicos, se considera estable
    void evaluarEstabilidad();
    
public:
    /* ======================= Constructores ======================= */
    // Constructor por defecto
    Formula();

    // Constructor con parámetros (solo nombre inicial)
    Formula(string n);

    /* ----------------------- Setters ----------------------- */
    void setNombre(string n);
    void setEstable(bool e);
    // Nota: La fórmula y masa molar se calculan internamente, no se asignan directamente.

    // Método principal de Agregación
    void agregarElemento(Elemento* e, int cantidad); 

    /* ----------------------- Getters ----------------------- */
    string getNombre() const;
    string getFormula() const;
    int getCantidadElementos() const;
    bool esEstable() const;
    float getMasaMolar() const;
    
    // Obtiene la lista de componentes (útil para Balanceador/Estequiometria)
    vector<Componente> getElementosFormula() const;

    /* ----------------------- Métodos ----------------------- */
    // Calcula la masa molar sumando las masas atómicas de los componentes
    void calcularMasaMolar();

    // Devuelve un mapa de símbolos y cantidades (útil para el balanceo)
    map<string, int> getElementosUnicos() const;

    // Muestra información completa de la molécula
    void mostrarInfo() const;
};

#endif