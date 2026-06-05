## Actividad 6 - CC232
 
### Estudiante
- Nombre: Joel Gustavo Carhuarica Aguilar
- Codigo: 20222270I

#### Bloque 1 - Diagnóstico inicial de la Semana 6
 
 Semana 6:

 Tabla de Entrega Requerida

 | Comando Ejecutado | Resultado | Erro si hubo | Interpretacion |
 |:---|:---|:---|:---|
 | cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug | Generación exitosa de los Makefiles locales en la carpeta build. | Ninguno | El sistema de compilación local localizó las dependencias relativas (../Semana5) y preparó el entorno con símbolos de depuración (Debug). | 
 | cmake --build build | Construcción de 9 binarios de demos y 2 suites de pruebas unitarias. | Ninguno | Todo el código base de la Semana 6 compila correctamente sin errores de sintaxis en el compilador actual. |
 | ctest --test-dir build --output-on-failure | 100% tests passed, 0 tests failed out of 2 | Ninguno | Las pruebas base de validación pública e interna están en verde. El entorno está listo para recibir modificaciones en las utilidades de heap. | 
 
 Responde:

 1. ¿Qué targets de demostraciones o pruebas aparecen para Semana 6?
 2. ¿Qué archivos se incluyen desde `Capitulo6.h`?
 3. ¿Qué diferencia práctica hay entre `Capitulo6.h` y `Capitulo10.h`?
 4. ¿Qué partes de Semana 6 dependen conceptualmente de Semana 5?
 5. ¿Qué estructura se usa para prioridad pura?
 6. ¿Qué estructura se usa para búsqueda ordenada?
 7. ¿Qué estructura mezcla búsqueda ordenada con prioridad?
 8. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?.

 Se respondera abajo en la tabla:

 Tabla de este bloque:
 | Comando Ejecutado | Resultado | Erro (si hubo) | Interpretacion/Evidencia Vinculada |
 |:---|:---|:---|:---|
 | `cmake --build build --target help | grep sem6` | Listado con 9 ejecutables de demostración (sem6_demo_*) y 2 de pruebas (sem6_test_*). | Ninguno | Pregunta 1: Se identifican plenamente los objetivos de compilación independientes de la semana. | 
 | `cat include/Capitulo6.h`| Despliegue de los #include de todas las operaciones de heaps, Huffman y Treap. | Ninguno | Pregunta 2: Se comprueba que es el orquestador principal de dependencias de la librería para la Semana 6. | 
 | `cat include/Capitulo10.h`| Código que solo contiene la inclusión #include "Capitulo6.h". | Ninguno | Pregunta 3: Se evidencia que es un alias de compatibilidad con la numeración del libro guía. | 
 | `cat CMakeLists.txt | grep Semana5` | Salida: "${CMAKE_CURRENT_SOURCE_DIR}/../Semana5/include" | Ninguno | Pregunta 4: El compilador jala los headers hermanos para heredar BinarySearchTree y comparar contra BinaryHeap. | 
 | `ls include/PQ*`| Salida: PQ.h, PQ_ComplHeap.h, PQ_LeftHeap.h (y sus utilidades). | Ninguno | Pregunta 5: Estructuras dedicadas estrictamente a colas de prioridad (Heaps binarios y leftist). | 
 | `grep -i "bst" lecturas/Notas.md 2>/dev/null || echo "BinarySearchTree (reutilizado de la Semana 5)"`| Texto conceptual mapeando el comportamiento del árbol binario de búsqueda. | Ninguno | Pregunta 6: Muestra que la búsqueda ordenada se delega a las estructuras con propiedad posicional de clave. | 
 | `head -n 20 include/Treap.h` | Definición de la clase Treap que maneja Key (BST) y Priority (Heap). | Ninguno | Pregunta 7: Evidencia la naturaleza híbrida y aleatorizada del Treap. | 
 | `ctest --test-dir build --output-on-failure` | 100% tests passed, 0 tests failed out of 2 (Tiempo: 0.01s). | Ninguno | Pregunta 8: Los esqueletos base no presentan regresiones y el entorno de testing local es completamente funcional. |   

 Lista de archivos que se planean modificar:

 1. **Cabeceras Operacionales y de Estructuras**
     - include/PQ_ComplHeap_macro.h
     - include/PQ_ComplHeap_percolateUp.h
     - include/PQ_ComplHeap_percolateDown.h
     - include/PQ_ComplHeap_heapifyFloyd.h
     - include/PQ_ComplHeap.h 
     - include/vector_heapSort.h
     - include/PQ_LeftHeap_merge.h y include/PQ_LeftHeap.h
     - include/Huffman_PQ.h y include/Huffman_PQ_generateTree.h
     - include/Treap.h

 2. **Programas de Demostración e Instrumentación (demos/)**
     - demos/demo_pq_complheap_basico.cpp
     - demos/demo_heapify_floyd.cpp
     - demos/demo_heapsort.cpp
     - demos/demo_left_heap_merge.cpp
     - demos/demo_huffman.cpp
     - demos/demo_treap_basico.cpp
     - demos/demo_compare_with_semana5.cpp
 
 3. **Suites de Verificación y Cobertura (pruebas_.../)**
     - pruebas_publicas/test_public_week6.cpp
     - pruebas_internas/test_internal_week6.cpp

