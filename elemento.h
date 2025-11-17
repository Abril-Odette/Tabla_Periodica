/*
    Descripción:
    Clase Elemento para modelar un elemento químico.
    - Recopila la información básica del elemento: nombre,
    número atómico y símbolo.
    - Calcula tipo químico y valencia automática (Z = 1–118),
    permitiendo además asignación manual de valencia.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [16/11/25]
    última modificación: [16/11/25]
*/

#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>
using namespace std;

class Elemento {

private:
    int numeroAtomico;
    string nombre;
    string simbolo;
    string tipoElemento;
    int valencia;
    bool valenciaModificada;

    // Determina el tipo de elemento según el número atómico.
    void determinarTipo();

    // Calcula la valencia automática con reglas simples (1–118).
    int calcularValenciaAutomatica() const;

public:
    // Constructores
    Elemento();
    Elemento(int _numeroAtomico, string _nombre, string _simbolo);

    // Setters
    void setNumeroAtomico(int _numeroAtomico);
    void setNombre(string _nombre);
    void setSimbolo(string _simbolo);
    
    // Getters
    int getNumeroAtomico() const;
    string getNombre() const;
    string getSimbolo() const;
    string getTipoElemento() const;

    // Asignación manual opcional de valencia
    void setValenciaManual(int _valencia);

    // Obtiene valencia (manual si existe, si no automática)
    int getValencia();

    // Actualiza todas las propiedades dependientes del número atómico
    void actualizarPropiedades();

    // Imprime información del elemento
    void mostrarInfo() const;
};

#endif