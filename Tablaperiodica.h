/*
    Descripción:
    Clase TablaPeriodica. Actúa como el repositorio central del proyecto.
    - Utiliza Composición: es responsable de crear y almacenar los objetos Elemento.
    - Permite buscar un elemento por su símbolo.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [2025]
    Última modificación: [2025]
*/
#ifndef TABLAPERIODICA_H
#define TABLAPERIODICA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "elemento.h" // Necesario para gestionar los objetos Elemento
#include "metal.h"    // Necesario para crear objetos Metal
#include "nometal.h"  // Necesario para crear objetos NoMetal

using namespace std;

class TablaPeriodica {

private:
    // Mapa que almacena todos los elementos, usando el símbolo como clave.
    // La clase es responsable de la memoria de estos punteros (Composición).
    map<string, Elemento*> elementosRegistrados;

public:
    /* ======================= Constructores y Destructor ======================= */
    // Constructor por defecto
    TablaPeriodica(); 

    // Destructor: Fundamental para liberar la memoria de los punteros (Regla de Tres/Cinco)
    ~TablaPeriodica(); 

    /* ----------------------- Métodos ----------------------- */
    // Carga todos los elementos iniciales en el mapa.
    void cargarElementos();

    // Busca un elemento por su símbolo.
    Elemento* buscarElemento(string simbolo) const;

    // Muestra todos los elementos filtrados por un tipo (ej. "Metal", "Halogeno").
    void mostrarElementosPorTipo(string tipo) const;
};

#endif