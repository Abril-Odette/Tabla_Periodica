/*
    Descripción:
    Clase Elemento para modelar un elemento químico.
    - Contiene información nuclear (A, Z, N) e identificativa (nombre, símbolo).
    - Incluye la lógica para determinar el tipo de elemento y su valencia.
    - Clase padre que será heredada por Metal, NoMetal y Halogeno.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [2025]
    Última modificación: [2025]
*/
#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Elemento {

protected:
    // --- Atributos de Identificación y Propiedades ---
    int numeroAtomico;
    int numeroMasa;
    int neutrones;
    string nombre;
    string simbolo;
    string tipoElemento;

    // --- Atributos de Reactividad ---
    vector<int> estadosOxidacion; // Nuevo: Permite múltiples estados de oxidación
    int valencia;
    bool valenciaModificada;

    // --- Métodos Privados de Cálculo ---
    // Determina el tipo de elemento según el número atómico.
    void determinarTipo();

    // Calcula la valencia automática con reglas periódicas.
    int calcularValenciaAutomatica() const;

    // Calcula la cantidad de neutrones a partir del número de masa y atómico.
    void actualizarNeutrones();

    // Actualiza todas las propiedades dependientes del número atómico (tipo, valencia).
    void actualizarPropiedades();

public:
    /* ======================= Constructores ======================= */
    // Constructor por defecto
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
    
    // Getters de datos nucleares
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