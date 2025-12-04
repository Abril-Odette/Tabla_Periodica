/*
    Descripción:
    Clase Metal, hereda de Elemento.
    - Especializa a Elemento añadiendo la propiedad de conductividad eléctrica.
    - Implementa métodos específicos como reaccionar con ácido.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [2025]
    Última modificación: [2025]
*/
#ifndef METAL_H
#define METAL_H

#include "elemento.h" // Incluye la clase padre

class Metal : public Elemento {

private:
    float conductividadElectrica;

public:
    /* ======================= Constructores ======================= */
    // Constructor por defecto
    Metal();
    
    // Constructor con parámetros, llama al constructor de la clase padre
    Metal(int _numeroAtomico, string _nombre, string _simbolo, int _numeroMasa, vector<int> _estadosOxidacion, float _conductividadElectrica);

    /* ----------------------- Getters ----------------------- */
    float getConductividadElectrica() const;

    /* ----------------------- Setters ----------------------- */
    void setConductividadElectrica(float _conductividadElectrica);

    /* ----------------------- Métodos de Herencia ----------------------- */
    // Sobreescribe el método virtual de Elemento para añadir información específica.
    string obtenerInformacion() const override;

    /* ----------------------- Métodos ----------------------- */
    // Determina si el metal es reactivo con ácidos (lógica simple)
    bool reaccionaConAcido() const;
};

#endif