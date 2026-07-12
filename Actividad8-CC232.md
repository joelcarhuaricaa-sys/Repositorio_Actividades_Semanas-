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

#### Bloque 4 - Colisiones controladas sin asumir hash de identidad

 Código de la función auxiliar

 ```C++
 #include <iostream>
 #include <vector>
 #include "HashCode.h"

 namespace {
 std::vector<int> findCollidingKeys(std::size_t capacity,
                                   std::size_t targetBucket,
                                   std::size_t needed) {
    std::vector<int> result;
    for (int x = 0; static_cast<std::size_t>(result.size()) < needed; ++x) {
        const std::size_t bucket = ods::hashCode(x) % capacity;
        if (bucket == targetBucket) {
            result.push_back(x);
        }
    }
    return result;
 }
 }  // namespace

 int main() {
    constexpr std::size_t capacity8 = 8;
    constexpr std::size_t capacity16 = 16;

    std::cout << "Buscando claves que caen en el bucket 0 con capacidad 8\n";
    auto keys8 = findCollidingKeys(capacity8, 0, 8);
    for (int x : keys8) {
        std::cout << "x=" << x
                  << " hash=" << ods::hashCode(x)
                  << " bucket=" << (ods::hashCode(x) % capacity8) << "\n";
    }

    std::cout << "\nBuscando claves que caen en el bucket 3 con capacidad 16\n";
    auto keys16 = findCollidingKeys(capacity16, 3, 8);
    for (int x : keys16) {
        std::cout << "x=" << x
                  << " hash=" << ods::hashCode(x)
                  << " bucket=" << (ods::hashCode(x) % capacity16) << "\n";
    }

    return 0;
 }
 ```
1. ¿Por qué `0, 8, 16, 24` solo garantiza colisión si la función hash efectiva es `h(x) = x mod m`?
 
 Por qué 0, 8, 16, 24 solo garantizan colisión si la función efectiva es h(x) = x mod m
 Porque en ese caso todos esos valores dejan el mismo residuo módulo m. Si la función real aplica una mezcla previa, como hashCode(x), entonces el resultado ya no es simplemente x mod m, y la relación de equivalencia desaparece.

2. ¿Qué ocurre si antes se aplica una mezcla como `hashCode(x)`?

 Qué ocurre si antes se aplica una mezcla como hashCode(x)
 La mezcla dispersa los valores de forma pseudoaleatoria, así que los enteros que parecían “separados por 8” ya no necesariamente comparten bucket. El experimento deja de ser una simple aritmética modular y pasa a medir la distribución real de la función hash.

3. ¿Qué claves encontraste para un mismo bucket con capacidad `8` o `16`?

 Qué claves encontraste para un mismo bucket con capacidad 8 o 16
 La demostración las encuentra automáticamente al recorrer enteros desde 0 en adelante y comprobar hashCode(x) % capacity == targetBucket. Como la ejecución del programa no se completó en esta sesión, no puedo afirmar un conjunto exacto de valores sin correrlo; la función ya está preparada para imprimirlos.

4. ¿Cómo cambia el experimento si usas cadenas en lugar de enteros?

 Cómo cambia el experimento si usas cadenas en lugar de enteros
 Cambia la función de dispersión: el código usa hashCode(const std::string&) en HashCode.h, así que la distribución depende de los caracteres y del algoritmo polinomial rotado. Con cadenas, el experimento se vuelve más interesante porque palabras diferentes pueden compartir bucket por motivos de contenido textual, no solo por aritmética.

5. ¿Por qué este bloque es importante para defender evidencia experimental honesta?.

 Por qué este bloque es importante para defender evidencia experimental honesta
 Porque evita suponer que “los números separados por 8 colisionan” sin verificarlo. La tabla hash real solo se puede justificar midiendo el bucket efectivo, no con intuiciones algebraicas que solo valen para una función hash trivial.

 **Tabla con clave, hash normalizado y bucket**

  La salida del programa tendrá este formato:
 
 | Clave | Valor hash | Bucket | 
 | :--- | :--- | :--- | 
 | x | hashCode(x) | hashCode(x) % capacity | 

 **Evidencia de colisión**

  La evidencia se obtiene directamente al ejecutar la demo: cada fila impresa muestra una clave x, su valor hash y el bucket calculado. Si varias filas comparten el mismo bucket para el mismo capacity, entonces esas claves colisionan de forma real según la implementación del proyecto.

