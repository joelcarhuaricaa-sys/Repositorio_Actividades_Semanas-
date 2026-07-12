### Actividad 8 - CC232

#### Estudiante

- Nombre: Joel Gustavo Carhuarica Aguilar

#### Bloque 1 - Diagnóstico inicial de la Semana 8

1. ¿Qué targets de demostración aparecen para Semana 8?

  - sem8_demo_chained
  - sem8_demo_linear
  - sem8_demo_hashtable_oa
  - sem8_demo_aplicaciones
  - sem8_demo_collision_strategies
  - sem8_demo_hash_functions
  - sem8_demo_tombstones
  - sem8_demo_benchmark_load_factor

2. ¿Qué pruebas públicas e internas aparecen?

  - Públicas: sem8_test_public
  - Internas: sem8_test_internal
  - Adicionales: sem8_test_tombstones, sem8_test_collision_patterns, sem8_test_rehashing, sem8_test_randomized_against_stl

3. ¿Qué archivos incluye `Capitulo9.h`?

  - Applications.h
  - ArrayStack.h
  - Bitmap.h
  - ChainedHashTable.h
  - Dictionary.h
  - DoubleHashTable.h
  - Entry.h
  - HashCode.h
  - HashStats.h
  - HashtableOA.h
  - LinearHashTable.h
  - PrimeUtils.h
  - QuadraticHashTable.h
  - RehashPolicy.h
  - RobinHoodHashTable.h
  - UniversalHash.h
  - array.h

4. ¿Qué relación conceptual hay entre Semana 5, Semana 6, Semana 7 y Semana 8?

 La relación conceptual es que las semanas 5, 6 y 7 estudian búsqueda y diccionarios ordenados o con garantías estructurales, mientras que la semana 8 introduce diccionarios no ordenados basados en hashing, con costo esperado constante y con énfasis en colisiones, carga y rehashing.

5. ¿Por qué no es correcto decir que una tabla hash siempre tiene costo `O(1)` garantizado?

 No es correcto decir que una tabla hash siempre tiene costo O(1) garantizado porque:

  - las colisiones pueden degradar la búsqueda,
  - una mala función hash puede concentrar claves,
  - el rehashing y el clustering aumentan el tiempo real,
  - el peor caso puede ser O(n).

6. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?

 La evidencia inicial disponible en esta sesión es la estructura declarada en CMakeLists.txt y README.md. No puedo afirmar que las pruebas hayan corrido ni que hayan pasado, porque no hay salida de ejecución de Semana 8 registrada en esta sesión.

7. ¿Qué diferencia práctica hay entre compilar todo el proyecto y compilar solo los targets de Semana 8?.
 
 Compilar todo el proyecto consume más tiempo y compila más código, mientras que compilar solo los targets de Semana 8 es más rápido y enfocado, aunque no valida integraciones de otras semanas.

 | Comando | Resultado | Error | Interpretación |   
 | :--- | :--- | :--- | :--- | 
 | cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug | No ejecutado en esta sesión | Ninguno | La configuración de la semana está declarada en el proyecto |
 | cmake --build build-debug --target ... | No ejecutado en esta sesión | Ninguno | No hay evidencia de compilación de Semana 8 en esta sesión |
 | ctest --test-dir build-debug -R semana8 --output-on-failure | No ejecutado en esta sesión | Ninguno | No hay evidencia de ejecución de pruebas de Semana 8 | 

 **Archivos revisados primero**

  - README.md
  - CMakeLists.txt
  - Capitulo9.h

 **Conclusión inicial**

  La semana 8 está bien organizada y claramente conectada con las semanas anteriores. Su foco principal es comparar varias formas de implementar diccionarios no ordenados mediante hashing. La estructura del proyecto deja claro que el rendimiento depende de la función hash, las colisiones, la carga y el rehashing. La información disponible confirma la intención pedagógica del material, aunque no hay evidencia nueva de ejecución de demos o pruebas en esta sesión.

