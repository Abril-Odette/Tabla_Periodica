/*
    Descripción:
    Clase Elemento para modelar un elemento químico.
    - Contiene información nuclear (A, Z, N) e identificativa (nombre, símbolo).
    - Incluye la lógica para determinar el tipo de elemento y su valencia.
    - Clase padre que será heredada por Metal, NoMetal y Halogeno.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [16/11/2025]
    Última modificación: [03/12/2025]
*/
#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Elemento {

protected:
    int numeroAtomico;
    int numeroMasa;
    int neutrones;
    string nombre;
    string simbolo;
    string tipoElemento;
    vector<int> estadosOxidacion;
    int valencia;
    bool valenciaModificada;

    // --- Métodos Privados de Cálculo ---
    void determinarTipo();
    int calcularValenciaAutomatica() const;
    void actualizarNeutrones();
    void actualizarPropiedades();

public:
    /* ======================= Constructores ======================= */
    Elemento(); 
    // Constructor con parámetros: num. atómico, nombre, símbolo, masa atómica, y vector de estados de oxidación
    Elemento(int _numeroAtomico, string _nombre, string _simbolo, int _numeroMasa, vector<int> _estadosOxidacion);

    // --- Métodos Virtuales ---
    // Método virtual para polimorfismo, se implementa en las clases hijas
    virtual string obtenerInformacion() const;

    /* ----------------------- Getters ----------------------- */
    int getNumeroAtomico() const;
    string getNombre() const;
    string getSimbolo() const;
    string getTipoElemento() const;
    int getValencia() const;
    vector<int> getEstadosOxidacion() const;
    bool getValenciaModificada() const;
    int getA() const; // Número de masa
    int getN() const; // Neutrones

    /* ----------------------- Setters ----------------------- */
    void setNumeroAtomico(int _numeroAtomico);
    void setNombre(string _nombre);
    void setSimbolo(string _simbolo);
    void setValenciaManual(int _valencia);
    void setNumeroMasa(int _numeroMasa);
    void setEstadosOxidacion(vector<int> _estadosOxidacion);

    /* ----------------------- Métodos ----------------------- */
    // Imprime información del elemento (para la clase base)
    void mostrarInfo() const;
};


#endif