#### Bloque 5 - Linear probing: estados, sondeo y tombstones
 
 Tabla de operaciones

 | Operación | Clave | Posición hash inicial | Secuencia de sondeo | Estado final de la celda | size | occupied | loadFactor() | occupiedFactor() | tombstoneCount() | 
 | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
 | add | 7 | h(7) | [h(7)] | Filled | 1 | 1 | 0.125 | 0.125 | 0 |
 | add | 15 | h(15) | [h(15)] o [h(15), h(15)+1] si colisiona | Filled | 2 | 2 | 0.250 | 0.250 | 0 |
 | add | 23 | h(23) | [h(23)] o [h(23), h(23)+1] si colisiona | Filled | 3 | 3 | 0.375 | 0.375 | 0 |
 | add | 31 | h(31) | [h(31)] o [h(31), h(31)+1, ...] | Filled | 4 | 4 | 0.500 | 0.500 | 0 | 
 | add | 39 | h(39) | [h(39)] o [h(39), h(39)+1, ...] | Filled | 5 | 5 | 0.625 | 0.625 | 0 |
 | remove | 23 | h(23) | [... hasta encontrar 23] | Deleted | 4 | 5 | 0.500 | 0.625 | 1 |
 | add | 47 | h(47) | [h(47)] o [h(47), h(47)+1, ...] | Filled | 5 | 6 | 0.625 | 0.750 | 1 |

 Trazado manual
 
  - Búsqueda exitosa:
     - Si se busca 23 después de insertarlo, la búsqueda inicia en h(23) y sigue probando posiciones contiguas hasta encontrar la celda Filled que contiene 23.
     - Si esa celda fue borrada, la búsqueda debe seguir más allá porque el elemento podría haber sido insertado más adelante.

  - Búsqueda fallida:

     - Si se busca 99, la búsqueda recorre posiciones ocupadas y Deleted hasta encontrar una celda Empty.
     - Si hay clustering, esa búsqueda puede recorrer muchas posiciones antes de terminar.
 
1. ¿Qué representan los estados `Empty`, `Filled` y `Deleted`?

  - Empty: la celda nunca fue usada o ya no tiene nada.
  - Filled: la celda contiene un elemento activo.
  - Deleted: la celda contenía un elemento que fue eliminado; sirve como marca de borrado para no romper la búsqueda por sondeo.

2. ¿Por qué `Deleted` no puede tratarse igual que `Empty`?

  - Porque una búsqueda fallida debe seguir pasando por una celda Deleted para no perder elementos que quedaron más adelante en la secuencia de sondeo.
  - Si se tratara como Empty, la búsqueda terminaría temprano y produciría un falso negativo.

3. ¿Qué diferencia hay entre `size` y `occupied`?

  - size: cantidad de elementos activos.
  - occupied: elementos activos más las celdas marcadas como Deleted.

4. ¿Por qué `loadFactor()` y `occupiedFactor()` pueden divergir después de muchas eliminaciones?

  - Después de muchas eliminaciones, size baja, pero occupied permanece mayor porque los tombstones siguen ocupando espacio lógico.
  - Por eso loadFactor() puede disminuir, mientras occupiedFactor() sigue alto.

5. ¿Qué problema aparece si se acumulan demasiados tombstones?

  - La tabla se vuelve más lenta para búsquedas e inserciones.
  - Aumenta la longitud de los sondeos y se degrada el rendimiento, parecido a un clustering acumulado.

6. ¿Cuándo debe hacerse rehashing por carga ocupada aunque haya pocos elementos activos?

  - Cuando occupiedFactor() supera el umbral de la política, aunque loadFactor() sea bajo.
  - Esto ocurre especialmente tras muchas eliminaciones con muchas marcas Deleted.

7. ¿Qué costo tiene una búsqueda fallida cuando hay clustering?.

  - El costo es O(k), donde k es la longitud del tramo de sondeos hasta encontrar una celda Empty.
  - En el peor caso puede acercarse a O(n). 

 **Por qué open addressing necesita una política cuidadosa de eliminación**
  
  Open addressing no puede eliminar elementos como en una lista simple, porque el sondeo depende del estado de las posiciones intermedias. Un borrado mal manejado rompe la continuidad de las búsquedas y puede hacer perder elementos. Por eso la política de eliminación con Deleted y rehashing es clave para mantener la tabla válida.

