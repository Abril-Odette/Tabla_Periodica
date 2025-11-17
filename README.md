# Motor de Tabla Periódica 

# Descripción general

Este proyecto es una implementación en C++ bajo el paradigma de Programación Orientada a Objetos, cuyo propósito es modelar una parte esencial de la química general mediante una tabla periódica, con los elementos, atómos y moléculas como clases y relaciones entre objetos. Con un carácter modular y extensible, su objetivo no es solo mostrar información, sino procesarla y automatizar tareas de análisis químico a un nivel introductorio.

# Funcionalidad
El usuario puede ejecutar tareas típicas de química básica tales como:
- Consulta y clasificación de elementos 
- Creación de moléculas simples a partir de átomos
- Cálculo de masa molar
- Identificación del tipo de enlace según electronegatividad (Por definirse)
- Determinación de polaridad molecular básica (Por definirse)
- Ejecución de reacciones químicas predefinidas (Por definirse)

El sistema funciona como una tabla periódica avanzada, capaz de ejecutar procesos de análisis químico que comúnmente se realizan de forma manual, facilitando la comprensión de conceptos fundamentales en química. Todo meniante una presentación amigable y organizada de los resultados.

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

- Átomo
  Instancia derivada de un elemento, utilizada para formar moléculas:
  - referencia al elemento base
  - carga
  - electronegatividad

- Molécula
  Conjunto ordenado de átomos y enlaces que permite:
  - almacenar una estructura molecular
  - calcular propiedades (masa molar, polaridad simple)
  - evaluar el tipo de enlace
  - representar la composición química

Estas clases se integran mediante composición, permitiendo construir moléculas a partir de elementos y extender el sistema.

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

Por el moemnto hacen falta varias revisiones en cuanto a la lógica de las propiedades químicas de cada elemento, principalmente ajustar mejor los cálculos de los electrones de valencia para que la información calculada sea más fiel con la realidad.