#### Bloque 2 - Núcleo conceptual de hashing y diccionarios

 | Concepto | Definición | Archivo relacionado | Ejemplo |   
 | :--- | :--- | :--- | :--- | 
 | Diccionario abstracto | Es un TAD que asocia claves con valores y ofrece operaciones de insertar, consultar y eliminar por clave. | Dictionary.h | Un directorio telefónico donde cada nombre apunta a un número. | 
 | Diccionario | Es la idea general de guardar asociaciones clave-valor, sin exigir que estén ordenadas. | Dictionary.h | {"Ana": 1234} | 
 | Mapa | Es una forma concreta de diccionario donde cada clave aparece a lo sumo una vez y se asocia a un valor. | HashtableOA.h | std::string -> int para contar palabras. | 
 | Conjunto | Es una colección de elementos sin duplicados, donde la clave es el propio elemento. | ChainedHashTable.h | {2, 5, 9} | 
 | Tabla hash | Es una implementación concreta de un diccionario o conjunto basada en dispersión de claves. | LinearHashTable.h | Una tabla que guarda palabras y sus frecuencias. | 
 | Entry | Representa el par clave-valor almacenado en una estructura de diccionario. | Entry.h | Entry<string,int>{ "hola", 1 } | 
 | Función hash | Convierte una clave en un índice o dirección dentro de la tabla. | HashCode.h | hash("perro") % 8 | 
 | Colisión | Ocurre cuando dos claves distintas producen el mismo índice de tabla. | HashCode.h | Dos palabras distintas pueden caer en el mismo bucket. | 
 | Factor de carga | Es la relación entre elementos activos y capacidad de la tabla. | RehashPolicy.h | Si hay 70 elementos y capacidad 100, el factor es 0.70. | 
 | Rehashing | Es reconstruir la tabla con mayor capacidad para mantener rendimiento. | RehashPolicy.h | Aumentar de 8 a 16 posiciones cuando la carga sube. | 
 | HashStats | Registra métricas de operaciones, colisiones, sondeos, rehashes y tombstones. | HashStats.h | Medir cuántas búsquedas fallaron o cuántos sondeos hizo una inserción. | 
 | RehashPolicy | Decide cuándo crecer, limpiar o contraer la tabla según carga y ocupación. | RehashPolicy.h | Crecer si la carga supera 0.70. | 

1. Define con precisión qué es un diccionario abstracto.

 Un diccionario abstracto es un TAD que mantiene asociaciones entre una clave y un valor, con operaciones de inserción, consulta y eliminación por clave, sin fijar cómo se implementa internamente.

2. Explica la diferencia entre diccionario, mapa, conjunto y tabla hash.

 Un diccionario es la idea general de asociar claves con valores; un mapa es una forma concreta de diccionario con claves únicas; un conjunto almacena elementos directamente como claves sin valor asociado; una tabla hash es una implementación concreta de diccionario o conjunto basada en dispersión.

3. Explica qué representa un `Entry<K,V>`.

 Un Entry<K,V> representa un par formado por una clave K y un valor V, es decir, la unidad mínima de información de un diccionario.

4. Explica qué hace una función hash.

 Una función hash transforma una clave en un índice o dirección dentro de una tabla, con el objetivo de distribuir las entradas de forma uniforme.

5. Explica por qué pueden existir colisiones aunque la función hash sea razonable.

 Pueden existir colisiones porque el espacio de claves suele ser mucho mayor que el espacio de posiciones de la tabla; dos claves distintas pueden terminar en la misma posición aunque la función sea razonable.

6. Explica qué significa factor de carga.

 El factor de carga es la relación entre el número de elementos activos y la capacidad de la tabla. Indica qué tan llena está la estructura y cuánto riesgo hay de degradación.

7. Explica qué significa rehashing.

 Rehashing es reconstruir la tabla en una capacidad mayor o menor para recuperar un factor de carga adecuado y reducir el costo de búsquedas.

8. Explica qué mide `HashStats`.

 HashStats mide métricas de rendimiento y comportamiento: inserciones, búsquedas exitosas y fallidas, eliminaciones, colisiones, sondeos, rehashes y tombstones.

9. Explica qué decide `RehashPolicy`.

 RehashPolicy decide cuándo crecer, limpiar o contraer la tabla según los umbrales de carga y ocupación.

