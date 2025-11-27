# Motor de Tabla Periódica 

# Descripción general

Este proyecto es una implementación en C++ bajo el paradigma de Programación Orientada a Objetos, cuyo propósito es modelar una parte esencial de la química general mediante una tabla periódica, con los elementos, atómos y moléculas como clases y relaciones entre objetos. Con un carácter modular y extensible, su objetivo no es solo mostrar información, sino procesarla y automatizar tareas de análisis químico a un nivel introductorio.

# Funcionalidad
El usuario puede ejecutar tareas típicas de química básica tales como:
- Registro de Elementos, átomos y moléculas
- Consulta y clasificación de elementos 
- Creación de moléculas simples a partir de átomos
- Registro de fórmulas básicas a traves de moléculas
- Obtener el balanceo de la fórmula

El sistema es capaz de ejecutar procesos de análisis químico para hacer cálculos de balanceo sencillos en fórmulas químicas que comúnmente se realizan de forma manual, facilitando la comprensión de conceptos fundamentales en química. Todo meniante una presentación amigable y organizada de los resultados.

# Arquitectura general

El proyecto se organiza alrededor de tres clases principales:

- Elemento
  Representa la información universal de un elemento químico:
  - número atómico
  - símbolo
  - nombre
  - masa atómica
  - electronegatividad
  - tipo (metal, no metal, gas noble, etc.)
  - valencia aproximada
(Esta clase funciona como una mini base de datos interna)

- Atomo
  Instancia derivada de un elemento, utilizada para formar moléculas:
  - referencia al elemento base
  - carga
  - electronegatividad

- Molecula
  Conjunto de elementos que:
  - almacena una estructura molecular
  - calcula propiedades (masa molar, etc)

Estas clases se integran mediante composición y agregación, permitiendo construir moléculas a partir de elementos y extender el sistema.

Y cuenta con clases indispensables para el calculo del balanceo, como lo son: 
- Formula (Que utiliza moléculas)
- Reaccion (Que es una ecuación de moléculas expresadas en una fórmula)
- TerminoReaccion (Que evalua el momento en que la reacción con ayuda de una flecha indica la separación entre reactivos y productos en una reacción)
- Balanceador (Que calcula los coeficientes de las fórmmulas en la reacción)
- Estequiometría (Que haría calculos de masa y moles en una reacción)

# Alcance

Este proyecto está diseñado para ser completado en un periodo corto (≈ 3 semanas), pero con una arquitectura sólida que permite posibles extensiones futuras:
- estructura de Lewis automática
- geometría molecular VSEPR
- balanceo de ecuaciones químicas
- cargas formales
- estequiometría
- representación gráfica
- base de datos completa de elementos
  
# Consideracones:
Requisitos para compilar: 
g++ main.cpp elemento.cpp atomo.cpp molecula.cpp -o programa

Por el moemnto hacen falta varias revisiones en cuanto a la lógica de las propiedades químicas de cada elemento, principalmente ajustar mejor los cálculos de los electrones de valencia para que la información calculada sea más fiel con la realidad.