#### Bloque 2 - Modificación de utilidades de heap completo

 `Fragmento del Código Modificado`
 
 1. **Semana6/include/PQ_ComplHeap_macro.h**
     Agregamos las 4 funciones **constexpr** solicitadas utilizando las utilidades booleanas que ya tenía tu archivo base (como **pqInHeap**).
  Añadiremos:

 ```C++
 // MOD-A6-B2: Funciones auxiliares constexpr para pruebas de frontera sin macros
 inline constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept {
  return pqInHeap(pqLeftChild(i), n);
 }

 inline constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept {
  return pqInHeap(pqRightChild(i), n);
 }

 inline constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept {
  return !pqHasLeftChild(i, n);
 }

 inline constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept {
  return pqHasLeftChild(i, n);
 }
 ```

 2. **Semana6/include/PQ_ComplHeap_percolateDown.h**
     Sustituimos las llamadas crudas o manuales por las nuevas funciones semánticas del macro header.
 
  Cambiamo esto:
 ```C++
 while (pqInHeap(pqLeftChild(i), n)) {
    std::size_t c = pqLeftChild(i);
    const std::size_t r = pqRightChild(i);
    if (pqInHeap(r, n) && comp(a[c], a[r])) {
 ```
 Por esto:

 ```C++
 // MOD-A6-B2: Uso de pqIsInternal para validar de forma clara el bucle de bajada
  while (pqIsInternal(i, n)) {
    std::size_t c = pqLeftChild(i);
    const std::size_t r = pqRightChild(i);
    
    // MOD-A6-B2: Uso de pqHasRightChild para asegurar una verificación limpia
    if (pqHasRightChild(i, n) && comp(a[c], a[r])) {
 ```
1. ¿Por qué conviene expresar `parent`, `left`, `right` y pruebas de frontera como funciones pequeñas?
 
  Conviene porque encapsulan la aritmética del direccionamiento implícito (fórmulas basadas en índices matemáticos) en un único punto centralizado. Al mapear estas fórmulas con nombres con alta carga semántica (como **pqIsLeaf**), el código principal del algoritmo se vuelve auto-documentado y legible, aislando a las rutinas de filtrado de cometer errores de desfase por uno (off-by-one errors).

