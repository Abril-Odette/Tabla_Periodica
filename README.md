# Motor de Tabla Periódica 

# Descripción general

Este proyecto es una implementación en C++ bajo el paradigma de Programación Orientada a Objetos, cuyo propósito es modelar una parte esencial de la química general mediante una tabla periódica, con los elementos, atómos y moléculas como clases y relaciones entre objetos. Con un carácter modular y extensible, su objetivo no es solo mostrar información, sino procesarla y automatizar tareas de análisis químico a un nivel introductorio.

# Funcionalidad
El usuario puede ejecutar tareas típicas de química básica tales como:
- Registro de Elementos: La Tabla Periódica centraliza la carga y gestión de todos los elementos (Metal, NoMetal).
- Clasificación y Herencia: Consulta de elementos especializados por tipo (Metal, NoMetal), demostrando Polimorfismo.
- Creación de Fórmulas: Construcción de compuestos químicos (Formula) mediante la Agregación de elementos.
- Cálculo Básico: Obtención de Masa Molar de cualquier compuesto creado.
- Modelado de Reacciones: Creación de ecuaciones químicas (Reaccion) mediante la Agregación de las fórmulas.
- Servicios de Lógica: El sistema es capaz de ejecutar procesos de análisis químico para:
- Obtener el Balanceo simplificado de la ecuación química (Balanceador).
- Realizar Cálculos Estequiométricos de masa y moles entre reactivos y productos (Estequiometria).

El sistema es capaz de ejecutar procesos de análisis químico para hacer cálculos de balanceo sencillos en fórmulas químicas que comúnmente se realizan de forma manual, facilitando la comprensión de conceptos fundamentales en química. Todo meniante una presentación amigable y organizada de los resultados.

# Arquitectura general

El proyecto utiliza la Programación Orientada a Objetos (POO) para modelar el sistema químico en tres capas principales que trabajan juntas:
1. Datos Base y Herencia (El Catálogo Químico)
   Elemento: Es la clase padre. Contiene la información universal del elemento (Z, símbolo, nombre).
   Metal / NoMetal: Son las clases hijas que heredan de Elemento e implementan propiedades específicas (conductividad, electronegatividad), demostrando la Herencia y el Polimorfismo.
2. Contenedores de Datos (Estructuras Químicas)TablaPeriodica:
   Repositorio central. Almacena y es dueña de todos los objetos Elemento.
   (Composición)Formula: Crea un compuesto químico (ej. H₂O). Usa los objetos Elemento cargados en la tabla.
   (Agregación)Reaccion: Crea la ecuación química (ej. H₂ + O₂ $\rightarrow$ H₂O). Usa los objetos Formula. (Agregación)
3. Servicios (La Lógica de Cálculo)
   Balanceador: Recibe una Reaccion y calcula los coeficientes estequiométricos.
   Estequiometria: Recibe una Formula o una Reaccion y realiza cálculos de conversión de masa y moles.
   
Y cuenta con clases indispensables para el calculo del balanceo, como lo son: 
- Formula (Que utiliza moléculas)
- Reaccion (Que es una ecuación de moléculas expresadas en una fórmula)
- TerminoReaccion (Que evalua el momento en que la reacción con ayuda de una flecha indica la separación entre reactivos y productos en una reacción)
- Balanceador (Que calcula los coeficientes de las fórmmulas en la reacción)
- Estequiometría (Que haría calculos de masa y moles en una reacción)

# Modificaciones

Esta versión del proyecto refactoriza la estructura anterior para cumplir rigurosamente con los principios de POO:Eliminación de Clases Redundantes: 
- Se eliminaron las clases Atomo y Molecula.
Las funcionalidades de Atomo (gestionar carga/neutrones) y Molecula (agrupar elementos y calcular masa molar) se consolidaron en las clases Elemento (para datos atómicos) y Formula (para el compuesto agrupador). Esto evita la redundancia conceptual y el exceso de capas de abstracción, resultando en un sistema más directo y fácil de mantener.
- Implementación de Herencia: El diseño anterior carecía de herencia.
La nueva arquitectura usa la herencia Elemento -> Metal/NoMetal para representar la especialización química de manera clara, cumpliendo un requisito clave del proyecto.
- Claridad en Punteros: Se definió que la TablaPeriodica es la dueña de los Elementos (Composición), mientras que Formula y Reaccion simplemente los usan (Agregación). Esto es fundamental para el manejo de memoria en C++.
- Desacoplamiento (Servicios): Las clases de cálculo Balanceador y Estequiometria se implementaron como clases de Servicio (sin atributos propios). Esto demuestra el principio de bajo acoplamiento, ya que solo reciben y procesan los objetos de datos necesarios, resultando en un diseño POO superior y más mantenible.
- 
# Alcance

Este proyecto está diseñado para ser completado en un periodo corto (≈ 3 semanas), pero con una arquitectura sólida que permite posibles extensiones futuras:
- estructura de Lewis automática
- geometría molecular VSEPR
- balanceo de ecuaciones químicas
- cargas formales
- estequiometría
- representación gráfica
- base de datos completa de elementos
  
# Consideraciones:
Requisitos para compilar: 
g++ main.cpp elemento.cpp metal.cpp nometal.cpp tablaperiodica.cpp formula.cpp reaccion.cpp balanceador.cpp estequiometria.cpp -o tablaperiodica

Forma de correr:
./tablaperiodica

Por el moemnto hacen falta varias revisiones en cuanto a la fidelidad química de varios métodos para que la información calculada sea más fiel con la realidad.