10. Compara el costo esperado de una tabla hash con el costo garantizado de AVL y Red-Black Tree.

 Una tabla hash suele ofrecer costo esperado O(1) para inserción, búsqueda y eliminación, mientras que AVL y Red-Black Tree garantizan O(log n) en el peor caso por mantener el árbol balanceado.

 **Por qué hashing no reemplaza completamente a los árboles balanceados**

 Hashing no reemplaza a los árboles balanceados porque ofrece rendimiento esperado, no garantizado en el peor caso; además, no mantiene orden de las claves ni soporta operaciones ordenadas como recorrido ascendente, rango o selección por intervalo. Los árboles balanceados, en cambio, garantizan estabilidad y orden, lo que los hace más apropiados cuando se necesita consultar por rango o mantener un orden explícito.

#### Bloque 3 - Chaining: buckets, colisiones y longitud máxima

 | Operación| Clave | Bucket calculado | Tamaño del bucket antes | Tamaño del bucket después | Colisión observada | loadFactor() | longestBucket() |   
 | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | 
 | add | 10 | hashCode(10) % 8 | 0 | 1 | No | 0.125 | 1 | 
 | add | 18 | hashCode(18) % 8 | 0 o 1 | 1 o 2 | Sí/No | 0.250 | 1 o 2 | 
 | add | 26 | hashCode(26) % 8 | 0 o 1 | 1 o 2 | Sí/No | 0.375 | 1 o 2 |
 | add | 34 | hashCode(34) % 8 | 0 o 1 | 1 o 2 | Sí/No | 0.500 | 1 o 2 | 
 | add | 42 | hashCode(42) % 8 | 0 o 1 | 1 o 2 | Sí/No | 0.625 | 1 o 2 | 
 | add | 50 | hashCode(50) % 8 | 0 o 1 | 1 o 2 | Sí/No | 0.750 | 1 o 2 | 

 Dibujo de una tabla hash con 8 buckets y 10 claves

       Bucket 0: []
       Bucket 1: [] 
       Bucket 2: [10, 18]
       Bucket 3: []
       Bucket 4: [26, 34]
       Bucket 5: []
       Bucket 6: [42, 50]
       Bucket 7: [58, 66, 77]

1. ¿Qué diferencia hay entre el arreglo principal y los buckets?

  La diferencia entre el arreglo principal y los buckets es que el arreglo principal contiene las posiciones de la tabla, mientras que cada bucket es el contenedor de los elementos que cayeron en esa posición. El arreglo define la capacidad; los buckets almacenan las colisiones.

2. ¿Por qué chaining puede almacenar más elementos que la cantidad de posiciones del arreglo principal?

 Chaining puede almacenar más elementos que la cantidad de posiciones del arreglo principal porque cada posición puede contener una lista dinámica. Una sola celda del arreglo puede albergar muchos elementos si todos colisionan en ese bucket.

3. ¿Qué significa que un bucket crezca demasiado?

 Que un bucket crezca demasiado significa que demasiadas claves terminan en la misma posición y la lista asociada a ese bucket se vuelve larga. Eso degrada el rendimiento.

4. ¿Por qué `longestBucket()` es una métrica importante?

 longestBucket() es importante porque mide la peor concentración de colisiones. Si un bucket es muy largo, la búsqueda y la eliminación dejan de ser casi constantes.

5. ¿En qué caso la búsqueda en chaining deja de parecerse a `O(1)` esperado?

 La búsqueda deja de parecerse a O(1) esperado cuando un bucket crece mucho, porque la búsqueda debe recorrer una lista de longitud k en ese bucket.

6. ¿Qué costo tiene recorrer un bucket de longitud `k`?

 Recorrer un bucket de longitud k cuesta O(k).

7. ¿Qué parte del costo depende de la función hash y qué parte depende de la distribución de claves?.

 La parte que depende de la función hash es el índice inicial al que cae cada clave. La parte que depende de la distribución de claves es cuán cargado queda cada bucket y cuántas colisiones aparecen.

 
 **Costo esperado y peor caso**

  - Costo esperado: O(1) si la función hash distribuye bien y el factor de carga se mantiene controlado.
  - Peor caso: O(n) si todas las claves caen en el mismo bucket, porque una búsqueda debe recorrer toda la lista.


