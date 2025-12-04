/*
    Descripción:
    Clase Metal, hereda de Elemento.
    - Especializa a Elemento añadiendo la propiedad de conductividad eléctrica.
    - Implementa métodos específicos como reaccionar con ácido.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [03/12/2025]
    Última modificación: [04/12/2025]
*/
#ifndef METAL_H
#define METAL_H

#include "elemento.h"

class Metal : public Elemento {

private:
    float conductividadElectrica;

public:
    /* ======================= Constructores ======================= */
    Metal(): Elemento();
    // Constructor con parámetros, llama al constructor de la clase padre
    Metal(int _numeroAtomico, string _nombre, string _simbolo, int _numeroMasa, vector<int> _estadosOxidacion, float _conductividadElectrica): Elemento(_numeroAtomico, _nombre, _simbolo, _numeroMasa, _estadosOxidacion);

    /* ----------------------- Getters ----------------------- */
    float getConductividadElectrica() const;

    /* ----------------------- Setters ----------------------- */
    void setConductividadElectrica(float _conductividadElectrica);

    /* ----------------------- Métodos de Herencia ----------------------- */
    string obtenerInformacion() const override;

    /* ----------------------- Métodos ----------------------- */
    // Determina si el metal es reactivo con ácidos
    bool reaccionaConAcido() const;
};


#endif
