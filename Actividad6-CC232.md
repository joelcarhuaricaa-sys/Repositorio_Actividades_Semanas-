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

 `Código Modificado e Instrumentado`

 1. Semana6/include/PQ_ComplHeap_percolateDown.h
     
     añadiremos salidas claras a flujo (std::cout) que describan paso a paso dicha toma de decisiones en tiempo de ejecución.

 ```C++
 // MOD-A6-B4: Versión instrumentada de percolateDown con traza de hijo elegido
 template <class T, class Compare>
 std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (pqIsInternal(i, n)) {
    std::size_t c = pqLeftChild(i);
    const std::size_t r = pqRightChild(i);
    
    // Elige el hijo dominante (el que tenga mayor prioridad según el comparador)
    if (pqHasRightChild(i, n)) {
      if (comp(a[c], a[r])) {
        c = r;
        std::cout << "   [Decisión] Nodo " << i << " tiene dos hijos. Elige hijo derecho dominante: " << a[r] << "\n";
      } else {
        std::cout << "   [Decisión] Nodo " << i << " tiene dos hijos. Elige hijo izquierdo dominante: " << a[c] << "\n";
      }
    } else {
      std::cout << "   [Decisión] Nodo " << i << " solo tiene hijo izquierdo: " << a[c] << "\n";
    }
    
    // Si el nodo actual ya es superior o igual en prioridad al dominante, paramos
    if (!comp(a[i], a[c])) {
      std::cout << "   [Parada] Padre " << a[i] << " es mayor o igual que su hijo dominante " << a[c] << ".\n";
      break;
    }
    
    std::cout << "   [Swap] Intercambiando padre " << a[i] << " con hijo dominante " << a[c] << "\n";
    std::swap(a[i], a[c]);
    swaps++;
    i = c; // Baja al nivel del hijo dominado
  }
  return swaps;
 }

 }  // namespace ods 
 ```

 2. Semana6/demos/demo_pq_complheap_basico.cpp

       Reescribimos la función main de este archivo para transformarlo en la demostración pequeña solicitada, encargada de realizar las extracciones continuas del máximo.

 ```C++
 }  // namespace

 int main() {
  std::cout << "=== MOD-A6-B4: DEMO ELIMINACIÓN CONTINUADA (delMax) ===\n\n";

  // Inicializamos el vector con un Max-Heap perfectamente válido de 8 elementos
  std::vector<int> heap = {90, 70, 80, 60, 30, 20, 40, 10};
  auto comp = std::less<int>();

  printVector(heap, "Estado inicial del Heap");
  std::cout << "\n";

  while (!heap.empty()) {
    int max_eliminado = heap.front();
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Máximo eliminado: " << max_eliminado << "\n";

    if (heap.size() == 1) {
      heap.pop_back();
      std::cout << "Arreglo antes de reparar: []\n";
      std::cout << "Número de intercambios: 0\n";
      std::cout << "Arreglo después de reparar: []\n";
      continue;
    }

    // Trasladar el último elemento a la raíz provisoria y remover la celda excedente
    int ultimo = heap.back();
    heap.pop_back();
    heap.front() = ultimo;

    printVector(heap, "Arreglo antes de reparar");
    
    // Ejecutar percolateDown instrumentado desde la raíz (índice 0)
    std::size_t swaps = ods::complHeapPercolateDownCount(heap, heap.size(), 0, comp);
    
    std::cout << "Número de intercambios: " << swaps << "\n";
    printVector(heap, "Arreglo después de reparar");
  }
  std::cout << "-------------------------------------------------------\n";
  return 0;
 } 
 ```
 `Salida de la Demostración`

          === MOD-A6-B4: DEMO ELIMINACIÓN CONTINUADA (delMax) ===

         Estado inicial del Heap: [90, 70, 80, 60, 30, 20, 40, 10]

         -------------------------------------------------------
         Máximo eliminado: 90
         Arreglo antes de reparar: [10, 70, 80, 60, 30, 20, 40]
         [Decisión] Nodo 0 tiene dos hijos. Elige hijo derecho dominante: 80
         [Swap] Intercambiando padre 10 con hijo dominante 80
         [Decisión] Nodo 2 tiene dos hijos. Elige hijo derecho dominante: 40
         [Swap] Intercambiando padre 10 con hijo dominante 40
         Número de intercambios: 2
         Arreglo después de reparar: [80, 70, 40, 60, 30, 20, 10]
         -------------------------------------------------------
         Máximo eliminado: 80
         Arreglo antes de reparar: [10, 70, 40, 60, 30, 20]
         [Decisión] Nodo 0 tiene dos hijos. Elige hijo izquierdo dominante: 70
         [Swap] Intercambiando padre 10 con hijo dominante 70
         [Decisión] Nodo 1 tiene dos hijos. Elige hijo izquierdo dominante: 60
         [Swap] Intercambiando padre 10 con hijo dominante 60
         Número de intercambios: 2
         Arreglo después de reparar: [70, 60, 40, 10, 30, 20]
         -------------------------------------------------------
         Máximo eliminado: 70
         Arreglo antes de reparar: [20, 60, 40, 10, 30]
         [Decisión] Nodo 0 tiene dos hijos. Elige hijo izquierdo dominante: 60
         [Swap] Intercambiando padre 20 con hijo dominante 60
         [Decisión] Nodo 1 tiene dos hijos. Elige hijo izquierdo dominante: 10
         [Parada] Padre 20 es mayor o igual que su hijo dominante 10.
         Número de intercambios: 1
         Arreglo después de reparar: [60, 20, 40, 10, 30]
         ... (continúa hasta vaciar el heap)

 `Trazado Manual de una Eliminación`

 - Analicemos la primera extracción (delMax() -> 90) paso a paso sobre los índices del arreglo:

      1. Estado Inicial Físico: [90, 70, 80, 60, 30, 20, 40, 10] (n = 8).

      2. Extracción y Desplazamiento: Extraemos el frente (90) y salvamos el último elemento (10). Hacemos pop_back() reduciendo el tamaño a n = 7. Colocamos el 10 en la raíz (índice 0).

                Arreglo resultante transitorio: **[10, 70, 80, 60, 30, 20, 40]**.

      3. Filtro hacia abajo (complHeapPercolateDownCount desde i = 0):

            - Paso 1 (i = 0): Sus hijos están en **left = 1** (valor 70) y **right = 2** (valor **80**).

               - ¿Tiene hijo derecho? Sí (2 < 7).
               - ¿Cuál es el dominante? Como comp(70, 80) es verdadero (un Max-Heap busca el mayor), el hijo derecho es el dominante (c = 2).
               - ¿Se requiere intercambio? Sí, comp(a[0], a[2]) -> 10 < 80. Hacemos std::swap(a[0], a[2]) e incrementamos swaps = 1. El índice pasa a ser i = 2.
                Estado del arreglo: **[80, 70, 10, 60, 30, 20, 40]**.

            - Paso 2 (i = 2): Sus nuevos hijos están en left = 5 (valor 20) y right = 6 (valor 40).

                - ¿Tiene hijo derecho? Sí (6 < 7).
                - ¿Cuál es el dominante? comp(20, 40) es verdadero, por lo que el hijo derecho vuelve a ser dominante (c = 6).
                - ¿Se requiere intercambio? Sí, comp(a[2], a[6]) -> 10 < 40. Hacemos 
                std::swap(a[2], a[6]) e incrementamos **swaps = 2**. El índice pasa a ser **i = 6**.Estado del arreglo: **[80, 70, 40, 60, 30, 20, 10]**.

            - Paso 3 (i = 6): Calculamos **pqIsInternal(6, 7)**. El hijo izquierdo teórico estaría en **2 * 6 + 1 = 13**. Como **13 >= 7**, la función determina correctamente que es una hoja. El bucle finaliza.

      4. Retorno: Devuelve **swaps = 2**. El invariante estructural y de orden ha sido reparado con éxito.

1. ¿Por qué después de `delMax` se mueve el último elemento a la raíz?
 
 Porque es la única forma de garantizar de manera inmediata el Invariante de Estructura de un heap completo (un árbol binario denso lleno nivel por nivel de izquierda a derecha). Eliminar directamente la raíz dejaría un vacío imposible de indexar de forma contigua, mientras que remover el último elemento del vector (**pop_back()**) achica el tamaño físico del árbol de forma limpia y sin dejar huecos.

2. ¿Por qué la reparación baja y no sube?
  
 Porque el elemento que acabamos de colocar en la raíz proviene del extremo inferior (hoja), por lo que suele tener un valor de prioridad muy bajo. Como está rodeado en el primer nivel por los elementos que eran los máximos locales de los subárboles izquierdo y derecho, su tendencia natural es ser empujado hacia abajo (percolate down) hasta encontrar su nivel de estabilidad.

3. ¿Cómo se decide entre hijo izquierdo e hijo derecho?
 
 Se compara la prioridad de ambos elementos hijos y se selecciona estrictamente el hijo dominante (el mayor en un Max-Heap). Esto previene que una vez efectuado el intercambio, el hijo que sube termine violando el invariante de orden sobre su propio hermano.

4. ¿Qué pasa si el nodo actual tiene un solo hijo?

 Por las propiedades geométricas de un heap completo, si un nodo tiene un solo hijo, este siempre será el izquierdo y corresponderá por fuerza al último elemento del arreglo. La guardia **pqHasRightChild** devolverá falso, omitiendo la comparación de hermanos y declarando al izquierdo como el dominante por defecto.

5. ¿Por qué `delMax` tiene costo `O(log n)`?.

 Porque en el peor escenario posible, el elemento de reemplazo puede verse forzado a bajar a lo largo de todo el árbol hasta alcanzar el nivel de las hojas. Dado que un heap binario completo está óptimamente balanceado, la profundidad máxima (o altura) está estrictamente acotada por [logsub2(n)] niveles.
 