#### Bloque 6 - HashtableOA como diccionario `key value`

  Tabla de operaciones

 | Operación | Entrada | Resultado esperado | Evidencia observada |  
 | :--- | :--- | :--- | :--- | 
 | put("hash", 1) | insertar | se agrega la entrada | la tabla queda con 1 elemento |
 | put("tree", 2) | insertar | se agrega la entrada | la tabla queda con 2 elementos |
 | put("graph", 3) | insertar | se agrega la entrada | la tabla queda con 3 elementos | 
 | get("hash") | consultar clave existente | devuelve 1 | el demo imprime hash -> 1 |
 | remove("tree") | eliminar clave existente | elimina la entrada | el size baja y aparece un tombstone | 
 | get("tree") | consultar clave eliminada | devuelve nullopt | la búsqueda falla |
 | put("hash", 9) | insertar clave repetida | la implementación actual no actualiza, solo rechaza | put devuelve false en el caso de clave ya presente |

1. ¿Qué diferencia hay entre una tabla usada como conjunto y una tabla usada como diccionario?

 Diferencia entre tabla usada como conjunto y tabla usada como diccionario

 - En un conjunto, la clave es el propio elemento y no hay valor adicional.
 - En un diccionario, cada clave apunta a un valor asociado.

2. ¿Qué representa una clave?

  - La clave identifica de forma única la entrada dentro del diccionario.

3. ¿Qué representa un valor?

  El valor es la información asociada a esa clave.

4. ¿Qué debe devolver `get(k)` si la clave existe?

  Debe devolver el valor asociado, encapsulado en std::optional<V>.

5. ¿Qué debe ocurrir con `remove(k)` si la clave no existe?

  Debe devolver false y no modificar la tabla.

6. ¿Qué política usa la implementación cuando se intenta insertar una clave repetida?

  La implementación actual de HashtableOA.h no actualiza la entrada existente; simplemente rechaza la inserción devolviendo false.

7. ¿Por qué una interfaz `put`, `get`, `remove` permite separar el uso del diccionario de su implementación interna?.
 
 - Porque el cliente solo necesita saber qué operación hace el diccionario, no cómo se resuelven colisiones, sondeos, rehashing o tombstones.
 - La implementación interna puede cambiar sin alterar el uso del diccionario.

 **Ejemplo string -> int para conteo de frecuencias**

 ```C++
 ods::HashtableOA<std::string, int> freq;
 freq.put("hola", 1);
 freq.put("mundo", 1);
 freq.put("hola", 2);   // en la implementación actual, esto no actualiza
 ```
 En la práctica, el diseño para conteo de frecuencias se hace con get, luego remove y luego put con el valor incrementado, como aparece en Applications.h.

 **Cómo cambia el diseño si put debe actualizar el valor**

 Si se quiere que put(k, v) actualice el valor de una clave ya existente, entonces:

  - la operación debe detectar si la clave ya estaba presente,
  - debe reemplazar el valor asociado,
  - y debe devolver un indicador de si la entrada fue nueva o actualizada.

 En otras palabras, el contrato cambia de “insertar o rechazar” a “insertar o reemplazar”, y eso exige que la implementación revise el estado de la clave antes de insertar.


## Bloque 7 - Comparación de estrategias de colisión

### Tabla comparativa

| Estrategia | Representación interna | Cómo resuelve colisiones | Métrica más sensible | Ventaja | Debilidad | Costo esperado | Peor caso |
|---|---|---|---|---|---|---|---|
| Chaining | Arreglo de buckets con listas | Acumula elementos en la misma cubeta | Longitud del bucket | Simple y robusta | Un bucket largo degrada el rendimiento | $O(1)$ esperado | $O(n)$ |
| Linear probing | Arreglo de slots con sondeo lineal | Busca la siguiente posición libre | Longitud del cluster | Muy simple | Sufre clustering primario | $O(1)$ esperado | $O(n)$ |
| Quadratic probing | Arreglo con sondeo cuadrático | Usa saltos $1,4,9,\dots$ | Longitud del cluster | Reduce clustering | Puede dejar huecos | $O(1)$ esperado | $O(n)$ |
| Double hashing | Arreglo con segundo hash | Usa un paso independiente del primer hash | Distribución del segundo hash | Muy buena dispersión | Más compleja | $O(1)$ esperado | $O(n)$ |
| Robin Hood | Arreglo con desplazamiento balanceado | Intercambia elementos para equilibrar distancia | Desplazamiento máximo | Reduce la desviación de búsqueda | Más compleja | $O(1)$ esperado | $O(n)$ |

### Respuestas

