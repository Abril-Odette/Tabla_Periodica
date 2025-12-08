#  Aplicación de Balanceo y Estequiometría Química (POO Avanzada)

## Descripción General

Este proyecto es una aplicación implementada en C++ bajo el paradigma de **Programación Orientada a Objetos (POO)**. Su propósito central es modelar una parte fundamental de la química: la **estructura atómica**, la **formulación química** y la **cuantificación de reacciones** (estequiometría).

La química se basa en principios de conservación, siendo el más crucial la **Ley de Conservación de la Materia** (o Ley de Lavoisier), que establece que la materia no se crea ni se destruye, solo se transforma. El **balanceo de ecuaciones**  es la traducción matemática de esta ley. La **Estequiometría** utiliza estas proporciones balanceadas para predecir o calcular las cantidades (masas o moles) de reactivos y productos.

El proyecto busca ofrecer una herramienta modular, extensible y rigurosa que no solo permite la visualización de la información atómica, sino que también **procesa, balancea automáticamente y analiza reacciones químicas** (cálculos estequiométricos) mediante una arquitectura sólida basada en el diseño POO.

---

##  Arquitectura General y Modelo POO

La solución está construida bajo un diseño POO que separa claramente las responsabilidades en capas:

1.  **Datos Base y Herencia (El Catálogo Químico):**
    * **Elemento** (Clase Base) : Contiene la información universal del átomo (símbolo, nombre, número atómico).
    * **Metal** y **NoMetal** (Clases Derivadas): Heredan de `Elemento` e implementan propiedades específicas (`ConductividadEléctrica` para Metales y `Electronegatividad` para No Metales).
    * **TablaPeriodica** (Composición): Funciona como un repositorio central que almacena y dispensa punteros a objetos `Elemento`.

2.  **Contenedores de Datos (Estructuras Químicas):**
    * **Formula:** Compuesto químico que utiliza **Composición/Agregación** al contener una lista de punteros a `Elemento` y sus respectivos subíndices. Es capaz de calcular su propia Masa Molar.
    * **Reaccion:** Contiene dos listas de objetos `Formula` (Reactivos y Productos). Modificación clave: Su estructura fue modificada para manejar la reacción como una **ecuación química dinámica**.

3.  **Módulos de Servicio (Lógica de los cálculos):**
    * **Balanceador:** Contiene la lógica matemática (método algebraico) para calcular los coeficientes estequiométricos enteros mínimos de una `Reaccion`.
    * **Estequiometria:** Contiene los métodos para realizar cálculos de conversión de masa a masa o masa a moles, utilizando los coeficientes de una reacción **balanceada**.

---

##  Funcionalidad Implementada

El usuario puede ejecutar tareas típicas de química básica, ahora con soporte para el balanceo y cálculo avanzado:

* **Registro de Elementos:** Crea Elementos diferenciados (Metales/NoMetales).
* **Creación de Fórmulas:** Construye compuestos químicos a partir de Elementos registrados y calcula su Masa Molar.
* **Modelado de Reacciones:** Define reacciones agregando Fórmulas como Reactivos y Productos.
* **Balanceo Automático:** Balancea ecuaciones químicas utilizando el método algebraico para determinar los coeficientes estequiométricos correctos.
* **Cálculos Estequiométricos (Masa-Masa):** Realiza cálculos de gramos de una sustancia basados en la masa conocida de otra sustancia participante en la reacción balanceada.
* **Modo Interactivo (CLI):** Un *main* dinámico que permite registrar elementos y fórmulas, balancear cualquier reacción y ejecutar cálculos.

---

##  Pruebas de Funcionalidad Inicial (Modo Interactivo)

Para verificar el funcionamiento del balanceo y la estequiometría, se recomienda registrar los elementos y fórmulas necesarios para la reacción de la **Fotosíntesis**.

Sigue los siguientes pasos en la **Opción 2: INSTANCIA INTERACTIVA**.

