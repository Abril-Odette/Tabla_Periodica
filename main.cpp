#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits> 

#include "elemento.h"
#include "Metal.h"
#include "NoMetal.h"
#include "Tablaperiodica.h"
#include "Formula.h"
#include "Reaccion.h"
#include "Balanceador.h"
#include "Estequiometria.h"

using namespace std;

// ========================== VARIABLES GLOBALES ======================

// Mapa para almacenar los elementos creados por el usuario, usando el símbolo como clave.
map<string, Elemento*> elementosRegistrados; 
// Vector para almacenar las fórmulas creadas por el usuario.
vector<Formula*> formulasRegistradas;

// ========================== FUNCIONES AUXILIARES ====================

// Función auxiliar para limpiar la entrada después de dar un enter.
void LimpiarEntrada() {
    if (cin.fail() || cin.peek() != '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Función auxiliar para buscar y retornar un puntero a una fórmula por su nombre completo.
Formula* BuscarFormula(const string& nombreFormula) {
    for (size_t i = 0; i < formulasRegistradas.size(); ++i) {
        Formula* formulaActual = formulasRegistradas[i];
        if (formulaActual->getNombre() == nombreFormula) {
            return formulaActual;
        }
    }
    return nullptr;
}

// ========================== MODO DEMOSTRACIÓN =======================

// Función que ejecuta una demostración preconfigurada de la creación de objetos,
// el balanceo de una reacción (Combustión de Metano) y un cálculo estequiométrico.
void EjecutarDemo() {
    cout << "\n======================================================\n";
    cout << "           MODO DEMOSTRACIÓN DEL PROYECTO         \n";
    cout << "======================================================\n";

    TablaPeriodica tabla;
    Elemento* hidrogenoPtr = tabla.buscarElemento("H"); 
    Elemento* oxigenoPtr = tabla.buscarElemento("O");
    Elemento* carbonoPtr = tabla.buscarElemento("C");
    Elemento* sodioPtr = tabla.buscarElemento("Na");
    
    cout << "\n--- ELEMENTOS BASE ---\n";
    if (sodioPtr) cout << "Sodio (Metal): " << sodioPtr->obtenerInformacion() << "\n";
    if (hidrogenoPtr) cout << "Hidrogeno (NoMetal): " << hidrogenoPtr->obtenerInformacion() << "\n";

    cout << "\n--- FORMULAS QUIMICAS ---\n";
    
    Formula metano("Metano");
    metano.agregarElemento(carbonoPtr, 1); 
    metano.agregarElemento(hidrogenoPtr, 4); 

    Formula dioxigeno("Dioxigeno");
    dioxigeno.agregarElemento(oxigenoPtr, 2); 

    Formula dioxidoCarbono("Dioxido de Carbono");
    dioxidoCarbono.agregarElemento(carbonoPtr, 1); 
    dioxidoCarbono.agregarElemento(oxigenoPtr, 2);
    
    Formula agua("Agua");
    agua.agregarElemento(hidrogenoPtr, 2); 
    agua.agregarElemento(oxigenoPtr, 1);
    
    agua.mostrarInfo();
    
    cout << "\n--- REACCION: COMBUSTION DE METANO ---\n";

    Reaccion combustionMetano("Combustion de Metano");
    combustionMetano.agregarReactivo(&metano, 1);
    combustionMetano.agregarReactivo(&dioxigeno, 1);
    combustionMetano.agregarProducto(&dioxidoCarbono, 1);
    combustionMetano.agregarProducto(&agua, 1);

    cout << "-- Reaccion Inicial (Desbalanceada) --\n";
    combustionMetano.mostrarReaccion();

    Balanceador balanceador;
    cout << "\n-- Proceso de Balanceo (Metodo Algebraico) --\n";
    
    bool resultadoBalanceo = balanceador.balancear(&combustionMetano);

    if (resultadoBalanceo) {
        cout << "\nBalanceo Exitoso! Reaccion final:\n";
        combustionMetano.mostrarReaccion();
    } else {
        cout << "\nBalanceo Fallido.\n";
    }

    Estequiometria estequiometria;
    float gramosPartidaMetano = 16.0f;

    cout << "\n-- Calculos Estequiometricos --\n";

    cout << "-> Calculemos los gramos de Agua producidos a partir de " << gramosPartidaMetano << "g de Metano.\n";

    float gramosAguaProducida = estequiometria.calcularMasaRelacionada(&combustionMetano, gramosPartidaMetano, &metano, &agua);
    
    cout << "Resultado: Se producen " << gramosAguaProducida << "g de Agua.\n";
}

// ========================= FUNCIONES INTERACTIVAS ===================

// Permite al usuario ingresar los datos para crear y registrar un nuevo Elemento (Metal o NoMetal).
void CrearElementoInteractivo() {
    string simboloElemento, nombreElemento;
    int numeroAtomico, masaAtomica, opcionTipo;
    float conductividadElectrica, electronegatividad;

    cout << "\n--- REGISTRAR NUEVO ELEMENTO ---\n";
    cout << "Nota: El Simbolo (ej. H) se usara posteriormente para crear Formulas.\n"; 
    
    cout << "Simbolo (Ej: H, O): ";
    cin >> simboloElemento;
    
    if (elementosRegistrados.count(simboloElemento)) {
        cout << "Error: El elemento '" << simboloElemento << "' ya esta registrado.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    cout << "Nombre: ";
    getline(cin, nombreElemento);

    cout << "Numero Atomico (Z): ";
    cin >> numeroAtomico;
    if (cin.fail()) {
        cin.clear();
        LimpiarEntrada();
        cout << "Error: Entrada de Numero Atomico invalida. Vuelva a intentar.\n";
        return;
    }
    LimpiarEntrada();

    cout << "Masa Atomica (A, entero): ";
    cin >> masaAtomica;
    if (cin.fail()) {
        cin.clear();
        LimpiarEntrada();
        cout << "Error: Entrada de Masa Atomica invalida. Vuelva a intentar.\n";
        return;
    }
    LimpiarEntrada();

    cout << "Tipo:\n 1) Metal\n 2) No Metal\nOpcion: ";
    cin >> opcionTipo;
    if (cin.fail() || (opcionTipo != 1 && opcionTipo != 2)) {
        cin.clear();
        LimpiarEntrada();
        cout << "Error: Opcion de tipo invalida. Vuelva a intentar.\n";
        return;
    }
    LimpiarEntrada();

    Elemento* nuevoElemento = nullptr;
    vector<int> estadosOxidacion;
    estadosOxidacion.push_back(1);
    estadosOxidacion.push_back(2);

    if (opcionTipo == 1) { // Metal
        cout << "Conductividad Electrica: ";
        cin >> conductividadElectrica;
        if (cin.fail()) {
            cin.clear();
            LimpiarEntrada();
            cout << "Error: Entrada de Conductividad Electrica invalida. Vuelva a intentar.\n";
            return;
        }
        LimpiarEntrada();
        nuevoElemento = new Metal(numeroAtomico, nombreElemento, simboloElemento, masaAtomica, estadosOxidacion, conductividadElectrica);
    } else if (opcionTipo == 2) { // No Metal
        cout << "Electronegatividad: ";
        cin >> electronegatividad;
        if (cin.fail()) {
            cin.clear();
            LimpiarEntrada();
            cout << "Error: Entrada de Electronegatividad invalida. Vuelva a intentar.\n";
            return;
        }
        LimpiarEntrada();
        nuevoElemento = new NoMetal(numeroAtomico, nombreElemento, simboloElemento, masaAtomica, estadosOxidacion, electronegatividad);
    } else {
        cout << "Tipo invalido.\n";
        return;
    }

    elementosRegistrados[simboloElemento] = nuevoElemento;
    cout << "\nElemento '" << nombreElemento << "' registrado.\n";
}

// Permite al usuario crear y registrar una nueva Fórmula (compuesto) a partir de los Elementos registrados.
void CrearFormulaInteractivo() {
    string nombreCompuesto, simboloElemento;
    int cantidadSubindice, opcionContinuar;
    
    cout << "\n--- REGISTRAR NUEVA FORMULA ---\n";
    cout << "Nota: El Nombre de la Formula (ej. Agua) sera la clave de busqueda en Reacciones y Estequiometria.\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nombre de la Formula (Ej: Agua, Dioxido de Carbono): ";
    getline(cin, nombreCompuesto); 
    if (nombreCompuesto.empty()) {
        cout << "Error: El nombre de la formula no puede estar vacio.\n";
        return;
    }

    Formula* nuevaFormula = new Formula(nombreCompuesto);

    do {
        cout << "Simbolo del Elemento (Ej: H, O): ";
        cin >> simboloElemento;
        LimpiarEntrada();
        
        if (cin.fail()) { 
            cin.clear();
            cout << "Error en la entrada del simbolo. Abortando registro de formula.\n";
            delete nuevaFormula;
            return;
        }

        if (elementosRegistrados.count(simboloElemento) == 0) {
            cout << "Error: El elemento '" << simboloElemento << "' no esta registrado. Registrelo primero (Opcion 1).\n";
            continue;
        }

        cout << "Cantidad (Subindice): ";
        cin >> cantidadSubindice;
        if (cin.fail()) {
            cin.clear();
            LimpiarEntrada();
            cout << "Error: Entrada de Cantidad (Subindice) invalida. Abortando registro de formula.\n";
            delete nuevaFormula;
            return;
        }
        
        LimpiarEntrada();

        Elemento* elementoPtr = elementosRegistrados[simboloElemento];
        nuevaFormula->agregarElemento(elementoPtr, cantidadSubindice);

        cout << "Formula parcial: " << nuevaFormula->getFormula() << endl;
        cout << "¿Agregar otro elemento? (1: Si, 0: No): ";
        cin >> opcionContinuar;
        if (cin.fail() || (opcionContinuar != 1 && opcionContinuar != 0)) {
            cin.clear();
            LimpiarEntrada();
            cout << "Error: Opcion invalida. Finalizando registro de formula.\n";
            opcionContinuar = 0; 
        }
        LimpiarEntrada();

    } while (opcionContinuar != 0);

    nuevaFormula->calcularMasaMolar(); 
    formulasRegistradas.push_back(nuevaFormula);
    cout << "\nFormula '" << nuevaFormula->getFormula() << "' registrada con el nombre: '" << nuevaFormula->getNombre() << "'.\n";
    nuevaFormula->mostrarInfo();
}

// Muestra en consola la lista de todos los elementos químicos que han sido registrados por el usuario.
void MostrarElementosRegistrados() {
    cout << "\n--- REGISTRO DE ELEMENTOS ---\n";
    if (elementosRegistrados.empty()) {
        cout << "No hay elementos registrados (Use la Opcion 1 para crear uno).\n";
        return;
    }

    cout << "Total de elementos registrados: " << elementosRegistrados.size() << "\n";
    cout << "------------------------------------------\n";

    for (const auto& par : elementosRegistrados) {
        cout << "Simbolo: " << par.first << " | Nombre: " << par.second->getNombre() << "\n";
        cout << par.second->obtenerInformacion() << "\n";
        cout << "--- * ---\n";
    }
}

// Permite al usuario ingresar las Fórmulas (Reactivos y Productos) de una Reacción,
// y luego utiliza la clase Balanceador para intentar balancearla automáticamente.
void BalancearReaccionInteractivo(Reaccion& reaccionActual) {
    if (formulasRegistradas.size() == 0) {
        cout << "Error: Debe registrar Formulas primero (Opcion 2).\n";
        return;
    }

    string nombreReaccion; 
    string nombreFormula; 

    cout << "\n--- BALANCEO DE REACCIONES ---\n";
    cout << "Nombre de la Reaccion: ";
    LimpiarEntrada();
    getline(cin, nombreReaccion);
    reaccionActual.setNombre(nombreReaccion);

    cout << "\n--- LISTADO DE FORMULAS DISPONIBLES ---\n";
    if (formulasRegistradas.empty()) {
        cout << "No hay formulas disponibles. Registre una primero.\n";
        return;
    } else {
        cout << "Nombres disponibles (Clave para la entrada): ";
        for (size_t i = 0; i < formulasRegistradas.size(); ++i) {
            cout << "'" << formulasRegistradas[i]->getNombre() << "'";
            if (i < formulasRegistradas.size() - 1) {
                cout << ", ";
            }
        }
        cout << "\n-----------------------------------------\n";
    }

    // --- 1. Entrada de Reactivos ---
    cout << "\n--- REACTIVOS (Entrada) ---\n";
    cout << "Instruccion: Ingrese el NOMBRE COMPLETO de CADA Formula Reactiva, una a la vez.\n";
    cout << "(Ingrese 'fin' para terminar la lista de reactivos)\n";
    while (true) {
        cout << "Nombre de Formula Reactiva (o 'fin'): ";
        getline(cin, nombreFormula);

        if (nombreFormula.empty()) {
            cout << "Advertencia: El nombre no puede estar vacio. Intente de nuevo.\n";
            continue; 
        }
        
        if (nombreFormula == "fin") break;

        Formula* formulaPtr = BuscarFormula(nombreFormula);
        if (formulaPtr) {
            reaccionActual.agregarReactivo(formulaPtr, 1);
        } else {
            cout << "Error: Formula '" << nombreFormula << "' no encontrada. Verifique el nombre completo.\n";
        }
    }

    // --- 2. Entrada de Productos ---
    cout << "\n--- PRODUCTOS (Entrada) ---\n";
    cout << "Instruccion: Ingrese el NOMBRE COMPLETO de CADA Formula Producto, una a la vez.\n";
    cout << "(Ingrese 'fin' para terminar la lista de productos)\n";
    while (true) {
        cout << "Nombre de Formula Producto (o 'fin'): ";
        getline(cin, nombreFormula);
        
        if (nombreFormula.empty()) {
            cout << "Advertencia: El nombre no puede estar vacio. Intente de nuevo.\n";
            continue; 
        }

        if (nombreFormula == "fin") break;

        Formula* formulaPtr = BuscarFormula(nombreFormula);
        if (formulaPtr) {
            reaccionActual.agregarProducto(formulaPtr, 1);
        } else {
            cout << "Error: Formula '" << nombreFormula << "' no encontrada. Verifique el nombre completo.\n";
        }
    }
    
    // --- 3. Proceso de Balanceo ---
    cout << "\n-- Reaccion a Balancear --\n";
    reaccionActual.mostrarReaccion();

    Balanceador balanceador;
    cout << "\nIniciando Balanceo Algebraico...\n";
    bool resultadoBalanceo = balanceador.balancear(&reaccionActual);
    
    if (resultadoBalanceo) {
        cout << "\nBalanceo Exitoso! Reaccion final:\n";
        reaccionActual.mostrarReaccion();
    } else {
        cout << "\nBalanceo Fallido. Verifique la sintaxis o si la reaccion es posible.\n";
    }
}

// Permite al usuario realizar cálculos estequiométricos (masa-masa)
// a partir de una reacción previamente balanceada.
void CalcularEstequiometriaInteractivo() {
    if (formulasRegistradas.size() == 0) {
        cout << "Error: Debe registrar Formulas primero (Opcion 2).\n";
        return;
    }

    cout << "\n--- CALCULOS ESTEQUIOMETRICOS ---\n";
    cout << "Paso 1: Primero se creara y balanceara la reaccion a utilizar.\n";
    Reaccion reaccionCalculo;
    BalancearReaccionInteractivo(reaccionCalculo);

    if (reaccionCalculo.esBalanceada() == false) {
        cout << "\nNo se puede realizar estequiometria con una reaccion desbalanceada. Abortando calculo.\n";
        return;
    }

    // --- 1. Definir los términos ---
    string nombreFormulaPartida, nombreFormulaLlegada;
    float masaPartidaGramos;

    cout << "\n--- DEFINIR CALCULO ESTEQUIOMETRICO (Paso 2) ---\n";
    cout << "Instruccion: Use el NOMBRE COMPLETO de la formula. Debe ser una formula que participe en la reaccion balanceada.\n";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Formula de PARTIDA (masa conocida): ";
    getline(cin, nombreFormulaPartida);
    if (nombreFormulaPartida.empty()) { cout << "Error de entrada.\n"; return; }

    cout << "Masa en gramos de la Formula PARTIDA: ";
    cin >> masaPartidaGramos;
    if (cin.fail()) { 
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error de entrada.\n"; 
        return; 
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Formula de LLEGADA (masa a calcular): ";
    getline(cin, nombreFormulaLlegada);
    if (nombreFormulaLlegada.empty()) { cout << "Error de entrada.\n"; return; }

    Formula* formulaPartidaPtr = BuscarFormula(nombreFormulaPartida);
    Formula* formulaLlegadaPtr = BuscarFormula(nombreFormulaLlegada);

    if (formulaPartidaPtr == nullptr || formulaLlegadaPtr == nullptr) {
        cout << "Error: Formulas de partida o llegada no encontradas en el registro.\n";
        return;
    }
    
    // --- 2. Realizar el Cálculo ---
    Estequiometria estequiometria;
    
    cout << "\nCalculando masa de " << formulaLlegadaPtr->getFormula() << "...\n";
    
    float masaLlegadaGramos = estequiometria.calcularMasaRelacionada(&reaccionCalculo, masaPartidaGramos, formulaPartidaPtr, formulaLlegadaPtr);
    
    cout << "\n======================================================\n";
    cout << "             RESULTADO ESTEQUIOMÉTRICO\n";
    cout << "------------------------------------------------------\n";
    cout << "Partida: " << masaPartidaGramos << "g de " << formulaPartidaPtr->getFormula() << endl;
    cout << "Llegada: " << masaLlegadaGramos << "g de " << formulaLlegadaPtr->getFormula() << endl;
    cout << "======================================================\n";
}

// Menú principal del modo interactiva.
void MenuInteractivo() {
    int opcionMenu;

    do {
        cout << "\n======================================================\n";
        cout << "           INSTANCIA INTERACTIVA (MENU)         \n";
        cout << "======================================================\n";
        cout << "Registros: " << elementosRegistrados.size() << " Elementos | " 
             << formulasRegistradas.size() << " Formulas\n";
        cout << "1. Registrar Elemento\n";
        cout << "2. Registrar Formula\n";
        cout << "3. Balancear Reaccion\n";
        cout << "4. Calcular Estequiometria\n";
        cout << "5. Mostrar Fórmulas Registradas\n"; 
        cout << "6. Mostrar Elementos Registrados\n"; 
        cout << "0. Volver al Menu Principal\n";
        cout << "Opcion: ";
        
        cin >> opcionMenu;
        
        if (cin.fail()) {
            cin.clear();
            LimpiarEntrada();
            cout << "Error: Opcion de menu invalida. Intente de nuevo con un numero.\n";
            opcionMenu = -1; 
            continue;
        }
        
        LimpiarEntrada();

        switch (opcionMenu) {
            case 1:
                CrearElementoInteractivo();
                break;
            case 2:
                CrearFormulaInteractivo();
                break;
            case 3:
                { Reaccion reaccionTemporal; BalancearReaccionInteractivo(reaccionTemporal); }
                break;
            case 4:
                CalcularEstequiometriaInteractivo();
                break;
            case 5:
                cout << "\n--- REGISTRO DE FÓRMULAS ---\n";
                if (formulasRegistradas.size() == 0) {
                    cout << "No hay formulas registradas.\n";
                } else {
                    for (size_t i = 0; i < formulasRegistradas.size(); ++i) {
                        formulasRegistradas[i]->mostrarInfo();
                    }
                }
                break;
            case 6:
                MostrarElementosRegistrados();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcionMenu != 0);
}

// ============================= MAIN PRINCIPAL =======================

// Función principal que presenta el menú inicial y gestiona el flujo del programa.
int main() {
    int opcionPrincipal;
    
    cout << "\n======================================================\n";
    cout << "    APLICACION DE BALANCEO Y ESTEQUIOMETRIA QUIMICA    \n";
    cout << "======================================================\n";

    do {
        cout << "\nSeleccione el modo de operacion:\n";
        cout << "1. DEMOSTRACION (Verificacion del Modelo POO)\n";
        cout << "2. INSTANCIA INTERACTIVA (Datos de Usuario)\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        
        cin >> opcionPrincipal;
        
        if (cin.fail()) {
            cin.clear();
            LimpiarEntrada();
            cout << "Error: Opcion de menu invalida. Intente de nuevo con un numero.\n";
            opcionPrincipal = -1; 
            continue;
        }
        
        LimpiarEntrada();

        switch (opcionPrincipal) {
            case 1:
                EjecutarDemo();
                break;
            case 2:
                MenuInteractivo();
                break;
            case 0:
                cout << "Gracias por usar el simulador. Saliendo...\n";
                for (auto pair : elementosRegistrados) {
                    delete pair.second;
                }
                for (size_t i = 0; i < formulasRegistradas.size(); ++i) {
                    delete formulasRegistradas[i];
                }
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcionPrincipal != 0);

    return 0;
}