1. El clustering primario es la formación de bloques contiguos de posiciones ocupadas cuando varias claves terminan en zonas vecinas.
2. Linear probing tiende a formar bloques porque cada inserción en una celda ocupada avanza a la siguiente, y eso hace que nuevas claves se acumulen cerca.
3. Quadratic probing intenta mejorar linear probing usando saltos que dispersan mejor las inserciones.
4. Double hashing intenta mejorar la distribución al usar una segunda función para calcular el paso del sondeo.
5. Robin Hood intenta equilibrar las distancias de búsqueda para que ninguna clave recorra demasiado.
6. Chaining y open addressing no tienen el mismo comportamiento ante carga alta porque chaining usa listas externas mientras open addressing depende de la continuidad de los slots.
7. Para una tabla pequeña de laboratorio, conviene chaining.
8. Para carga alta con muchas búsquedas, conviene double hashing o Robin Hood.
9. La estrategia que se degrada más con muchas eliminaciones es linear probing, por los tombstones y el clustering.

---

## Bloque 8 - Funciones hash, hashing universal y distribución

### Tabla de distribución esperada

| Conjunto de claves | Cantidad | Capacidad | Buckets usados | Bucket más cargado | Colisiones | Comentario |
|---|---:|---:|---:|---:|---:|---|
| Enteros consecutivos | $n$ | $m$ | varios | moderado | pocas | Tiende a distribuirse bien si la mezcla es buena |
| Enteros con patrón repetitivo | $n$ | $m$ | pocos | alto | muchas | Los patrones pueden favorecer agrupaciones |
| Texto con prefijos comunes | $n$ | $m$ | varios | moderado/alto | moderadas | Depende mucho del hash de cadenas |

### Respuestas

1. Una buena función hash debe ser determinista, rápida y distribuir las claves de forma uniforme.
2. Una función hash determinista puede ser buena para datos comunes y mala para datos adversariales, porque un adversario puede elegir entradas que concentren colisiones.
3. El hashing universal introduce una familia de funciones y elige una al azar, reduciendo la probabilidad de que un conjunto adversarial haga daño.
4. No se debe evaluar una función hash con un solo conjunto porque puede funcionar bien para uno y mal para otro.
5. A mayor dispersión, menores son las colisiones y menor el número esperado de sondeos, por lo que el costo esperado se acerca a $O(1)$.

---

## Bloque 9 - Rehashing, política de carga y costo amortizado

### Respuestas

1. El crecimiento ocurre cuando el factor de carga activo supera el umbral de la política, es decir, cuando $active / capacity > 0.70$.
2. La limpieza por tombstones puede ocurrir cuando la ocupación total con borrados supera $occupied / capacity > 0.82$.
3. La contracción puede ocurrir cuando el número activo baja mucho, por ejemplo cuando $active / capacity < 0.125$.
4. El rehashing cuesta $O(n)$ porque hay que redistribuir todos los elementos en una tabla nueva.
5. Aun así se habla de costo amortizado porque esos rehashings no ocurren en cada operación, sino de forma ocasional.
6. A mayor capacidad, menor es el factor de carga y menores suelen ser los sondeos; a menor capacidad, la tabla se llena más rápido y las búsquedas se degradan.
7. `HashStats` muestra evidencia de rehashings y del número de sondeos, lo que permite medir si la política está funcionando.
8. Si el factor de carga es demasiado alto, las búsquedas, inserciones y eliminaciones pueden volverse lineales en el peor caso.

### Tabla de política

| Situación | Condición |
|---|---|
| Crecer | $active / capacity > 0.70$ |
| Limpiar o crecer | $occupied / capacity > 0.82$ |
| Contraer | $active / capacity < 0.125$ |

---

## Bloque 10 - Aplicaciones de hashing

### Aplicación 1: `frequencyCount`

- Problema: contar cuántas veces aparece cada palabra.
- Salida esperada: un diccionario palabra → frecuencia.
- Lo que se guarda: la palabra como clave y el contador como valor.
- Operación dominante: `get` y `put`.
- Costo esperado: $O(n)$ al procesar una lista de palabras.
- Degradación posible: muchas colisiones o una mala función hash.

### Aplicación 2: `twoSum`

- Problema: encontrar dos índices cuya suma sea un objetivo.
- Salida esperada: un par de índices o `nullopt`.
- Lo que se guarda: un valor ya visto como clave y su índice como valor.
- Operación dominante: `get` y `put`.
- Costo esperado: $O(n)$.
- Degradación posible: colisiones que hagan más lenta la búsqueda.

