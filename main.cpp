#include <iostream>
#include <vector>
#include <string>

#include "elemento.h"
#include "metal.h"
#include "nometal.h"
#include "tablaperiodica.h"
#include "formula.h"
#include "reaccion.h"
#include "balanceador.h"
#include "estequiometria.h"

using namespace std;

int main() {
    
    // --- 1. INICIALIZACION Y DATOS BASE (Herencia y Composicion) ---
    cout << "\n========== PRUEBA 1: DATOS BASE Y HERENCIA ==========\n";

    // Creamos la Tabla Periodica, que inicializa y contiene los Elementos
    TablaPeriodica tabla;

    // Obtenemos los punteros de los Elementos desde la Tabla (Composicion)
    Elemento* hidrogeno = tabla.buscarElemento("H");
    Elemento* oxigeno = tabla.buscarElemento("O");
    
    if (hidrogeno) {
        cout << "Elemento H (NoMetal) cargado:\n" << hidrogeno->obtenerInformacion() << "\n\n";
    }

    // --- 2. CREACION DE FORMULAS (Agregacion y Calculo) ---
    cout << "========== PRUEBA 2: AGREGACION Y FORMULAS ==========\n";
    
    // a) Formula Reactivo 1: H2
    Formula h2("Dihidrogeno");
    h2.agregarElemento(hidrogeno, 2); 

    // b) Formula Reactivo 2: O2
    Formula o2("Dioxigeno");
    o2.agregarElemento(oxigeno, 2); 

    // c) Formula Producto 1: H2O
    Formula agua("Agua");
    agua.agregarElemento(hidrogeno, 2); 
    agua.agregarElemento(oxigeno, 1);
    
    agua.mostrarInfo();
    
    // --- 3. REACCION, BALANCEO Y SERVICIOS (Agregacion y Servicio) ---
    cout << "========== PRUEBA 3: REACCION Y SERVICIOS ==========\n";

    // 3.1. Crear la Reaccion (Agregacion de Formulas)
    Reaccion reaccionAgua("Formacion de Agua");

    // Agregamos las Fórmulas con coeficientes iniciales (1, 1, 1)
    reaccionAgua.agregarReactivo(&h2, 1);
    reaccionAgua.agregarReactivo(&o2, 1);
    reaccionAgua.agregarProducto(&agua, 1);

    cout << "-- Reaccion Inicial --\n";
    reaccionAgua.mostrarReaccion();

    // 3.2. Demostración del Balanceador
    Balanceador balanceador;
    cout << "\n-- Proceso de Balanceo --\n";
    
    // La funcion balancear debe ajustar los coeficientes de la Reaccion
    bool resultadoBalanceo = balanceador.balancear(&reaccionAgua);

    if (resultadoBalanceo) {
        cout << "Balanceo Exitoso! Reaccion final (2 H2 + 1 O2 -> 2 H2O):\n";
        reaccionAgua.mostrarReaccion(); 
    } else {
        cout << "Balanceo Fallido.\n";
    }

    // 3.3. Demostración de Estequiometría
    Estequiometria estequiometria;
    float gramosInicialesH2 = 4.0f; 
    
    cout << "\n-- Calculos Estequiometricos --\n";

    // Calcular gramos de Agua producidos (usando la reacción balanceada)
    float gramosAguaProducida = estequiometria.calcularGramosProducto(&reaccionAgua, gramosInicialesH2);
    
    cout << "Gramos de H2O producidos a partir de " << gramosInicialesH2 << "g de H2: " << gramosAguaProducida << "g\n";

    return 0;
}