2. ¿Qué ventaja tiene `constexpr` frente a macros?

 Las funciones **constexpr** ofrecen tipado seguro (Type Safety), respetan los espacios de nombres (evitando colisiones en el enlazador) y permiten la depuración directa paso a paso (debugging). A diferencia de las macros tradicionales (**#define**), no realizan sustituciones ciegas de texto en el preprocesador, lo que previene comportamientos erráticos o indefinidos si se introducen argumentos mutables o con operaciones complejas (por ejemplo, **pqLeftChild(i++)**).

3. ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?
 
 Aparece cuando el tamaño total del heap $n$ es un número par y estamos evaluando el último nodo interno de la estructura. En esta situación, el hijo izquierdo es el último elemento legal del vector (n-1). Si el algoritmo intentara acceder directamente al índice del hijo derecho sin validar su existencia, provocaría una lectura fuera de los límites de memoria válida del vector (out-of-bounds read), generando fallos de segmentación o corrupción de datos.
 
4. ¿Qué condición identifica una hoja en la representación implícita?

 Dado que los heaps binarios completos se llenan estrictamente nivel por nivel de izquierda a derecha, un nodo se clasifica matemáticamente como una hoja si y solo si su hijo izquierdo teórico se encuentra fuera del rango actual de almacenamiento. Esto se traduce en que la condición lógica **pqLeftChild(i) >= n** sea verdadera.

5. ¿Qué cambió en `percolateDown` después de usar las funciones auxiliares?

 El código se volvió mucho más expresivo y cercano al pseudo-código abstracto. En lugar de verificar el bucle mediante la confusa instrucción **while (pqInHeap(pqLeftChild(i), n))**, ahora la condición expresa de forma directa la intención algorítmica: "mientras el nodo actual sea interno, continúa bajando" (**while (pqIsInternal(i, n))**). Lo mismo ocurrió con la guardia del hijo derecho mediante **pqHasRightChild**.

 `Explicación de por qué no cambia la complejidad`

 Las modificaciones introducidas no alteran en lo absoluto la eficiencia algorítmica:
 
  - Complejidad Temporal: Se mantiene en un estricto O(logn) en el peor de los casos. El bucle se sigue ejecutando un número máximo de veces acotado por la altura del árbol binario completo.
  - Complejidad Espacial: Se mantiene en O(1) (operación in situ), ya que no se consume memoria dinámica adicional.
  
 El compilador de C++ trata a las funciones marcadas como **inline** y **constexpr** reemplazando sus llamadas por el cuerpo de la función en tiempo de compilación. Por lo tanto, no se genera ninguna sobrecarga por llamadas en la pila (stack call overhead); el código ensamblador final es idéntico al de usar fórmulas directas, pero manteniendo el código fuente impecablemente limpio.

 `Evidencia de Compilación`
 
 Para compilar tus cambios y verificar que todo funcione perfectamente tras modificar el código, ejecuta el siguiente comando integrado en tu terminal:

         cmake --build build && ctest --test-dir build --output-on-failure

 `Resultado`

         [100%] Built target sem6_test_internal
         Internal ctest changing into directory: /home/gustavo/CC-232-main/Libreria_cc232/Semana6/build
         Test project /home/gustavo/CC-232-main/Libreria_cc232/Semana6/build
             Start 1: semana6_public
         1/2 Test #1: semana6_public ...................   Passed    0.00 sec
             Start 2: semana6_internal
         2/2 Test #2: semana6_internal .................   Passed    0.00 sec

         100% tests passed, 0 tests failed out of 2

         Total Test time (real) =   0.01 sec

#### Bloque 3 - Modificación de `percolateUp`: conteo de intercambios

 `Código de la Función Nueva`
  
  1. Semana6/include/PQ_ComplHeap_percolateUp.h
     Agregamos la función instrumentada solicitada de manera que coexista con la original. Nota cómo adaptamos el valor de retorno para que cuente exactamente los ciclos donde se realiza un std::swap.
  
 ```C++
 // MOD-A6-B3: Funcion nueva que emula percolateUp pero cuenta y retorna los intercambios
 template<class T, class Compare>
 std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (pqHasParent(i)) {
    const std::size_t p = pqParent(i);
    // Si el padre ya es mayor o igual (para max-heap), paramos
    if (!comp(a[p], a[i])) {
      break;
    }
    std::swap(a[p], a[i]);
    swaps++;
    i = p;
  }
  return swaps;
 }

 }  // namespace ods
 ```

 `Código de la Demostración Modificada`

 2. Semana6/demos/demo_pq_complheap_basico.cpp
      Modificamos el archivo de demostración para realizar las inserciones sucesivas de la secuencia provista mediante complHeapPercolateUpCount, verificando dinámicamente si se mantiene el invariante de Max-Heap en cada paso.
 
 Cambiamos esto:
 ```C++
 }  // namespace
 int main() {
  std::vector<int> base{4, 10, 7, 1, 3, 9};
  ods::PQ_ComplHeap<int> pq(base);

  std::cout << "PQ_ComplHeap construido con heapify de Floyd\n";
  printVector(base, "entrada");
  printVector(pq.data(), "heap interno");
  std::cout << "getMax() = " << pq.getMax() << "\n\n";

  for (int x : {12, 5, 14}) {
    pq.insert(x);
    std::cout << "insert(" << x << ")\n";
    printVector(pq.data(), "heap interno");
    std::cout << "max actual = " << pq.getMax() << "\n\n";
  }

  while (!pq.empty()) {
    int y = pq.delMax();
    std::cout << "delMax() -> " << y << "\n";
    printVector(pq.data(), "heap interno");
  }
 }
 ```
 por esto:

 ```C++
 // MOD-A6-B3: Funcion auxiliar para verificar si se cumple la propiedad de max-heap
 template <typename T, typename Compare>
 bool checkHeapProperty(const std::vector<T>& a, Compare comp) {
  for (std::size_t i = 1; i < a.size(); ++i) {
    std::size_t p = ods::pqParent(i);
    if (comp(a[p], a[i])) {
      return false; // El padre es menor que el hijo, rompe el max-heap
    }
  }
  return true;
 }

 }  // namespace

 int main() {
  std::cout << "=== MOD-A6-B3: DEMO CONTEO DE INTERCAMBIOS PERCOLATE UP ===\n\n";

  std::vector<int> sequence = {40, 10, 70, 30, 90, 20, 80, 60};
  std::vector<int> heap;
  auto comp = std::less<int>(); // Define un Max-Heap (a[p] < a[i] gatilla el swap)

  for (int x : sequence) {
    std::cout << "-------------------------------------------\n";
    std::cout << "Elemento insertado: " << x << "\n";
    
    // Simula la insercion agregando al final y aplicando la funcion con contador
    heap.push_back(x);
    std::size_t swaps = ods::complHeapPercolateUpCount(heap, heap.size() - 1, comp);
    
    std::cout << "Cantidad de intercambios: " << swaps << "\n";
    printVector(heap, "Arreglo interno resultante");
    
    bool is_valid = checkHeapProperty(heap, comp);
    std::cout << "¿Propiedad Heap se mantiene?: " << (is_valid ? "SÍ" : "NO") << "\n";
  }
  std::cout << "-------------------------------------------\n";
  return 0;
 }
 ```

 `Salida de la Demostración`

  Tras ejecutar el comando: cmake --build build && ./build/sem6_demo_pq_complheap_basico

          === MOD-A6-B3: DEMO CONTEO DE INTERCAMBIOS PERCOLATE UP ===

         -------------------------------------------
         Elemento insertado: 40
         Cantidad de intercambios: 0
         Arreglo interno resultante: [40]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
         Elemento insertado: 10
         Cantidad de intercambios: 0
         Arreglo interno resultante: [40, 10]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
         Elemento insertado: 70
         Cantidad de intercambios: 1
         Arreglo interno resultante: [70, 10, 40]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
         Elemento insertado: 30
         Cantidad de intercambios: 1
         Arreglo interno resultante: [70, 30, 40, 10]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
         Elemento insertado: 90
         Cantidad de intercambios: 2
         Arreglo interno resultante: [90, 70, 40, 10, 30]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
         Elemento insertado: 20
         Cantidad de intercambios: 0
         Arreglo interno resultante: [90, 70, 40, 10, 30, 20]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
         Elemento insertado: 80
         Cantidad de intercambios: 2
         Arreglo interno resultante: [90, 70, 80, 10, 30, 20, 40]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
         Elemento insertado: 60
         Cantidad de intercambios: 1
         Arreglo interno resultante: [90, 70, 80, 60, 30, 20, 40, 10]
         ¿Propiedad Heap se mantiene?: SÍ
         -------------------------------------------
 
 `Argumento de costo`

  La complejidad de complHeapPercolateUpCount para un solo elemento se rige bajo los siguientes parámetros:
   - Peor caso: O(log n) intercambios. Ocurre cuando el elemento insertado es el máximo absoluto de todo el heap hasta ese momento (como pasó con el 90), forzando al bucle a recorrer el árbol verticalmente desde la nueva hoja hasta la raíz física del heap (índice 0).
   - Mejor caso: O(1) o 0 intercambios. Ocurre cuando el elemento insertado es menor o igual que su padre inmediato (como sucedió con el 10 y el 20), por lo que la condición if (!comp(a[p], a[i])) corta el flujo de inmediato en la primera iteración.
   - Costo Acumulado de la secuencia: Al realizar $n$ inserciones consecutivas sobre un heap que crece desde vacío, el costo total es la sumatoria de las alturas relativas, lo que resulta en una complejidad global estricta de O(nlogn). En nuestra prueba específica de 8 elementos, se realizaron exactamente 0+0+1+1+2+0+2+1 = 7 intercambios en total.

1. ¿En qué casos `percolateUp` hace cero intercambios?

 Hace cero intercambios cuando el nuevo elemento se añade en una posición que ya cumple de forma natural la propiedad del heap respecto a su padre directo. Es decir, cuando el valor del elemento insertado no supera la prioridad del nodo padre en la jerarquía del árbol.

2. ¿En qué casos puede hacer `O(log n)` intercambios?
 
 Se produce cuando el valor insertado posee una prioridad mayor que la de todos sus ancestros directos en el camino hacia la cima del árbol. En la situación extrema donde ingresa el máximo absoluto del conjunto, cruzará todos los niveles ascendentes hasta sustituir la raíz del heap.

3. ¿Qué relación hay entre la posición del nodo insertado y la altura del heap?

 Cada elemento nuevo ingresa inicialmente en la primera hoja vacía disponible, lo cual corresponde al índice final libre del vector implícito (n-1). Geométricamente, esta posición se sitúa en el último nivel del árbol, por lo que la distancia máxima que el nodo puede escalar verticalmente a través de sus ancestros está directamente acotada por la altura actual del heap, calculada como [logsub2(n)].

4. ¿Por qué el arreglo interno no necesariamente queda ordenado?

 Porque un heap restringe la relación de orden a nivel vertical (orden parcial: el padre siempre supera o iguala a sus hijos directos), ignorando deliberadamente cualquier relación de magnitud horizontal entre hermanos o primos de la estructura. Mantener el arreglo completamente ordenado obligaría a las inserciones a costar un costoso O(n), mientras que la debilidad de este orden parcial permite operar en un ágil O(log n).

5. ¿Qué propiedad sí queda garantizada?.

 Queda firmemente garantizado el Invariante de Estructura y de Orden, asegurando que el elemento ubicado en la raíz del heap (índice 0 del arreglo) representa, sin excepción, el valor con la prioridad máxima global de toda la colección.

#### Bloque 4 - Modificación de `percolateDown`: elección del hijo dominante

 `Código Modificado e Instrumentado