# Respuestas Obligatorias - PC3

### 1. ¿Cuál es el problema exacto asignado?
 
 AtCoder ABC241 D - Sequence Query. Enlace oficial: https://atcoder.jp/contests/abc241/tasks/abc241_d

### 2. ¿Qué recibe la entrada y qué produce la salida?
 
 - La entrada recibe en la primera línea un número entero Q que representa la cantidad total de consultas a procesar. Las siguientes Q líneas contienen el formato de cada consulta. Cada consulta empieza con el tipo de operación (1, 2 o 3). Si es tipo 1, recibe además un entero x para ser insertado. Si es tipo 2 o 3, recibe el entero x y un entero k para realizar la búsqueda posicional.

 - La salida produce, por cada consulta de tipo 2 y tipo 3, una línea con un único número entero que corresponde al valor encontrado en el árbol según los criterios solicitados, o en su defecto el valor -1 si la cantidad de elementos disponibles en ese rango es menor que k.

### 3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?
 
 La restricción principal es la cantidad de consultas, donde Q puede llegar hasta 200,000 operaciones, combinado con el hecho de que los valores de x pueden ser extremadamente grandes, hasta 10 elevado a la 18. Una solución ingenua que ordene un arreglo en cada paso o busque linealmente los elementos toma un tiempo excesivo. El juez electrónico impone un límite estricto de tiempo de 2 segundos, por lo que cualquier algoritmo con costo cuadrático sufrirá una penalización por exceso de tiempo.

### 4. ¿Cuál sería la solución ingenua y cuál es su complejidad?

 La solución ingenua consistiría en utilizar un vector dinámico como el contenedor estandar vector de C++. Para la consulta 1, se añade el elemento al final y se ordena el contenedor usando la función sort, lo cual cuesta un tiempo de N logaritmo de N. Para las consultas 2 y 3, se realiza una búsqueda lineal o binaria para ubicar la posición de x y luego se retrocede o avanza k posiciones de forma lineal. La complejidad temporal de esta solución ingenua en el peor de los casos es de O de Q por N, lo que resulta en un comportamiento cuadrático inviable para el volumen de datos del problema.

### 5. ¿Qué estructura de datos elegiste?

 Se eligió un Treap Aumentado con soporte explícito para multiconjuntos. El Treap combina las propiedades de un Árbol Binario de Búsqueda para mantener los elementos ordenados por sus llaves, y las propiedades de un Heap o montículo basado en prioridades aleatorias asignadas a cada nodo para asegurar que el árbol se mantenga balanceado de forma probabilística. Está aumentado porque cada nodo guarda campos internos para registrar su propia frecuencia de repetición y el tamaño total acumulado de su subárbol.

### 6. ¿Qué estructura de la librería cc232 se parece más?

 La estructura que más se parece en la librería del curso es la variante indexada y aumentada de un Árbol Binario de Búsqueda balanceado. Al igual que el Treap propuesto, estas estructuras académicas añaden campos de soporte en sus nodos para permitir el cálculo dinámico de estadísticas de orden y consultas por rangos en tiempo logarítmico.

### 7. ¿Qué operación domina el tiempo?

 La operación que domina el tiempo es la búsqueda descendente combinada con la selección del k-ésimo elemento en los métodos countLess, countLessOrEqual y findKth. Dado que el Treap está balanceado de forma probabilística, la altura promedio del árbol se mantiene acotada. Por lo tanto, el recorrido desde la raíz hasta las hojas toma un tiempo logarítmico proporcional a logaritmo de N, el cual domina todas las consultas del problema.

### 8. ¿Qué invariante mantiene tu estructura?

 La estructura mantiene estrictamente tres propiedades fundamentales:
   - Primero, la propiedad de árbol binario de búsqueda, donde para cualquier nodo, todas las llaves en su subárbol izquierdo son estrictamente menores y todas las llaves en su subárbol derecho son estrictamente mayores.
   - Segundo, la propiedad de montículo min-heap para las prioridades aleatorias, donde la prioridad de cualquier nodo padre es menor o igual a la prioridad de sus nodos hijos.
   - Tercero, la propiedad del tamaño aumentado, donde el tamaño del subárbol de un nodo es igual a su propia frecuencia local más la suma de los tamaños de sus subárboles izquierdo y derecho.

### 9. ¿Dónde se actualiza ese invariante en el código?

 Este invariante se actualiza en el código inmediatamente después de cualquier operación que altere la estructura física o los contadores del árbol. Específicamente, ocurre al final de la inserción recursiva en el método add, y dentro de las funciones de asistencia llamadas rotateLeft y rotateRight, las cuales recalculan los tamaños de los subárboles modificados mediante la función auxiliar updateSize.

### 10. ¿Qué caso borde puede romper una solución superficial?

 Una solución superficial puede romperse ante dos escenarios críticos: cuando el árbol está completamente vacío y se intenta realizar una consulta de tipo 2 o 3, o cuando el parámetro k solicitado supera ampliamente la cantidad real de elementos válidos que cumplen la condición en el subárbol. Si el código no intercepta estas condiciones comparando k contra los tamaños acumulados, intentará acceder a direcciones de memoria 
nulas o punteros inexistentes, provocando una caída por fallo de segmentación.

### 11. ¿Cómo manejas duplicados, empates o elementos obsoletos?

 Los valores duplicados y los empates se manejan de manera nativa sin crear nodos adicionales en el árbol. Cada nodo posee un contador entero llamado frequency. Cuando se intenta insertar una llave que ya existe en el Treap, el algoritmo simplemente incrementa este contador en uno y actualiza de forma ascendente los tamaños de los subárboles. No se generan elementos obsoletos en este problema ya que no se solicitan operaciones de eliminación.

### 12. ¿Cuál es la complejidad temporal por operación?

 La complejidad temporal por operación es de O de logaritmo de N en promedio, tanto para la inserción de un elemento como para el procesamiento de las consultas de búsqueda de extremos posicionales de tipo 2 y tipo 3. Esto se debe a que todas las funciones descienden de manera directa por la altura balanceada del Treap.