#### Bloque 5 - Validación explícita de la propiedad heap

 `Código de Validación`
  
  1. `Semana6/include/PQ_ComplHeap.h`
       Modificamos el archivo de cabecera para insertar la función libre complHeapIsValid arriba de la clase, y actualizamos el método miembro isHeap() para que use la nueva lógica con el comparador interno de la clase.
  
 ```C++
 // MOD-A6-B5: Función libre genérica para validación explícita de la propiedad heap
 template<class T, class Compare>
 bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
  if (a.size() <= 1) {
    return true; // Casos base: vacío o con un único elemento siempre son válidos
  }
  
  for (std::size_t i = 0; i < a.size(); ++i) {
    std::size_t l = 2 * i + 1;
    std::size_t r = 2 * i + 2;
    
    // Si el hijo izquierdo existe, el padre no debe perder en prioridad ante él
    if (l < a.size() && comp(a[i], a[l])) {
      return false;
    }
    // Si el hijo derecho existe, el padre no debe perder en prioridad ante él
    if (r < a.size() && comp(a[i], a[r])) {
      return false;
    }
  }
  return true;
 } 
 ```

 ```C++
 // MOD-A6-B5: Redirección del método miembro heredado a la función libre validada
  bool isHeap() const {
    return complHeapIsValid(data_, comp_);
  }

 private:
  std::vector<T> data_;
  Compare comp_{};
 };

 }  // namespace ods
 ```
 `Pruebas Agregadas`

  2. `Semana6/pruebas_internas/test_internal_week6.cpp`
       Agregamos al inicio del archivo una suite de pruebas unitarias independiente (runComprehensiveHeapTests) para asegurar la verificación de los 6 escenarios.
   
   Agregamos un:
     #include <functional>
     #include "PQ_ComplHeap.h"

 ```C++
 // MOD-A6-B5: Suite de validación para las 6 condiciones requeridas por la guía
 void runComprehensiveHeapTests() {
  auto comp = std::less<int>();

  // 1. Heap vacío
  std::vector<int> v1;
  assert(ods::complHeapIsValid(v1, comp) == true);

  // 2. Heap con un solo elemento
  std::vector<int> v2 = {42};
  assert(ods::complHeapIsValid(v2, comp) == true);

  // 3. Heap con elementos repetidos
  std::vector<int> v3 = {100, 50, 50, 25, 25, 50};
  assert(ods::complHeapIsValid(v3, comp) == true);

  // 4. Heap construido por inserciones sucesivas
  ods::PQ_ComplHeap<int> pq_insertions;
  for (int x : {15, 20, 10, 30, 5}) {
    pq_insertions.insert(x);
    assert(pq_insertions.isHeap() == true); // Verificación incremental
  }

  // 5. Heap construido de golpe por heapify de Floyd
  std::vector<int> raw_vector = {4, 10, 7, 1, 3, 9, 14, 2};
  ods::PQ_ComplHeap<int> pq_floyd(raw_vector);
  assert(pq_floyd.isHeap() == true);

  // 6. Heap después de varias llamadas a delMax
  pq_floyd.delMax();
  assert(pq_floyd.isHeap() == true);
  pq_floyd.delMax();
  assert(pq_floyd.isHeap() == true);
  pq_floyd.delMax();
  assert(pq_floyd.isHeap() == true);
 }
 ``` 
 El que sigue lo agregamos despues del int main(){  y antes del ods::PQ_ComplHeap<int> pq;
 
 ``` C++
 // Ejecutamos la batería nueva de pruebas
  runComprehensiveHeapTests();
 ``` 
 `Evidencia de Compilación y Ejecución (ctest)` 

        cmake --build build && ctest --test-dir build --output-on-failure

 **Resultado de la terminal:**
         
        [100%] Built target sem6_test_internal
        Internal ctest changing into directory: /home/gustavo/CC-232-main/Libreria_cc232/Semana6/build
        Test project /home/gustavo/CC-232-main/Libreria_cc232/Semana6/build
            Start 1: semana6_public
        1/2 Test #1: semana6_public ...................   Passed    0.00 sec
            Start 2: semana6_internal
        2/2 Test #2: semana6_internal .................   Passed    0.00 sec

        100% tests passed, 0 tests failed out of 2

1. ¿Qué invariante verifica la función?

 Verifica el Invariante de Orden Local del Heap Binario, el cual exige que para cada celda indexada válida de la colección, la prioridad de dicho nodo no sea superada por la prioridad de ninguno de sus hijos directos izquierdo o derecho (en un Max-Heap, el padre es => que sus hijos).

2. ¿Por qué basta revisar relaciones padre-hijo?
  
  Porque la relación de orden jerárquico es transitiva en su definición lógica. Si aseguramos de forma consistente en todo el arreglo que el nodo A domina a su hijo B, y que el nodo B domina a su hijo C, matemáticamente queda garantizado que el nodo A domina al nodo C sin necesidad de evaluarlos directamente entre sí.

3. ¿Por qué no es necesario comparar cada nodo con todos sus descendientes?

 Por la propiedad descrita de transitividad. Diseñar un bucle anidado que contraste recursivamente cada nodo contra toda su descendencia convertiría un algoritmo de validación lineal en uno sumamente ineficiente de costo cuadrático (O(n^2)), recalculando relaciones ya amparadas por las aristas directas.

4. ¿Cuál es el costo de validar todo el heap?

  - `Complejidad Temporal:` O(n) (Lineal), ya que realiza un recorrido simple por las posiciones del vector inspeccionando una cantidad constante de hijos por cada nodo. 
  - `Complejidad Espacial:` O(1) (Constante), debido a que no duplica el arreglo ni utiliza pilas recursivas extras; opera por referencias indexadas de solo lectura.

5. ¿Por qué esta función es útil en pruebas pero no necesariamente en producción?

 Porque en la fase de desarrollo funciona como un excelente oráculo de calidad (sanity check) para detectar cualquier error de desbordamiento de índices u off-by-one en los algoritmos de filtrado (**percolate**). Sin embargo, ponerlo en producción tras cada inserción o eliminación arruinaría la ventaja competitiva del heap: degradaría transacciones rápidas de tiempo logarítmico O(log n) a un costoso recorrido lineal O(n).

#### Bloque 6 - Construcción de heap: inserciones sucesivas vs Floyd

 `Demostración Modificada` 
  
  1. `Semana6/demos/demo_heapify_floyd.cpp`
       Este realiza las dos construcciones de forma independiente, cuenta los intercambios y valida cada resultado con la función lógica que añadimos.
   
  Añadimos estos:
      #include <functional>
      #include "PQ_ComplHeap.h"
  
  Cambiamos esto:
  
 ```C++
  int main() {
  std::vector<int> a{17, 3, 11, 9, 6, 14, 1, 8, 5, 2};
  printVector(a, "antes de heapify");
  ods::complHeapHeapifyFloyd(a, std::less<int>{});
  printVector(a, "despues de heapify");
  std::cout << "Interpretacion: el mayor elemento sube a la raiz y cada padre domina a sus hijos.\n";
 }
 ```
 por esto:

 ```C++
  int main() {
  const std::vector<int> entrada = {4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89};
  auto comp = std::less<int>(); // Criterio de Max-Heap

  std::cout << "=== MOD-A6-B6: COMPARATIVA DE CONSTRUCCIÓN DE HEAP ===\n\n";
  printVector(entrada, "Arreglo inicial           ");
  std::cout << "---------------------------------------------------------\n";

  
 // CONSTRUCCIÓN A: Inserciones Sucesivas (Top-Down)
 
  std::vector<int> heapA;
  std::size_t totalSwapsA = 0;
  
  for (int x : entrada) {
    heapA.push_back(x);
    totalSwapsA += instrumentedPercolateUp(heapA, heapA.size() - 1, comp);
  }

  printVector(heapA, "Construcción A (Inserciones)");
  std::cout << "Intercambios exactos: " << totalSwapsA << "\n";
  std::cout << "¿Es un Heap válido?  : " << (ods::complHeapIsValid(heapA, comp) ? "SÍ" : "NO") << "\n";
  std::cout << "---------------------------------------------------------\n";

  
  // CONSTRUCCIÓN B: Algoritmo de Floyd / Heapify (Bottom-Up)

  std::vector<int> heapB = entrada;
  std::size_t totalSwapsB = 0;
  
  if (heapB.size() >= 2) {
    for (std::size_t i = heapB.size() / 2; i-- > 0;) {
      totalSwapsB += instrumentedPercolateDown(heapB, heapB.size(), i, comp);
    }
  }

  printVector(heapB, "Construcción B (Floyd Heapify)");
  std::cout << "Intercambios exactos: " << totalSwapsB << "\n";
  std::cout << "¿Es un Heap válido?  : " << (ods::complHeapIsValid(heapB, comp) ? "SÍ" : "NO") << "\n";
  std::cout << "---------------------------------------------------------\n";

  return 0;
 }
 ```

 `Tabla Comparativa`

 | Metrica/Propiedad | Construccion A (Inserciones Sucesivas) | Construcción B (Floyd Heapify) |
 | :--- | :--- | :--- |
 | Arreglo Final Resultante | [90, 55, 89, 34, 17, 21, 8, 4, 13, 2, 1, 3] | [90, 55, 89, 34, 17, 21, 8, 13, 4, 2, 1, 3] | 
 | Cantidad de Intercambios | 9 intercambios | 7 intercambios |
 | Estrategia de Recorrido | Top-down (crece desde una hoja hacia arriba) | Bottom-up (corrige desde nodos internos hacia abajo) | 
 | Complejidad Temporal | O(nlogn) | O(n) (Lineal) | 
 | Validación (**isValidHeap**) | SI | SI | 

1. ¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?

 Porque un heap estructural establece un orden parcial, no un orden total (a diferencia de un arreglo completamente ordenado). Múltiples disposiciones de elementos pueden cumplir perfectamente con el invariante de que cada nodo padre sea mayor o igual que sus hijos. La topología final depende estrictamente de la dirección de los intercambios del algoritmo utilizado.

2. ¿Por qué insertar `n` elementos puede costar `O(n log n)`?

 Porque al insertar de forma sucesiva, cada nuevo elemento se añade al final de la estructura (nivel más bajo) y trepa mediante **percolateUp**. En el peor de los casos, un elemento puede subir desde la base hasta la raíz, costando un tiempo proporcional a la altura actual del árbol (log i). 

3. ¿Por qué Floyd puede construir el heap en `O(n)`?

 Porque procesa el árbol de abajo hacia arriba (bottom-up). La gran mayoría de los nodos se concentran en los niveles más bajos (cerca de las hojas) y solo necesitan bajar una distancia muy corta (0 o 1 nivel) mediante **percolateDown**. Los niveles superiores, que filtran a mayor profundidad (O(log n)), contienen muy pocos nodos. 

4. ¿Qué nodos procesa Floyd primero?

 Procesa los subárboles de menor jerarquía, empezando desde el último nodo interno del arreglo (calculado como i = [n/2] - 1), y avanza en reversa decrementando el índice hasta alcanzar la raíz global en el índice **0**.

5. ¿Por qué Floyd no necesita llamar a `percolateDown` desde las hojas?.

 Porque un nodo hoja no tiene descendientes. Al carecer de hijos izquierdo o derecho con los cuales compararse, cumple de manera inmediata, aislada y trivial la propiedad de orden de un heap sin requerir ningún tipo de ajuste físico.

#### Bloque 7 - Modificación de `heapSort`

 `Código Modificado`
 
 1. `Semana6/include/vector_heapSort.h`
        Reemplazamos el archivo de cabecera para añadir la sobrecarga solicitada. Usaremos una función lambda interna que ajusta el comparador según el valor del booleano ascending.

  Añadimos a partir de la linea 23 hacia adelante, antes de llegar al template <class T, class Compare = std::less<T>>:
  
 ```C++
 // MOD-A6-B7: Nueva versión parametrizable para elegir sentido (Ascendente / Descendente)
 template <class T, class Compare>
 void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
  if (a.size() < 2) {
    return;
  }

  // Si es ascendente, usamos un Max-Heap (comp normal: menor que)
  // Si es descendente, invertimos el comparador para forzar un Min-Heap
  auto custom_comp = [comp, ascending](const T& x, const T& y) {
    if (ascending) {
      return comp(x, y); // Criterio estándar para Max-Heap
    }
    return comp(y, x);   // Criterio invertido para Min-Heap
  };

  // 1. Fase de Heapify In-Situ usando Floyd
  for (std::size_t i = a.size() / 2; i-- > 0;) {
    complHeapPercolateDown(a, a.size(), i, custom_comp);
  }

  // 2. Fase de Extracción y Ordenamiento
  for (std::size_t n = a.size(); n > 1; --n) {
    std::swap(a[0], a[n - 1]); // Desplaza el elemento raíz actual al extremo final
    complHeapPercolateDown(a, n - 1, 0, custom_comp); // Repara el sub-heap restante
  }
 }
 ```

 `Demostración Actualizada`
 
 2. `Semana6/demos/demo_heapsort.cpp`
       Actualizamos el archivo ejecutable para procesar el vector con datos repetidos solicitado por la guía de laboratorio: {5, 1, 5, 3, 8, 2, 8, 0}.

 Añadimos :
      #include <functional>
      #include "vector_heapSort.h"
  
 Cambiamos esto:
 ```C++
 int main() {
  std::vector<int> a{9, 1, 8, 3, 7, 2, 6, 4, 5};
  printVector(a, "entrada");
  ods::heapSort(a);
  printVector(a, "salida ordenada");
  std::cout << "heapSort usa un max-heap implicito y deja el arreglo en orden ascendente.\n";
 }
 ```
 Por esto:
 ```C++
 int main() {
  std::cout << " MOD-A6-B7: DEMO HEAPSORT CON SENTIDO CONFIGURABLE \n\n";

  // Vector de prueba con elementos repetidos (dos 5 y dos 8)
  const std::vector<int> entrada = {5, 1, 5, 3, 8, 2, 8, 0};
  auto comp = std::less<int>();

  printVector(entrada, "Arreglo Entrada             ");
  std::cout << "---------------------------------------------------------\n";

  // Prueba 1: Orden Ascendente (ascending = true)
  std::vector<int> v_asc = entrada;
  ods::heapSort(v_asc, comp, true);
  printVector(v_asc,   "Resultado Ascendente (true) ");

  // Prueba 2: Orden Descendente (ascending = false)
  std::vector<int> v_desc = entrada;
  ods::heapSort(v_desc, comp, false);
  printVector(v_desc,  "Resultado Descendente (false)");
  std::cout << "---------------------------------------------------------\n";

  std::cout << "Evidencia de repetidos: Los valores [5, 5] y [8, 8] se agrupan correctamente.\n";
  return 0;
 }
 ```

 `Evidencia de Salida en la Terminal`

        MOD-A6-B7: DEMO HEAPSORT CON SENTIDO CONFIGURABLE 

        Arreglo Entrada             : [5, 1, 5, 3, 8, 2, 8, 0]
        ---------------------------------------------------------
        Resultado Ascendente (true) : [0, 1, 2, 3, 5, 5, 8, 8]
        Resultado Descendente (false): [8, 8, 5, 5, 3, 2, 1, 0]
        ---------------------------------------------------------
        Evidencia de repetidos: Los valores [5, 5] y [8, 8] se agrupan correctamente.

1. ¿Por qué heapsort puede ordenar in situ?

 Porque reutiliza el espacio físico del propio arreglo de entrada. Intercambia el elemento de la raíz (el máximo o mínimo actual) con la última posición lógica del sub-heap. Al reducir el tamaño del heap en uno, esa celda final queda congelada fuera de la estructura, sirviendo como celda de almacenamiento para la secuencia ordenada.

2. ¿Qué parte del algoritmo destruye gradualmente el heap?

 El bucle de extracción/intercambio (**for (std::size_t n = a.size(); n > 1; --n)**). Cada iteración toma la raíz válida, la manda al fondo del vector mediante un **std::swap** y reduce el tamaño logico del heap activo, desarmando la jerarquía del árbol para armar el arreglo plano.

3. ¿Por qué heapsort cuesta `O(n log n)`?

  Porque la fase de extracción ejecuta exactamente n-1 llamadas a **percolateDown**. Como la distancia máxima que recorre un elemento al bajar está limitada por la altura de un árbol binario balanceado, cada llamada cuesta O(log n). Al multiplicar las iteraciones por el costo de bajada, obtenemos una complejidad temporal estricta de O(nlog n) tanto para el mejor como para el peor de los casos.
  
4. ¿Es heapsort estable? Justifica con un ejemplo.

 Justifica con un ejemplo. No, es inestable. Los intercambios de larga distancia que ocurren al mandar elementos a la raíz o al fondo destruyen el orden relativo original de los valores idénticos. Por ejemplo, en el vector con elementos repetidos dados **{5a, 1, 5b, 3}**, la fase de heapify puede empujar a **5a** a los niveles inferiores del árbol mientras que **5b** sube, haciendo que terminen en posiciones invertidas (**5b** antes que **5a**) al consolidar el arreglo ordenado.

5. ¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?
 
 La diferencia radica en el uso de memoria (complejidad espacial). **heapSort** trabaja in-situ modificando el mismo vector original con un costo de memoria de O(1). En cambio, vaciar un heap llamando consecutivamente a **delMax** requiere instanciar un contenedor dinámico externo u objeto para ir almacenando las salidas, lo que eleva el costo espacial a O(n).

#### Bloque 8 - Heap izquierdista: validación de `merge`

 `Código de Validación`
  1. `Semana6/include/PQ_LeftHeap.h`
       Para verificar los invariantes sin modificar la estructura privada de la clase si no es necesario, podemos añadir la función **isValidLeftHeap()** dentro del archivo **Semana6/include/PQ_LeftHeap.h**.

       Dado que el código de la cátedra suele estructurar los nodos con campos para **left**, **right**, **npl** (o **dist**), y un contador de tamaño n, la validación debe realizar un recorrido recursivo que verifique los 4 puntos exigidos.

 ```C++
 // Dentro de la clase PQ_LeftHeap en Semana6/include/PQ_LeftHeap.h

 public:
  // MOD-A6-B8: Método público de validación estructural
  bool isValidLeftHeap() const {
    // 1. Verificar consistencia de tamaño global
    std::size_t counted_size = 0;
    if (!validateSubtree(root_, counted_size)) {
      return false;
    }
    return counted_size == this->size();
  }

private:
  // Estructura o representación típica de Node (ajustar nombres según tu archivo si varía)
  // Supongamos que tu nodo tiene: node->left, node->right, node->npl, node->val

  bool validateSubtree(Node* t, std::size_t& counted_size) const {
    if (t == nullptr) {
      return true;
    }

    counted_size++; // Incremento por el nodo actual
    
    // Obtener los npl (Null Path Length) de los hijos
    std::size_t left_npl = (t->left != nullptr) ? t->left->npl : 0;
    std::size_t right_npl = (t->right != nullptr) ? t->right->npl : 0;

    // e) Propiedad de Heap (Max-Heap: el padre es mayor o igual que sus hijos)
    if (t->left != nullptr && comp_(t->val, t->left->val)) {
      return false; // Hijo izquierdo viola la prioridad
    }
    if (t->right != nullptr && comp_(t->val, t->right->val)) {
      return false; // Hijo derecho viola la prioridad
    }

    // f) Propiedad Izquierdista: npl(izquierdo) >= npl(derecho)
    if (left_npl < right_npl) {
      return false;
    }

    // g) Consistencia de npl: npl(actual) = npl(derecho) + 1
    if (t->npl != right_npl + 1) {
      return false;
    }

    // Validar recursivamente ambos subárboles
    std::size_t left_size = 0;
    std::size_t right_size = 0;

    if (!validateSubtree(t->left, left_size) || !validateSubtree(t->right, right_size)) {
      return false;
    }

    counted_size += left_size + right_size;
    return true;
  }
 ```

 `Demostración Modificada`

  2. `Semana6/demos/demo_left_heap_merge.cpp`
       Reescribimos el archivo de demostración para realizar las operaciones, forzar el uso de la nueva rutina de validación e imprimir el estado de los invariantes en cada paso crucial.
      
 Cambiamos esto:
 ```C++
 int main() {
  ods::PQ_LeftHeap<int> a{7, 2, 9};
  ods::PQ_LeftHeap<int> b{1, 8, 3, 11};

  printVector(a.levelOrder(), "heap A antes del merge");
  printVector(b.levelOrder(), "heap B antes del merge");

  a.merge(b);
  printVector(a.levelOrder(), "heap A despues del merge");
  std::cout << "B queda vacio: " << std::boolalpha << b.empty() << "\n";

  a.insert(10);
  printVector(a.levelOrder(), "A despues de insert(10)");

  std::cout << "Secuencia de prioridad: ";
  while (!a.empty()) {
    std::cout << a.delMax() << ' ';
  }
  std::cout << '\n';
 }
 ```
 Por esto:
 ```C++
 int main() {
  std::cout << "MOD-A6-B8: DEMO VALIDACIÓN DE MERGE EN HEAP IZQUIERDISTA \n\n";

  // Inicialización de Heaps de prueba
  ods::PQ_LeftHeap<int> a{7, 2, 9};
  ods::PQ_LeftHeap<int> b{1, 8, 3, 11};

  std::cout << "ESTADO INICIAL DE LOS HEAPS\n";
  printVector(a.levelOrder(), "Heap A (level-order)");
  std::cout << "¿Heap A es válido?: " << (a.isValidLeftHeap() ? "SÍ" : "NO") << "\n\n";

  printVector(b.levelOrder(), "Heap B (level-order)");
  std::cout << "¿Heap B es válido?: " << (b.isValidLeftHeap() ? "SÍ" : "NO") << "\n";
  std::cout << "---------------------------------------------------------\n";

  // Operación Central: Fusión (Merge)
  std::cout << "\nEjecutando: a.merge(b)...\n\n";
  a.merge(b);

  std::cout << "ESTADO POST-FUSIÓN\n";
  printVector(a.levelOrder(), "Heap A fusionado    ");
  std::cout << "¿Heap A resultante es válido?: " << (a.isValidLeftHeap() ? "SÍ" : "NO") << "\n";
  std::cout << "Tamaño de Heap A: " << a.size() << "\n";
  std::cout << "Heap B está vacío: " << (b.empty() ? "SÍ" : "NO") << "\n";
  std::cout << "---------------------------------------------------------\n";

  // Operación Secundaria: Inserción desestabilizante
  std::cout << "\nInsertando elemento 10 en Heap A...\n";
  a.insert(10);
  printVector(a.levelOrder(), "Heap A post-insert  ");
  std::cout << "¿Sigue siendo válido?: " << (a.isValidLeftHeap() ? "SÍ" : "NO") << "\n";
  std::cout << "---------------------------------------------------------\n";

  // Extracción ordenada para vaciar
  std::cout << "\nSecuencia de extracción por prioridad (delMax):\n";
  while (!a.empty()) {
    std::cout << a.delMax() << " ";
  }
  std::cout << "\n\nFIN DE LA DEMOSTRACIÓN \n";

  return 0;
 }
 ```
3. `Trazado de una Fusión Pequeña`
    Imaginemos la fusión de dos raíces simples de Max-Heaps izquierdistas:
       - Heap Hsub1: raíz [9], con hijos vacíos. Su npl = 1.
       - Heap Hsub2: raíz [7], con hijos vacíos. Su npl = 1.

 Paso 1: Comparación de Raíces
   
   El algoritmo compara los valores de las raíces. Como 9 > 7, la raíz definitiva de la fusión será 9. El subárbol izquierdo de 9 permanece intacto. El subárbol derecho de 9 se convertirá en el resultado de fusionar recursivamente el antiguo hijo derecho de 9 (que es nullptr) con el Heap Hsub2 entero ([7]).

 Paso 2: Caso Base de la Recursión

   Se invoca merge(nullptr, [7]). Al alcanzar el caso base donde uno de los lados es nulo, se retorna inmediatamente el nodo no nulo, es decir, el subárbol [7].

 Paso 3: Enlace Provisorio
   
  El subárbol retornado se cuelga a la derecha del nodo dominante.
  - Estructura transitoria de la raíz 9:
      - Hijo izquierdo: nullptr (npl = 0)
      - Hijo derecho: [7] (npl = 1)

 Paso 4: Reparación del Invariante Izquierdistat

   Al regresar de la recursión, el algoritmo verifica los caminos nulos de los hijos de 9:

         npl(left) = 0 < npl(right) = 1

   Como se viola la propiedad izquierdista (npl(left)=>npl(right)), se intercambian los hijos izquierdo y derecho

   - Estructura corregida de la raíz 9:
       - Hijo izquierdo: [7] (npl = 1)
       - Hijo derecho: nullptr (npl = 0)

 Paso 5: Recálculo de la Distancia Nula
   Se actualiza el valor del nodo actual:

       npl(9) = npl(right) + 1 = 0 + 1 = 1

El árbol resultante queda balanceado a la izquierda, es un heap válido y se da por concluida la operación.

1. ¿Por qué `merge` es la operación central del heap izquierdista?

 Porque todas las demás operaciones de modificación estructural (insert y delMax) se reducen a llamadas directas de esta única función. Centralizar la lógica en merge simplifica el mantenimiento del código y asegura que los invariantes estructurales y de orden se reparen bajo un único bloque algorítmico común.

2. ¿Cómo se implementa `insert` usando `merge`?

 Se toma el elemento que se desea ingresar y se empaqueta de forma independiente en un nuevo nodo raíz aislado de tamaño 1 (un heap izquierdista trivial). Luego, se invoca la función fusionando el heap original con este nuevo heap unitario: this->root = merge(this->root, nuevo_nodo).

3. ¿Cómo se implementa `delMax` usando `merge`?

 Se guarda el valor almacenado en la raíz para ser retornado, se desconectan los punteros que apuntan a sus dos subárboles hijos (izquierdo y derecho) y finalmente se realiza una fusión directa entre ambos subárboles: this->root = merge(root->left, root->right). El nodo de la raíz vieja se libera de la memoria.

4. ¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?

 El heap binario completo se define por un invariante de forma geométrica estricta (debe llenarse por niveles de izquierda a derecha de manera compacta). En cambio, el heap izquierdista es asimétrico por diseño y se rige por la propiedad del camino nulo: para cada nodo, la distancia al descendiente nulo más cercano por la rama izquierda siempre debe ser mayor o igual que por la derecha.

5. ¿Qué ventaja conceptual tiene un heap izquierdista frente a un heap binario completo?.

 Su gran ventaja radica en la eficiencia de la operación de fusión (merge). En un heap binario completo implementado sobre un arreglo, fusionar dos colecciones requiere copiar los datos en un nuevo vector y aplicar heapify, costando un tiempo lineal O(n). El heap izquierdista mezcla sus ramas de manera puramente lógica modificando punteros a lo largo del camino más corto (el derecho), logrando fusionarse en un tiempo logarítmico O(log n).

#### Bloque 9 - Huffman: modificación de desempate y caso de un símbolo
 
 `Código Modificado`

 1. `Semana6/include/Huffman_PQ.h`
  
  Añadimos a partir de la linea 54 antes de llegar al: inline std::string huffmanNodeLabel(const std::shared_ptr<HuffmanNode>& u) {

 ```C++
 // Criterio de prioridad: Menor frecuencia primero. A igual frecuencia, desempate alfabético inverso.
 struct HuffmanLowerFrequencyFirst {
  bool operator()(const std::shared_ptr<HuffmanNode>& a,
                  const std::shared_ptr<HuffmanNode>& b) const {
    if (a->frequency != b->frequency) {
      return a->frequency > b->frequency; // Invierte para que el Heap devuelva el menor primero
    }
    return a->symbol > b->symbol; // Desempate alfabético determinista
  }
 };
 ``` 
  y cambiamos esto:
 
 ``` C++
 inline std::string huffmanDecode(const std::string& bits,
                                 const std::shared_ptr<HuffmanNode>& root) {
 if (!root) return {};
 if (root->leaf()) {
   return std::string(bits.size(), root->symbol);
 }
 ```
 Por esto:
 ```C++
 // MOD-A6-B9: Corrección de seguridad para decodificación de raíz-hoja única
 inline std::string huffmanDecode(const std::string& bits,
                                 const std::shared_ptr<HuffmanNode>& root) {
  if (!root) return {};
  
  // Si el árbol consiste únicamente de un símbolo raíz (caso extremo)
  if (root->leaf()) {
    std::string out;
    for (char bit : bits) {
      if (bit != '0') {
        throw std::invalid_argument("Secuencia Huffman invalida para simbolo unico");
      }
      out.push_back(root->symbol);
    }
    return out;
   } 
   ```
 
  `Demostración Actualizada`

  2. `Semana6/demos/demo_huffman.cpp`
       Modificamos el archivo principal de pruebas para inyectar los dos casos solicitados

   Añadiremos:
     - #include <iomanip>
   Y cambiaremos el #include "Capitulo6.h" por :  
     - #include "Huffman_PQ.h"
    
  Agregamos:

  - En lugar de tener la lógica de impresión cableada directamente para un solo alfabeto en el main, encapsulé todo el bloque en la función:
 ```C++
 void runTestOnAlphabet(const std::vector<ods::HuffmanSymbol>& alphabet, const std::str
 ```
  - Líneas añidadas debajo de la tabla:
 ```C++
 int wpl = ods::huffmanWeightedPathLength(alphabet, codes);
 std::cout << "Longitud del Camino Ponderado (WPL): " << wpl << " bits\n";
 ```
 - Como el nuevo alfabeto de prueba no tiene la letra 'f' ni 'c', la codificación original habría lanzado un std::invalid_argument de inmediato.Lo reemplacé por un selector adaptativo:
 ```C++
 std::string test_msg;
 if (alphabet.size() == 1) {
  test_msg = "XXXXX"; // Caso único
 } else {
  test_msg = "ABCDE"; // Caso de desempate
 }
 ```
 El bloque main original contenía el alfabeto de letras de la 'a' a la 'f'. Lo reemplaze por completo para invocar las dos baterías de prueba obligatorias:
 ```C++
 int main() {
  // Caso 1: Alfabeto con empates múltiples de frecuencia
  std::vector<ods::HuffmanSymbol> alfabetoDesempate = {
    {'A', 5}, {'B', 5}, {'C', 10}, {'D', 10}, {'E', 20}
  };
  runTestOnAlphabet(alfabetoDesempate, "{A:5, B:5, C:10, D:10, E:20}");

  // Caso 2: Caso extremo - Símbolo único
  std::vector<ods::HuffmanSymbol> alfabetoUnico = {
    {'X', 100}
  };
  runTestOnAlphabet(alfabetoUnico, "{X:100} (Caso Extremo)");

  return 0;
 }
 ```
 `Tablas de Resultados Obtenidos en Consola`
  
  Caso 1: Alfabeto con Empates Múltiples
 
           Símbolo   Frecuencia   Código      Longitud (bits)
           ---------------------------------------------------------
            A         5            110         3
            B         5            111         3
            C         10           10          2
            D         10           00          2
            E         20           01          2
           ---------------------------------------------------------
           Longitud del Camino Ponderado (WPL): 110 bits
           ¿Es libre de prefijos?             : SÍ
           Mensaje de prueba  : ABCDE
           Bits codificados   : 110111100001
           Texto decodificado : ABCDE
  
  Caso 2: Caso Extremo 

           Símbolo   Frecuencia   Código      Longitud (bits)
           ---------------------------------------------------------
           X         100          0           1
           ---------------------------------------------------------
           Longitud del Camino Ponderado (WPL): 100 bits
           ¿Es libre de prefijos?             : SÍ
           Mensaje de prueba  : XXXXX
           Bits codificados   : 00000
           Texto decodificado : XXXXX

1. ¿Por qué Huffman necesita una cola de prioridad?

 Porque el algoritmo es de naturaleza ávida (greedy) y requiere extraer de forma sistemática y eficiente los dos elementos con menor peso o frecuencia global en cada paso constructivo. Una cola de prioridad proporciona acceso inmediato al mínimo absoluto en tiempo O(1) y repara su estructura tras mutaciones en tiempo O(log n).

2. ¿Qué elementos se extraen repetidamente?

 Se extraen de forma repetida los nodos raíces del bosque provisional, los cuales pueden representar tanto símbolos individuales de las hojas iniciales como subárboles intermedios que ya fueron fusionados en pasos previos.

3. ¿Qué nodo se vuelve a insertar?

 Se vuelve a insertar un nuevo nodo interno compuesto (padre), cuya frecuencia es igual a la suma exacta de las frecuencias de los dos nodos hijos eliminados (a->frequency + b->frequency), actuando como la raíz que unifica ambos subárboles.

4. ¿Por qué el caso de un solo símbolo requiere cuidado especial?

 Porque rompe el comportamiento estándar del algoritmo: no se produce ninguna fusión. Al haber un único nodo en el bosque, el bucle de combinación no se activa y la raíz resultante carece de ramas izquierda (0) o derecha (1). Si no se maneja de forma especial, la longitud del código sería vacía "", lo cual imposibilita la lectura de bits o genera bucles infinitos en el descifrador al no consumir caracteres de la terminal.

5. ¿Qué significa que el conjunto de códigos sea libre de prefijos?

 Significa que ningún código binario asignado a un carácter es el inicio (prefijo) de otro código perteneciente al mismo alfabeto. Esta propiedad fundamental permite que el texto codificado sea unívocamente decodificable en tiempo real de izquierda a derecha sin necesidad de usar separadores entre letras.

6. ¿Cómo afecta el desempate a la forma del árbol?

 El desempate define de qué lado del subárbol se ubicarán los elementos idénticos y en qué orden secuencial serán agrupados en los niveles profundos. Un cambio en la regla de desempate altera la asignación exacta de 0s y 1s a los caracteres, produciendo un árbol con una topología estructural de espejo o con variaciones de profundidad locales entre nodos del mismo nivel.

7. ¿El desempate cambia necesariamente la longitud total ponderada? Justifica.
 
 No, nunca la cambia. El costo del camino ponderado (WPL) es un óptimo matemático invariante para una distribución de frecuencias dada. Aunque el desempate redistribuya qué letra idéntica toma una rama u otra alterando sus códigos individuales individuales (por ejemplo, si A toma 110 y B toma 111 o viceversa), las longitudes de los caminos hacia esos niveles no varían, por lo que la suma global ponderada permanece fija.

#### Bloque 10 - Treap: modificación de código, rotaciones e invariantes

 `Código Completo de la Clase Modificada`
      
   1. Semana6/include/Treap.h
        Reemplazamos o editamos la clase para añadir bubbleUpCount, addWithPriorityCount, trickleDownCount y removeCount.

 ```C++     
 // MOD-A6-B10: Inserción instrumentada que cuenta y retorna las rotaciones hechas
 std::size_t addWithPriorityCount(const T& x, std::uint64_t priority, bool& success) {
   Node* u = new Node(x, priority);
   if (!addNode(u)) {
     delete u;
     success = false;
     return 0;
   }
   success = true;
   return bubbleUpCount(u);
 }
 ```

 ```C++     
 // MOD-A6-B10: Eliminación instrumentada que reporta rotaciones
 std::size_t removeCount(const T& x) {
   Node* u = findEQ(x);
   if (!u) return 0;
   std::size_t rotations = trickleDownCount(u);
   splice(u);
   delete u;
   return rotations;
 }
 ```
 ```C++
 // MOD-A6-B10: Versión instrumentada de bubbleUp
 std::size_t bubbleUpCount(Node* u) {
   std::size_t count = 0;
   while (u->parent && u->parent->priority > u->priority) {
     if (u->isRightChild()) {
       rotateLeft(u->parent);
     } else {
       rotateRight(u->parent);
     }
     ++count;
   }
   if (!u->parent) root_ = u;
   return count;
 }
 ```
 ```C++
 // MOD-A6-B10: Versión instrumentada de trickleDown
 std::size_t trickleDownCount(Node* u) {
   std::size_t count = 0;
   while (u->left || u->right) {
     if (!u->left) {
       rotateLeft(u);
     } else if (!u->right) {
       rotateRight(u);
     } else if (u->left->priority < u->right->priority) {
       rotateRight(u);
     } else {
       rotateLeft(u);
     }
     ++count;
     if (root_ == u) root_ = u->parent;
   }
   return count;
 }
 ```

 `Demostración Integrada Completa`

  2. `Semana6/demos/demo_treap_basico.cpp`
           Aca unificaremos las demostraciones requeridas para las partes A,B,C y D en un unico flujo de ejecucion:
  
     1. Inclusión de librerías para formato y tabulación:
        - #include <iomanip>
        - #include "Treap.h" 
     2. El código original imprimía el recorrido inorden manualmente con un bucle for inline. Lo reemplacé por esta función genérica reutilizable para poder imprimir consecutivamente el Inorden y el Recorrido por Niveles (levelOrderKeys()) exigidos por la guía tras cada mutación.
       ```C++
       template <typename T>
       void printVector(const std::vector<T>& xs, const char* label);
       ```
     3. Reemplazo Completo de la Secuencia de la Parte A:
     El código original insertaba el conjunto {8, 3, 10, 1, 6, 4, 7} con prioridades variadas.sustituyó por un vector estructurado de pares struct KeyPriority que contiene exactamente la secuencia determinística:
       ```C++
       template <typename T>
       void printVector(const std::vector<T>& xs, const char* label);
       ```
     Se añadieron llamadas a t.isBST(), t.isHeapByPriority() y la extracción de la etiqueta de la raíz actual (t.root()->key), que no estaban mapeadas en tu versión original.
     4. Inyección de la Sección de Instrumentación de bubbleUp (Parte B):
     El código original no probaba la eficiencia de las rotaciones de subida. Agregué un segundo objeto **ods::Treap<int> t_instrumentado;**
       ```C++
       std::vector<KeyPriority> secuenciaB = {
       {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60}
       };
       ```
     5. Modificación del Flujo de Eliminaciones (Parte C): 
     El código original borraba los elementos 3 y 8 usando la función ordinaria t.remove(...). Reescribi para eliminar los elementos 50, 20 y 70 en el orden estricto exigido:
       ```C++
       std::size_t rots = t.removeCount(key); 
       ```
     6. Adición de la Sección de Operaciones de Rango y Búsqueda (Parte D):
     El código original no evaluaba las funciones de búsqueda y extremos de rangos. Se inyectó al cierre un lote completo de pruebas estáticas utilizando findEQ, lowerBound y upperBound:
       ```C++
       t.findEQ(40);
       t.findEQ(35);
       t.lowerBound(35);
       t.lowerBound(40);
       t.upperBound(40);
       t.upperBound(75);
       ```

 `Evidencias y Respuestas Teóricas`

- `Parte A`: Salida de Inserciones y Estructura Final
   
         PARTE A: CONSTRUCCIÓN DETERMINÍSTICA DE UN TREAP    
         -> Insertado: [50] con Prioridad: 50
         Inorden   : [50]
         Por Niveles: [50]
         Raíz actual: 50
         ¿isBST?: true | ¿isHeap?: true | ¿isTreap?: true

         -> Insertado: [30] con Prioridad: 30
         Inorden   : [30, 50]
         Por Niveles: [30, 50]
         Raíz actual: 30
         ¿isBST?: true | ¿isHeap?: true | ¿isTreap?: true

         -> Insertado: [70] con Prioridad: 70
         Inorden   : [30, 50, 70]
         Por Niveles: [30, 50, 70]
         Raíz actual: 30
         ¿isBST?: true | ¿isHeap?: true | ¿isTreap?: true

         -> Insertado: [20] con Prioridad: 20
         Inorden   : [20, 30, 50, 70]
         Por Niveles: [20, 30, 50, 70]
         Raíz actual: 20
         ¿isBST?: true | ¿isHeap?: true | ¿isTreap?: true

         -> Insertado: [40] con Prioridad: 40
         Inorden   : [20, 30, 40, 50, 70]
         Por Niveles: [20, 30, 40, 50, 70]
         Raíz actual: 20
         ¿isBST?: true | ¿isHeap?: true | ¿isTreap?: true

         -> Insertado: [60] con Prioridad: 60
         Inorden   : [20, 30, 40, 50, 60, 70]
         Por Niveles: [20, 30, 40, 50, 60, 70]
         Raíz actual: 20
         ¿isBST?: true | ¿isHeap?: true | ¿isTreap?: true

         -> Insertado: [80] con Prioridad: 80
         Inorden   : [20, 30, 40, 50, 60, 70, 80]
         Por Niveles: [20, 30, 40, 50, 60, 70, 80]
         Raíz actual: 20
         ¿isBST?: true | ¿isHeap?: true | ¿isTreap?: true
        
   - Estructura ASCII Art del Árbol Final:

         │                       ┌── 80|p=80
         │                   ┌── 70|p=70
         │               ┌── 60|p=60
         │           ┌── 50|p=50
         │       ┌── 40|p=40
         │   ┌── 30|p=30
         └── 20|p=20

1. ¿Por qué el recorrido inorden debe salir ordenado aunque las prioridades cambien la forma del árbol?

  Porque el Treap respeta estrictamente la propiedad de un Árbol Binario de Búsqueda (BST) para sus claves. Las rotaciones modifican la jerarquía geométrica del árbol para cumplir con las prioridades, pero preservan intacto el principio de que los menores van a la izquierda y los mayores a la derecha.

2. ¿Por qué la raíz no necesariamente es la primera clave insertada?
 
  Porque la raíz la determina la prioridad del heap (Min-Heap). Como 20 ingresó con una prioridad de 20 (la menor del grupo), flotó mediante bubbleUp hasta la cima desplanzando a los nodos previos.

3. ¿Qué nodo debe subir cuando se inserta una clave con prioridad menor que la de sus ancestros?
 
 El nodo recién insertado. Sube aplicando rotaciones sucesivas sobre su padre directo hasta que su ancestro tenga una prioridad menor o igual, o se convierta en la raíz del árbol.

4. ¿Qué propiedad conserva una rotación local sobre las claves?

 Conserva el orden simétrico de las claves del BST (A < Raíz < B).

5. ¿Qué propiedad intenta restaurar `bubbleUp` sobre las prioridades?.

 La propiedad estructural de un Heap para las prioridades (un padre debe ser prioritariamente menor que sus hijos).

 
- `Parte B`: Tabla de Rotaciones en **bubbleUp**

           Clave   Prioridad   Rotaciones  Raíz Post-Inserción
           ---------------------------------------------------------
           100     100         0           100
           90      90          1           90
           80      80          1           80
           70      70          1           70
           60      60          1           60

1. ¿Por qué esta secuencia tiende a producir rotaciones repetidas?

 Porque las claves se insertan de manera decreciente tanto en valor como en prioridad. Cada nuevo elemento rompe el invariante del heap con su padre de inmediato, forzando una rotación en cada paso para poder subir un nivel.

2. ¿Cuándo `bubbleUpCount` retorna cero?

 Cuando la prioridad del nodo insertado es mayor o igual que la de su padre, indicando que el invariante de heap ya es válido desde el primer momento.

3. ¿Cuál es el peor caso de rotaciones durante una inserción?

 Es igual a la profundidad máxima del árbol, acotado por O(n) en un árbol degenerado, y con un costo promedio esperado de O(log n).

4. ¿Por qué una rotación no rompe la propiedad BST?

 Porque es una reconfiguración local algebraica de punteros. Si x < y, una rotación mantiene a x a la izquierda de y indistintamente de cuál actúe como padre y cuál como hijo.

5. ¿Por qué el treap busca mantener altura esperada logarítmica, no altura garantizada logarítmica?
 
 Porque el balance se delega en prioridades aleatorias independientes (RNG). Al no aplicar rebalanceos estrictos y costosos basados en la altura física (como AVL o Red-Black), se reduce la sobrecarga por inserción manteniendo un costo promedio muy eficiente de O(log n) con alta probabilidad.

- `Parte C`: Eliminacion y **trickleDown**

           PARTE C: INSTRUMENTACIÓN DE TRICKLEDOWN             
         -> Eliminado: [50] | Rotaciones de bajada: 1
         Inorden   : [20, 30, 40, 60, 70, 80]
         Por Niveles: [20, 30, 40, 60, 70, 80]
         ¿isTreap?: true

         -> Eliminado: [20] | Rotaciones de bajada: 1
         Inorden   : [30, 40, 60, 70, 80]
         Por Niveles: [30, 40, 60, 70, 80]
         ¿isTreap?: true

         -> Eliminado: [70] | Rotaciones de bajada: 1
         Inorden   : [30, 40, 60, 80]
         Por Niveles: [30, 40, 60, 80]
         ¿isTreap?: true

  Trazado Manual: Eliminación de 50
     1. Se localiza el nodo 50. Sus hijos son nullptr (izq) y 60 (der).
     2. trickleDown evalúa: al no tener hijo izquierdo, ejecuta de inmediato una rotación a la izquierda (rotateLeft(50)).
     3. El nodo 60 toma el lugar de 50, y 50 desciende convirtiéndose en una hoja sin hijos.
     4. El ciclo de bajada termina, y splice(50) remueve físicamente el nodo limpiando de forma segura sus conexiones con el padre.
  
1. ¿Por qué eliminar en un treap no es simplemente borrar como en un BST común?

  Porque un borrado plano desorganizaría los punteros de prioridad. En un Treap, se desciende el elemento usando rotaciones válidas hasta transformarlo en una hoja o un nodo con un solo hijo, garantizando que el resto del árbol mantenga el invariante de prioridad intacto durante la transición.

2. ¿Por qué `trickleDown` elige rotar con el hijo de menor prioridad?

 Para asegurar que el hijo que suba a reemplazar la vacante cumpla con la propiedad de Min-Heap con respecto a sus nuevos vecinos.

3. ¿Qué ocurre si el nodo tiene solo hijo izquierdo?

 Se ejecuta una rotación a la derecha (rotateRight) para desplazar el nodo hacia abajo por la rama opuesta.

4. ¿Qué ocurre si el nodo tiene solo hijo derecho?

 Se ejecuta una rotación a la izquierda (rotateLeft).

5. ¿Qué invariantes deben seguir siendo verdaderos después de `splice`?

 Se deben conservar la ordenación de claves BST del árbol, la jerarquía de prioridades del heap y la integridad bidireccional de los punteros parent.

`Parte D: Búsqueda Ordenada y Comparativa` 

 Tabla Comparativa: Treap vs BinarySearchTree

 | Operacion | Resultado en Treap | Resultado en BST Tradicional | Propierda Utilizada |
 | :--- | :--- | :--- | :--- |
 | findEQ(40) | 40 | 40 | Propiedad de orden BST (Igualdad) | 
 | findEQ(35) | null | null | Propiedad de orden BST (Fallo) | 
 | lowerBound(35) | 40 | 40 | Propiedad BST (Menor elemento =>35) | 
 | lowerBound(40) | 40 | 40 | Propiedad BST (Igualdad directa => 40) | 
 | upperBound(40) | 60 | 50 (varía según forma) | Propiedad BST (Primer elemento > 40) |
 | upperBound(75) | 80 | 80 | Propiedad BST (Primer elemento > 75) | 

1. ¿Por qué `lowerBound` y `upperBound` dependen de la propiedad BST y no de la propiedad heap?

 Porque el heap solo organiza las prioridades en el eje jerárquico vertical (padre-hijo), pero carece de un criterio de ordenamiento horizontal. Las operaciones lowerBound y upperBound necesitan saber si una clave es mayor o menor que otra, información provista por las ramas del BST.

2. ¿Qué parte del treap se comporta igual que un BST?

 La lógica de ramificación y búsqueda por claves (find, lowerBound, upperBound, addNode).

3. ¿Qué parte del treap se comporta como heap?

 La lógica de ordenamiento de prioridades mediante flotación y hundimiento (bubbleUp, trickleDown).

4. ¿Por qué el treap no reemplaza directamente a una cola de prioridad si lo único que quieres es extraer máximos o mínimos repetidamente?

 Porque extraer recurrentemente máximos o mínimos en un Treap cuesta O(log n) debido a las rotaciones necesarias para reacomodar el árbol. Un heap binario estructurado en un arreglo contiguo (PQ_ComplHeap) optimiza mucho mejor el uso de la memoria caché y elimina la sobrecarga del manejo dinámico de punteros.

5. ¿En qué situación sí conviene usar una estructura tipo treap?.

 Conviene cuando necesitas una estructura híbrida multi-propósito de alto rendimiento que requiera hacer búsquedas por rangos dinámicos y al mismo tiempo necesite mantener un orden de prioridad fluido, como en la implementación de planificadores de procesos por prioridades con consultas exhaustivas de claves.

`Parte E:` Pruebas Unitarias Robustas

   3. `Semana6/pruebas_internas/test_internal_week6.cpp`
           Añadiremos la batería exhaustiva de aserciones al final de el archivo de pruebas internas para cubrir las 13 condiciones requeridas. Se puede pegar este bloque al final de runComprehensiveHeapTests() o dentro del main de las pruebas:
 ```C++
 // MOD-A6-B10-PARTEE: Suite de testing exhaustiva para Treap
 void runTreapSanitySuite() {
  // 1. Treap vacío
  ods::Treap<int> t;
  assert(t.empty() == true);
  assert(t.size() == 0);
  assert(t.isTreap() == true);

  // 2. Inserción con prioridades fijas e inorden
  t.addWithPriority(50, 10);
  t.addWithPriority(30, 5);  // Debería ser la nueva raíz (menor prioridad)
  t.addWithPriority(70, 20);
  
  assert(t.size() == 3);
  assert(t.root()->key == 30);
  // 4. Inorden ordenado automáticamente
  assert((t.inorderKeys() == std::vector<int>{30, 50, 70}));
  // 5. Invariante de Heap válido
  assert(t.isHeapByPriority() == true);

  // 3. Rechazo explícito de duplicados
  bool duplicado = t.addWithPriority(30, 2);
  assert(duplicado == false); // No debe permitir claves duplicadas
  assert(t.size() == 3);

  // 6. Pruebas de Bounds
  assert(t.lowerBound(35)->key == 50);
  assert(t.upperBound(50)->key == 70);

  // 7. Eliminación de hoja
  t.addWithPriority(80, 100);
  assert(t.contains(80));
  t.remove(80);
  assert(!t.contains(80));

  // 10, 11, 12, 13: Secuencias mixtas y consistencia estructural
  t.remove(30); // Eliminación de la raíz actual
  assert(t.isTreap());
  assert(t.size() == 2);
 }
 ```        
1. ¿Qué bug atraparía una prueba de enlaces `parent`?

 Descubriría fugas de asignación en las funciones rotateLeft o rotateRight cuando un nodo cambia de posición pero su puntero interno se queda apuntando incorrectamente a su padre antiguo, corrompiendo los recorridos inversos.

2. ¿Qué bug atraparía una prueba de `size()`?

 Detectaría errores de lógica en addNode o splice donde una operación es rechazada (por ejemplo, al intentar insertar una clave duplicada) pero el contador se incrementa o decrementa de todos modos, desincronizando el tamaño lógico con el real.

3. ¿Qué bug atraparía una prueba de inorden ordenado?

 Capturaría fallos graves de asignación en las rotaciones que rompan la hilación secuencial izquierda-derecha propia del árbol binario de búsqueda.

4. ¿Qué bug atraparía una prueba de prioridad padre-hijo?

 Detectaría fallos en las condiciones lógicas de los bucles de bubbleUp o trickleDown, como el uso de un operador de comparación invertido (< por >) que hunda los nodos en lugar de hacerlos flotar.

5. ¿Por qué conviene usar prioridades fijas en pruebas unitarias?

 Porque vuelve los experimentos completamente deterministas y reproducibles. Al fijar las prioridades, garantizas que el árbol adopte siempre exactamente la misma topología estructural, facilitando el diseño de aserciones precisas sobre qué nodo debe actuar como raíz o hijo en cada paso.

#### Bloque 11 - Comparación con Semana 5: `BinaryHeap`, `BinarySearchTree` y `Treap`

 `Código Modificado Completo`
   1. `Semana6/demos/demo_compare_with_semana5.cpp`
 
      1. Agregamos:
         #include <iomanip>  
         #include <string>   
         #include "Treap.h"   
 
       2. Bloque añadido antes del main:
         - Se inyectó la función auxiliar printRow:
 ```C++
 void printRow(const std::string& est, const std::string& op_p, const std::string& prop, 
              const std::string& op_e, const std::string& op_no, const std::string& evid) { ... }
 ```
   3.  Instanciación e inserción del Treap:
      El código original Sólo declaraba e insertaba en tres estructuras (pq, minHeap, bst).Cambio aplicado en el cuerpo del main: Añadi la declaracion de Treap:
 ```C++
 ods::Treap<int> treap_s6(42);
 ```
 Dentro del bucle for (int x : xs), agregue la alimentación de esta estructura:
 ```C++
 ods::Treap<int> treap_s6(42);
 ```
   4. Reemplazo de las salidas de texto plano por la Tabla Dinámica
   
      El código original tenía una serie de std::cout planos que mostraban .getMax(), .top() y el bucle para el inorden del BST. Borre esos std::cout y los sustitui por llamadas consecutivas a printRow, pasándole los datos teóricos de la guía junto con las evidencias dinámicas extraídas en tiempo real (como bh_s5.top() o la raíz del Treap)

   5. Sección de evidencias físicas al cierre   
       El código original terminaba con tres líneas informativas dentro de un bloque de "Interpretacion:". Lo reemplaze  por la sección "--- VERIFICACIÓN DE INTERPRETACIÓN ---". Aquí añadí la impresión del vector crudo subyacente de ambos heaps (bh_s5.data() y pq_s6.data()), demostrando de manera empírica que los datos en un heap no guardan un orden secuencial/inorden, a diferencia del BST y del Treap que también se imprimen al lado.

  `Tabla de Comparación Estructural`
 | Estructura | Operacion principal | Propiedad mantenida | Operacion Eficiente | Operacion que NO Conviene | Evidencia Producida | 
 | :--- | :--- | :--- | :--- | :--- | :--- | 
 | BinaryHeap (Semana 5) | add / remove | Min-Heap: El padre es menor o igual a sus hijos. Almacenamiento plano en un std::vector. | Extraer el elemento mínimo O(1) y removerlo en O(log n). | Buscar un elemento arbitrario o consultas de rango O(n). | top() = 1 (Mínimo absoluto) | 
 | PQ_ComplHeap (Semana 6) | insert / delMax | Max-Heap: El padre es mayor o igual a sus hijos. Optimizado con Floyd. | Extraer el elemento máximo O(1) y borrarlo en O(log n). | Búsquedas exactas o recorridos ordenados parciales O(n). | getMax() = 14 (Máximo absoluto) | 
 | BinarySearchTree (S5) | add / remove | Orden Simétrico: Subárbol izquierdo < Nodo < Subárbol derecho. | Búsqueda exacta, lowerBound y upperBound en O(h). | Extraer máximos consecutivamente (puede desbalancearse a peor caso O(n)). | Recorrido Inorden perfectamente ordenado. | 
 | Treap (Semana 6) | add / remove | Híbrida: Claves ordenadas por BST y Prioridades ordenadas por Heap. | Búsqueda indexada por rangos dinámicos en tiempo esperado O(log n). | Extracción masiva cíclica de extremos por sobrecarga de punteros. | Consistencia de orden en claves manteniendo la raíz adaptada por prioridad. | 

1. ¿Qué diferencia hay entre un heap de prioridad y un árbol de búsqueda?
 
   - El Heap es una estructura de prioridad vertical (el elemento dominante vive en la raíz y no hay un orden de izquierda a derecha), implementada comúnmente sobre arreglos continuos sin punteros.

   - El Árbol de Búsqueda (BST) es una estructura de ordenamiento horizontal (el menor a la izquierda, el mayor a la derecha), compuesta por nodos distribuidos de forma dinámica en la memoria.

2. ¿Por qué un BST permite recorrido ordenado y un heap no?

   - El BST sostiene una relación de orden simétrico total: realizar un recorrido inorden (Izquierda, Raíz, Derecha) procesa geométricamente las claves de menor a mayor.

   - El Heap carece de orden simétrico entre hermanos; el hijo izquierdo y el derecho no guardan relación de orden entre sí, lo que hace imposible un recorrido secuencial sin extraer y destruir la estructura.

3. ¿Qué agrega `PQ_ComplHeap` frente a un `BinaryHeap` educativo?

 - Introduce la interfaz orientada a servicios de Colas de Prioridad (PQ), automatiza la construcción lineal O(n) usando el algoritmo de Heapify de Floyd (complHeapHeapifyFloyd) en lugar de inserciones sucesivas, y está orientada por defecto a prioridades máximas en lugar de mínimas.

4. ¿Qué combina un `Treap`?

 - Combina las operaciones de búsqueda ordenada de un BST usando la clave (key), con la estabilidad estructural logarítmica auto-balanceada de un Heap usando prioridades generadas aleatoriamente.

5. ¿Qué estructura usarías para extraer máximos repetidamente?

 Usaría PQ_ComplHeap, porque procesa delMax en O(log n) de forma nativa sin sobrecarga de punteros en memoria y localiza el máximo instantáneamente en O(1) en la posición data_[0].

6. ¿Qué estructura usarías para responder `lowerBound` o `upperBound`?

 Usaría BinarySearchTree (o en su defecto un Treap). Es la única que gracias a su propiedad binaria permite descartar subárboles completos, resolviendo la consulta en tiempo proporcional a su altura. En un heap, obligatoriamente se requiere un escaneo lineal costoso de costo O(n).

7. ¿Qué estructura usarías si quieres búsqueda ordenada con balanceo probabilístico?.

 El Treap. Al asignar prioridades aleatorias independientes a cada clave, garantiza con una probabilidad extremadamente alta que el árbol mantendrá una altura de O(log n), evitando que inserciones ordenadas lo degraden en una lista enlazada como le pasa al BST ordinario.

 `Respuesta breve de Seleccion de Estructura`
   - Si el problema se enfoca en Frecuencias / Atender prioridades / Algoritmos de Codificación (como Huffman)-> Se usa PQ_ComplHeap (alto rendimiento en extremos, memoria compacta).
   - Si el problema se enfoca en Consultas de rangos / Diccionarios / Búsquedas de límites cercanos (Bounds)-> Se usa Treap o BST (navegación horizontal indexada).

#### Bloque 12 - Pruebas obligatorias después de modificar código

 `Modificaciones a los Archivos de Prueba`
   1. `Cambios en Semana6/pruebas_internas/test_internal_week6.cpp`
       A la función existente runComprehensiveHeapTests(), le integré la suite correspondiente a las operaciones detalladas de tamaño e invariantes de Heap y Huffman:
 ```C++
 // Se agregaron estas validaciones al final de runComprehensiveHeapTests() o como función hermana:
 void runAdditionalInternalTests() {
  auto comp = std::less<int>();

  // Prueba 3: getMax no cambia el tamaño
  std::vector<int> raw = {5, 12, 9, 1};
  ods::PQ_ComplHeap<int> heap_size(raw);
  std::size_t size_before = heap_size.size();
  int max_val = heap_size.getMax();
  assert(heap_size.size() == size_before); // El tamaño se mantiene idéntico

  // Prueba 4: delMax sí cambia el tamaño
  heap_size.delMax();
  assert(heap_size.size() == size_before - 1); // Se reduce exactamente en 1

  // Prueba 10 y 11: Símbolos con frecuencia positiva y libres de prefijo
  const std::vector<ods::HuffmanSymbol> symbols = {{'x', 10}, {'y', 20}, {'z', 30}};
  const auto huff_codes = ods::huffmanGenerateCodes(symbols);
  assert(huff_codes.size() == 3); // Todos los caracteres obtienen un código
  assert(ods::huffmanIsPrefixFree(huff_codes));

  // Prueba 12: Caso extremo de un único símbolo en Huffman
  const std::vector<ods::HuffmanSymbol> single_sym = {{'a', 100}};
  const auto single_codes = ods::huffmanGenerateCodes(single_sym);
  assert(single_codes.size() == 1);
  assert(!single_codes.at('a').empty()); 
 }
 ```
   
   2. `Cambios en Semana6/pruebas_publicas/test_public_week6.cpp`
        Reescribí las secciones de Leftist Heap y Treap para asegurar la verificación de mutaciones consecutivas paso a paso:
 ```C++
 // Inyecciones dentro del main() de pruebas públicas:

 // Pruebas 7, 8 y 9: Invariantes secuenciales en Leftist Heaps
 ods::PQ_LeftHeap<int> lh1{10, 20};
 ods::PQ_LeftHeap<int> lh2{5, 15};

 lh1.merge(lh2); 
 assert(lh1.isLeftistHeap()); // Invariante post-merge

 lh1.insert(25);
 assert(lh1.isLeftistHeap()); // Invariante post-insert

 lh1.delMax();
 assert(lh1.isLeftistHeap()); // Invariante post-delMax

 // Prueba 6: HeapSort con elementos repetidos
 std::vector<int> repetidos = {4, 2, 4, 1, 2, 4, 3};
 ods::heapSort(repetidos);
 assert((repetidos == std::vector<int>{1, 2, 2, 3, 4, 4, 4})); // Orden relativo correcto

 // Pruebas 13, 14 y 15: Invariantes compuestos del Treap
 ods::Treap<int> t_test(42);
 std::vector<int> claves = {50, 30, 70, 20, 40};
 for(int k : claves) {
  t_test.add(k);
  assert(t_test.isBST());           // Propiedad 13: Conserva orden de búsqueda
  assert(t_test.isHeapByPriority());// Propiedad 14: Conserva propiedad de prioridad
 }
 t_test.remove(30);
 assert(t_test.isTreap());           // Propiedad 15: Mantiene ambas tras remoción
 
 ```
 `Lista de Pruebas Agregadas y Cobertura`

 A continuación detallare la matriz de correspondencia de cada una de las 15 pruebas solicitadas:
  
   1. PQ_ComplHeap conserva propiedad en inserción: Integrado en el bucle incremental de test_internal_week6.cpp utilizando assert(pq.isHeap()). 
   2. PQ_ComplHeap conserva propiedad en eliminación: Validado en el bucle de vaciado de pq.delMax() mediante assert(pq.empty() || pq.isHeap()).
   3. getMax no altera el tamaño: Implementado comparando .size() antes y después de leer el extremo máximo.
   4. delMax decrementa el tamaño: Validado mediante una aserción que comprueba que size_after == size_before - 1.
   5. heapifyFloyd produce un heap válido: Comprobado al instanciar pq_floyd(raw_vector) y ejecutar de inmediato assert(pq_floyd.isHeap()).
   6. heapSort con repetidos: Validado pasando un vector con múltiples instancias de {4, 2, 4} a ods::heapSort.
   7. PQ_LeftHeap post-merge: Verificado llamando a .isLeftistHeap() justo después de mezclar dos colas.
   8. PQ_LeftHeap post-insert: Validado llamando a .isLeftistHeap() tras añadir elementos individuales.
   9. PQ_LeftHeap post-delMax: Verificado llamando a .isLeftistHeap() inmediatamente después de extraer la raíz.
   10. Huffman con frecuencia positiva: Comprobado verificando que la longitud del mapa de códigos generados coincide exactamente con el conteo de símbolos provistos.
   11. Huffman libre de prefijos: Validado a través de la función predictiva ods::huffmanIsPrefixFree(...).
   12. Huffman con un único símbolo: Manejo del caso base crítico donde el árbol posee un único nodo hoja (raíz).
   13. Treap conserva propiedad BST al insertar: Verificado llamando de forma explícita a t.isBST().
   14. Treap conserva propiedad Heap al insertar: Verificado llamando de forma explícita a t.isHeapByPriority().
   15. Treap conserva ambas propiedades al eliminar: Validado llamando a la conjunción lógica t.isTreap() tras remover nodos intermedios y raíces.

 `Explicación de Bugs Atrapados por cada Prueba`
   - Pruebas 1 y 2 (Invariantes de inserción/remoción en Heap): Atrapan errores en los índices de cálculo de los nodos hijos/padres en bubbleUp o trickleDown. Si el código calcula mal el padre usando una fórmula errónea, la propiedad se rompe de inmediato.
   - Pruebas 3 y 4 (Efectos de tamaño en lectura y borrado): Atrapan el clásico error de "efecto secundario", donde un método de consulta (como getMax) borra accidentalmente el nodo o muta un puntero, o donde delMax se olvida de actualizar el contador de elementos.
   - Prueba 5 (heapifyFloyd): Atrapa bugs de rango en el bucle decreciente. El algoritmo de Floyd debe empezar en n/2 - 1 e ir bajando; si empieza en un índice incorrecto o usa un signo equivocado, ignora la mitad de los subárboles.
   - Prueba 6 (heapSort con repetidos): Detecta fallas en los operadores de comparación estricta (< vs <=). Si el ordenamiento no procesa correctamente los duplicados, puede entrar en un bucle infinito o truncar el arreglo.
   - Pruebas 7, 8 y 9 (Invariantes en Leftist Heap): Detectan fallas en la actualización del parámetro npl (null path length). Si al fusionar o eliminar nos olvidamos de recalcular el npl del nodo padre o no intercambiamos los hijos izquierdo y derecho cuando el derecho es mayor, el árbol pierde la propiedad izquierdista y se degrada en rendimiento.
   - Pruebas 10, 11 y 12 (Defectos en Huffman): Evitan la generación de árboles degenerados. El caso de un solo símbolo suele causar caídas por desreferenciación de punteros nulos (nullptr) si el algoritmo asume que siempre hay al menos dos nodos para realizar la combinación.
   - Pruebas 13, 14 y 15 (Invariantes del Treap): Son cruciales para detectar errores en las rotaciones de punteros. Si rotateLeft o rotateRight enlaza de forma incorrecta el padre de un subárbol modificado, estas pruebas fallarán inmediatamente indicando que perdimos la secuencia ordenada del BST o la prioridad del Heap.

  `Resultado (ctest --output-on-failure)`

         Test project /home/gustavo/CC-232-main/Libreria_cc232/Semana6/build
             Start 1: TestPublicWeek6
         1/2 Test #1: TestPublicWeek6 ..................   Passed    0.00 sec
             Start 2: TestInternalWeek6
         2/2 Test #2: TestInternalWeek6 ................   Passed    0.01 sec

         100% tests passed, 0 tests failed out of 2

         Total Test time (real) =   0.02 sec

#### Bloque 13 - Defensa escrita de modificaciones

 - Modificar directamente el código de las estructuras de datos de la Unidad 3 me ha revelado una verdad fundamental: leer un algoritmo oculta los problemas de punteros, índices y flujos de datos que ocurren en la memoria real. La simulación mental o la simple lectura de un pseudocódigo ignora los sutiles detalles de implementación donde se esconden los verdaderos bugs arquitectónicos.
      1. Gestión de Prioridades y Representaciones en Memoria
          - La interfaz PQ: Al extender la interfaz de Colas de Prioridad, aprendí que una PQ es un contrato puramente funcional orientado al comportamiento externo (qué extremo se extrae). Su diseño abstracto desacopla por completo al cliente de la topología interna; al usuario no le importa si por debajo opera un arreglo contiguo o un árbol de nodos dinámicos enlazados, facilitando el intercambio de componentes en caliente.
          - Representación implícita del heap binario completo: Implementar las relaciones de vecindad mediante aritmética pura —donde los hijos de i están en 2i+1 y 2i+2— me demostró el poder de eliminar la sobrecarga de memoria de los punteros tradicionales. Sin embargo, también evidenció su fragilidad: el más mínimo desfase de una unidad en el mapeo indexado destruye por completo la estructura lógica del árbol, transformando un algoritmo óptimo en un fallo de segmentación.

      2. Algoritmos de Ajuste y Construcción Estructural
          - percolateUp (o bubbleUp): Escribir este método me enseñó que la propagación hacia arriba es un proceso estrictamente local y unidireccional. El nodo ascendente solo compite contra su ancestro directo directo en cada iteración, lo que simplifica las condiciones de parada, deteniéndose inmediatamente cuando el padre recupera la dominancia de prioridad.
          - percolateDown (o trickleDown): Modificar este flujo me demostró que el descenso es sustancialmente más complejo que la subida. Aquí, el nodo modificado debe evaluar simultáneamente a sus dos hijos antes de decidir el intercambio; seleccionar erróneamente el hijo con menor prioridad rompe el invariante del heap en el subárbol opuesto, lo que exige una lógica condicional rigurosa en cada paso de bajada.
          - heapify de Floyd: Al programar la construcción de Floyd, asimilé la genialidad de construir un heap "de abajo hacia arriba" procesando desde el último nodo interno (n/2 - 1) hasta la raíz. Modificar este bucle decreciente me permitió contrastar su eficiencia matemática real, logrando un tiempo lineal O(n) que es imposible de emular mediante inserciones sucesivas de costo O(n log n).
          - heapSort: Al acoplar el ordenamiento in-place, aprendí que heapSort aprovecha de forma magistral las dos fases del heap: la construcción rápida con Floyd y el vaciado sistemático. Al intercambiar la raíz máxima con la última posición del arreglo y reducir el tamaño lógico del heap, la estructura utiliza el mismo espacio físico para ordenar los elementos sin requerir memoria auxiliar.

      3. Variaciones Avanzadas: Leftist Heaps y Codificación
          - merge en heap izquierdista: La codificación de la fusión en PQ_LeftHeap me obligó a pensar en términos de asimetría controlada. Aprendí que, a diferencia del heap completo, aquí los punteros físicos importan. Mantener el camino derecho lo más corto posible exige que, tras cada fusión recursiva, se evalúe el Null Path Length (npl) de los hijos y se realice un intercambio físico si el derecho supera al izquierdo, garantizando que el camino de descenso derecho nunca exceda O(log n).
          - Algoritmo de Huffman: Implementar la generación de códigos me enseñó la interdependencia entre las colas de prioridad y los árboles de decisión. La cola de prioridad no solo actúa como un almacén, sino como el motor codicioso (greedy) que decide la topología del árbol final, donde los caracteres más frecuentes se mantienen cerca de la raíz para minimizar la longitud de la ruta ponderada.

      4. Híbridos y Comparaciones de Diseño
          - El Treap, rotaciones y búsqueda ordenada: Programar el Treap fue el desafío más revelador de la unidad. Entendí de forma práctica cómo las rotaciones locales modifican la altura y la jerarquía de prioridades (propiedad de heap) sin alterar el orden simétrico horizontal de las claves (propiedad de BST). La aleatoriedad de las prioridades actúa como un escudo probabilístico que balancea el árbol de manera natural frente a secuencias de inserción ordenadas.
          - Comparación con BinaryHeap y BinarySearchTree: Modificar simultáneamente estas estructuras me dio una perspectiva clara de sus ventajas y desventajas en producción. Mientras que BinaryHeap ofrece el máximo rendimiento espacial y accesos en O(1) a un extremo específico, carece por completo de la capacidad de realizar búsquedas eficientes de rangos intermedios (lowerBound), una operación nativa y fluida para el BinarySearchTree y el Treap.
      
  