### Comparación con AVL o Red-Black Tree

Con un árbol balanceado, el mismo problema se resuelve normalmente en $O(n \log n)$ porque cada consulta requiere buscar en el árbol. Con hashing, el costo esperado suele ser lineal.

---

## Bloque 11 - Modificación controlada de código

### Opción elegida: experimento de colisiones reales

- Archivo modificado: una demo nueva para encontrar claves que realmente colisionen con la función hash usada.
- Función agregada: `findCollidingKeys(capacity, targetBucket, needed)`.
- Invariante: cada clave reportada debe cumplir `hashCode(x) % capacity == targetBucket`.
- Prueba o demo: la demo imprime la clave, el valor hash y el bucket real.
- Costo: el costo es lineal en la cantidad de enteros probados hasta encontrar las claves necesarias.
- Por qué no oculta el algoritmo: porque sigue usando la misma función hash y la misma lógica de tabla, solo mide el comportamiento real.

### Ejemplo de idea

```cpp
std::vector<int> findCollidingKeys(std::size_t capacity,
                                   std::size_t targetBucket,
                                   std::size_t needed) {
    std::vector<int> result;
    for (int x = 0; static_cast<std::size_t>(result.size()) < needed; ++x) {
        if (ods::hashCode(x) % capacity == targetBucket) {
            result.push_back(x);
        }
    }
    return result;
}
```

---

## Bloque 12 - Comparación final con BST, Treap, AVL, Red-Black Tree y tablas hash

### Matriz de decisión

| Estructura | Mantiene orden | Búsqueda promedio | Búsqueda peor caso | Inserción | Eliminación | Memoria adicional | Ventaja principal | Riesgo principal | Caso de uso recomendado |
|---|---|---|---|---|---|---|---|---|---|
| BST simple | Sí | $O(h)$ | $O(n)$ | $O(h)$ | $O(h)$ | Baja | Simple | Puede degenerarse | Laboratorio simple |
| Treap | Sí | $O(\log n)$ esperado | $O(n)$ en peor caso | $O(\log n)$ esperado | $O(\log n)$ esperado | Media | Balanceo probabilístico | Aleatoriedad | Uso práctico ligero |
| AVL | Sí | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | Media | Garantía fuerte | Rebalanceo frecuente | Búsquedas estrictas |
| Red-Black Tree | Sí | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | Media | Menos rotaciones que AVL | Más compleja | Contenedores ordenados |
| ChainedHashTable | No | $O(1)$ esperado | $O(n)$ | $O(1)$ esperado | $O(1)$ esperado | Media | Muy rápida en diccionarios | Colisiones y buckets largos | Conteo y acceso por clave |
| LinearHashTable | No | $O(1)$ esperado | $O(n)$ | $O(1)$ esperado | $O(1)$ esperado | Baja | Simplicidad | Clustering y tombstones | Laboratorio de open addressing |
| HashtableOA | No | $O(1)$ esperado | $O(n)$ | $O(1)$ esperado | $O(1)$ esperado | Media | Interfaz tipo diccionario | Tombstones y rehashing | Diccionario key → value |

### Respuestas

1. Elegiría una tabla hash para acceso rápido por clave sin necesidad de orden.
2. Elegiría AVL cuando necesito garantías fuertes de complejidad y búsquedas balanceadas.
3. Elegiría Red-Black Tree cuando necesito un árbol ordenado robusto y estable.
4. Elegiría Treap para una implementación más ligera y probabilística.
5. Una tabla hash no sirve directamente para consultas por rango porque no preserva orden.
6. Un árbol balanceado sí permite recorrer claves en orden porque mantiene una estructura jerárquica ordenada.
7. Costo esperado significa que el rendimiento suele ser bueno en promedio; costo garantizado significa que se cumple siempre, aunque sea peor.
8. Para un índice de palabras sin orden, prefiero hashing.
9. Para un ranking ordenado por clave, prefiero AVL o Red-Black Tree.
10. Para `lowerBound` y `upperBound`, prefiero AVL o Red-Black Tree.

---

## Conclusión final

Las tablas hash son excelentes para búsqueda rápida por clave cuando no se necesita mantener orden. Los árboles balanceados, en cambio, son preferibles cuando se requiere recorrido ordenado, rango o garantías estrictas de complejidad en el peor caso. La elección correcta depende de si el problema prioriza velocidad esperada o estabilidad y orden.