### Paso 1: Registrar Elementos Base (Opción 1 del menú Interactivo)

| Símbolo | Nombre | Z | A | Tipo | Dato Adicional |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **C** | Carbono | 6 | 12 | No Metal | Electronegatividad: 2.55 |
| **H** | Hidrógeno | 1 | 1 | No Metal | Electronegatividad: 2.20 |
| **O** | Oxígeno | 8 | 16 | No Metal | Electronegatividad: 3.44 |

### Paso 2: Registrar Fórmulas (Opción 2 del menú Interactivo)

| Nombre de la Fórmula | Fórmula Química | Elemento + Subíndice |
| :---: | :---: | :---: |
| **Dióxido de Carbono** | $\text{CO}_2$ | C: 1, O: 2 |
| **Agua** | $\text{H}_2\text{O}$ | H: 2, O: 1 |
| **Glucosa** | $\text{C}_6\text{H}_{12}\text{O}_6$ | C: 6, H: 12, O: 6 |
| **Dioxígeno** | $\text{O}_2$ | O: 2 |

### Paso 3: Balancear la Reacción (Opción 3 del menú Interactivo)

1. **Nombre de la Reacción:** Fotosíntesis
2. **Reactivos (Entrada):**
    * Ingrese el nombre: **Dióxido de Carbono**
    * Ingrese el nombre: **Agua**
    * Ingrese el nombre: **fin**
3. **Productos (Entrada):**
    * Ingrese el nombre: **Glucosa**
    * Ingrese el nombre: **Dioxígeno**
    * Ingrese el nombre: **fin**
4. **Resultado esperado:** El sistema deberá mostrar la reacción balanceada: $6\text{CO}_2 + 6\text{H}_2\text{O} \to 1\text{C}_6\text{H}_{12}\text{O}_6 + 6\text{O}_2$.

### Paso 4: Calcular Estequiometría (Opción 4 del menú Interactivo)

1. **Repetir Pasos de Balanceo (mismos reactivos/productos).**
2. **Fórmula de PARTIDA:** Dióxido de Carbono
3. **Masa en gramos de la PARTIDA (Ejemplo):** 264.0 (g)
4. **Fórmula de LLEGADA:** Glucosa
5. **Resultado esperado:**
    * $\text{Masa Molar Dióxido de Carbono} \approx 44 \text{ g/mol}$
    * $264.0 \text{ g} / 44 \text{ g/mol} = 6 \text{ moles de } \text{CO}_2$
    * Por la estequiometría ($6:1$), se producirá $1 \text{ mol de Glucosa}$.
    * $\text{Masa Molar Glucosa} \approx 180 \text{ g/mol}$
    * $\text{Masa de Glucosa} = 1 \text{ mol} \times 180 \text{ g/mol} = 180 \text{ g}$.
    * **El programa debe retornar:** $180.0 \text{ g de Glucosa}$.

***

##  Limitaciones y Alcance Futuro

El proyecto cumple satisfactoriamente con todos los requerimientos funcionales esperados (registro, formulación, balanceo y estequiometría).

**Alcance de la Interacción:**
* El **módulo principal de interacción con el usuario (main)** actualmente implementado a través de la Consola (CLI) es completamente **funcional y estable**.
* **Limitación actual:** Su interfaz es básica. Se reconoce que la **experiencia de usuario** podría diseñarse de forma significativamente más cómoda e intuitiva (por ejemplo, con una interfaz gráfica o un *parser* más sofisticado para la entrada de reacciones).
* **Posible mejora futura:** Se podría implementar el uso de **archivos** o una pequeña base de datos para almacenar permanentemente los registros de Elementos, Fórmulas y Reacciones, en lugar de depender únicamente de la memoria volátil del programa.

---

##  Correcciones y Modificaciones Clave

Se realizaron varias correcciones y modificaciones fundamentales para la robustez del sistema y la mejora de la fidelidad del modelo.
La evidencias de las cuales se solicita una reevalación están planteadas en el archivo *Correcciones.txt*

