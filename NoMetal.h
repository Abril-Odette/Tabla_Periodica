/*
    Descripción:
    Clase NoMetal, hereda de Elemento.
    - Especializa a Elemento añadiendo la propiedad de electronegatividad.
    - Contiene un método para calcular un punto de ebullición simplificado.

    Autor: [Abril Odette Jiménez Sánchez - A01715095]
    Fecha de creación: [03/12/2025]
    Última modificación: [04/122025]
*/
#ifndef NOMETAL_H
#define NOMETAL_H

#include "elemento.h"

class NoMetal : public Elemento {

private:
    float electronegatividad;

public:
    /* ======================= Constructores ======================= */
    NoMetal();
    NoMetal(int _numeroAtomico, string _nombre, string _simbolo, int _numeroMasa, vector<int> _estadosOxidacion, float _electronegatividad);

    /* ----------------------- Getters ----------------------- */
    float getElectronegatividad() const;

    /* ----------------------- Setters ----------------------- */
    void setElectronegatividad(float _electronegatividad);

    /* ----------------------- Métodos de Herencia ----------------------- */
    // Sobreescribe el método virtual de Elemento.
    string obtenerInformacion() const override;

    /* ----------------------- Métodos ----------------------- */
    // Calcula un punto de ebullición.
    float calcularPuntoEbullicion() const;
};


#endif
