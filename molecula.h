/*
    Clase Molecula (versión simplificada)
    - Permite construir una molécula usando su nombre y sus elementos
    - Usa arreglos simples en lugar de estructuras avanzadas
    - Construye fórmula química de forma básica
    - Permite agregar elementos y mostrar información

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [16/11/25]
    Última modificación: [16/11/25]
*/
#ifndef MOLECULA_H
#define MOLECULA_H

#include <iostream>
#include <sstream>
using namespace std;

class Molecula {

private:
    string nombre;               
    string elementos[20];        
    int cantidades[20];          
    int totalElementos;          
    string formula;              
    bool estable;                

    // Construye la fórmula química usando los elementos y cantidades
    void construirFormula();

    // Evalúa estabilidad de manera sencilla:
    // Si la molécula tiene al menos 2 elementos, se considera estable
    void evaluarEstabilidad();

public:
    // Constructor
    Molecula();

    // Setters
    void setNombre(string n);
    void agregarElemento(string simbolo, int cantidad);

    // Getters
    string getNombre() const;
    string getFormula() const;
    int getCantidadElementos() const;
    bool esEstable() const;

    // Muestra información completa de la molécula
    void mostrarInfo() const;
};

#endif