### 1. Modificaciones al Modelo POO y Estructura

| Cambio/Corrección | Descripción | Sub-Competencia | Indicador | Ubicación |
| :--- | :--- | :--- | :--- | :--- |
| **Diseño de Clase Reaccion** | Se modificó la estructura interna de `Reaccion` para manejar los reactivos y productos como colecciones (vectores de punteros a `Formula` o estructuras similares) en lugar de propiedades directas. Esto elimina el límite rígido de dos reactivos/dos productos y mejora la modularidad. | **Implementa SICT030A** | Implemento composición (o agregación) siguiendo mi diagrama de clases (3) | Clases `Reaccion.h`/`.cpp` |
| **Balanceo y Estequiometría** | Se verificó que las clases `Balanceador` y `Estequiometria` operen como **clases de Servicio**, desacoplando la lógica matemática del modelo de datos (`Formula`, `Reaccion`). Solo reciben la instancia de `Reaccion` y los datos necesarios, no tienen estado propio. | **Implementa SICT030A** | Implemento composición (o agregación) siguiendo mi diagrama de clases (3) | Clases `Balanceador.h`/`.cpp` y `Estequiometria.h`/`.cpp` |
| **Herencia Aplicada** | Se confirmó que la relación de herencia `Elemento -> Metal/NoMetal` se utiliza correctamente para acceder a la funcionalidad base mientras se implementan las especializaciones de cada tipo de elemento. | **Implementa SICT030A** | Implemento herencia de manera correcta y útil (3) | Clases `Metal.h`/`.cpp`, `NoMetal.h`/`.cpp` |

### 2. Estabilidad de Entrada de Datos (Input Buffer)

| Cambio/Corrección | Descripción | Sub-Competencia | Indicador | Ubicación |
| :--- | :--- | :--- | :--- | :--- |
| **Limpieza de Buffer** | Se implementó y verificó la función `LimpiarEntrada()` y el uso de `cin.ignore(numeric_limits<streamsize>::max(), '\n');` de forma sistemática y absoluta **después de cada lectura numérica** (`cin >> int/float`) que fuera seguida por una lectura de línea completa (`getline(cin, ...)`). | **Implementa SICT030A** | Codifico métodos y atributos de clase correctamente (1) | Funciones interactivas en `main.cpp` (`CrearElementoInteractivo`, `CrearFormulaInteractivo`, `CalcularEstequiometriaInteractivo`) |

### 3. Estándares de Código y Compilación

| Cambio/Corrección | Descripción | Sub-Competencia | Indicador | Ubicación |
| :--- | :--- | :--- | :--- | :--- |
| **Estándares (Nombres)** | Se realizó una revisión para asegurar que los nombres de variables (camelCase), funciones/métodos (camelCase) y clases (PascalCase) sigan los estándares definidos. | **Estándares SICT401A** | Sigo estándares en todo mi código fuente (0) | Archivos `.h` y `.cpp` (General) |
| **Especificación de Compilación** | Se actualizó la instrucción de compilación para incluir **todos** los archivos de implementación (`.cpp`) necesarios en la línea de comandos de `g++`. | **Estándares SICT401A** | Guardo correctamente los avances en commits durante la materia (1) | Documentación (`README.md`) |

## Instrucción de Compilación (Consola):

Para compilar el proyecto en su totalidad, asegurese de tener todos los archivos descargados, tener todos los cambios guardados y estar en el directorio adecuado, luego use el siguiente comando:
g++ main.cpp elemento.cpp Metal.cpp NoMetal.cpp Tablaperiodica.cpp Formula.cpp Reaccion.cpp Balanceador.cpp Estequiometria.cpp -o ProyectoQuimica

Y luego ejecute:
./ProyectoQuimica

Una vez hecho esto puede acceder a la prueba DEMO del proyecto que le permite comprobar la creación de objetos o interactuar con el programa y crear sus propios objetos. 
