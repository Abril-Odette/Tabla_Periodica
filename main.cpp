#include <iostream>
using namespace std;

// Incluir clases
#include "elemento.h"
#include "atomo.h"
#include "molecula.h"

int main() {

    cout << "\n========== PRUEBA ELEMENTO ==========\n";

    Elemento oxigeno(8, "Oxigeno", "O");
    oxigeno.mostrarInfo();

    oxigeno.setValenciaManual(2);   // Asignar valencia manual
    cout << "Valencia manual asignada: " << oxigeno.getValencia() << endl;


    cout << "\n========== PRUEBA ATOMO ==========\n";

    Atomo atomoO(oxigeno, 16);    // Z = 8, A = 16
    atomoO.mostrarInfo();

    atomoO.setCarga(-1);          // Convertirlo en anión O⁻
    cout << "\nDespues de ajustar carga:\n";
    atomoO.mostrarInfo();


    cout << "\n========== PRUEBA DE ENLACE ENTRE ATOMOS ==========\n";

    Elemento hidrogeno(1, "Hidrogeno", "H");
    Atomo atomoH(hidrogeno, 1);

    cout << "¿O puede enlazar con H?: "
         << (atomoO.puedeEnlazarCon(atomoH) ? "Si" : "No") << endl;


    cout << "\n========== PRUEBA MOLECULA ==========\n";

    Molecula agua;
    agua.setNombre("Agua");

    agua.agregarElemento("H", 2);
    agua.agregarElemento("O", 1);

    agua.mostrarInfo();


    cout << "\n========== FIN DE LAS PRUEBAS ==========\n";

    return 0;
}