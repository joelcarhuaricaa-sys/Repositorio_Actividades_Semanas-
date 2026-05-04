### Actividad 3 - CC232

### INTEGRANTES
 - Joel Gustavo Carhuarica Aguilar

#### BLOQUE 1 - NUCLEO CONCEPTUAL DE LA SEMANA

1. Expliquen con sus palabras qué cambia cuando una estructura pasa de almacenamiento contiguo a almacenamiento dinámico.

 Cuando una estructura pasa de almacenamiento contiguo (como arreglos) a dinámico (como listas enlazadas), los elementos dejan de ocupar posiciones consecutivas en memoria y se distribuyen en nodos conectados por punteros. Esto facilita inserciones y eliminaciones locales al solo ajustar referencias, pero complica el acceso directo por índice, ya que requiere recorrer nodos secuencialmente, y aumenta el uso de memoria por los punteros adicionales.

2. Expliquen la diferencia entre acceso por rango y acceso por posición o enlace.

 El **acceso por rango** (o índice) permite localizar un elemento directamente mediante una posición numérica (ej. get(i)), aprovechando la contigüidad en memoria para cálculos aritméticos rápidos. **El acceso por posición** o enlace navega mediante punteros entre nodos, siendo más flexible para modificaciones locales pero menos eficiente para posiciones arbitrarias, ya que implica recorridos secuenciales.
 
3. Expliquen por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice.

 En una lista enlazada, las inserciones y eliminaciones locales son eficientes porque solo requieren ajustar punteros de nodos adyacentes, sin desplazar otros elementos. Sin embargo, el acceso por índice empeora porque no hay contigüidad; se debe recorrer la lista desde el inicio hasta la posición deseada, resultando en tiempo lineal en el peor caso.

4. Expliquen por qué `SLList` implementa bien operaciones de `Stack` y `Queue`.

 **SLList** implementa bien operaciones de **Stack** (LIFO) y **Queue** (FIFO) porque mantiene referencias al head y tail. Para Stack, push y pop operan en head en O(1). Para Queue, add en tail y remove en head también son O(1), aprovechando la estructura simplemente enlazada para acceso directo a extremos.

5. Expliquen por qué `SLList` no implementa naturalmente todas las operaciones de un `Deque` con el mismo costo.

 `SLList` no implementa naturalmente todas las operaciones de un Deque con el mismo costo porque un `Deque` requiere acceso eficiente a ambos extremos para inserciones y eliminaciones. Aunque add y remove en extremos son O(1), operaciones como removeLast requieren recorrer toda la lista para actualizar tail, resultando en O(n) en el peor caso, en lugar del O(1) deseado.

6. Expliquen qué aporta el nodo centinela `dummy` en `DLList`.

 El nodo centinela dummy en DLList actúa como un marcador ficticio que simplifica el manejo de la lista vacía y evita casos especiales en operaciones. Conecta el inicio y fin de la lista, permitiendonos recorridos bidireccionales uniformes y reduciendo código duplicado para insertar/eliminar en extremos.

7. Expliquen por qué `DLList` permite justificar `get(i)`, `set(i,x)`, `add(i,x)` y `remove(i)` con costo `O(1 + min(i, n-i))`.

 DLList justifica get(i), set(i,x), add(i,x) y remove(i) en O(1 + min(i, n-i)) porque usa navegación bidireccional desde el extremo más cercano (inicio o fin) hasta la posición i. El min(i, n-i) minimiza el recorrido, y las operaciones locales (ajustar punteros) son O(1) una vez localizada la posición.

8. Expliquen cuál es la idea espacial central de `SEList`.

 La idea espacial central de SEList es agrupar elementos en bloques (usando BDeque) para reducir la sobrecarga de memoria de punteros por elemento. En lugar de un puntero por nodo, múltiples elementos comparten un bloque, mejorando la eficiencia espacial mientras mantiene propiedades de listas enlazadas.

9. Expliquen por qué `SEList` reutiliza una `BDeque` basada en `ArrayDeque`.

 `SEList` reutiliza `BDeque` (basada en ArrayDeque) porque cada bloque necesita un contenedor dinámico eficiente para almacenar elementos. `ArrayDeque` proporciona inserciones/eliminaciones rápidas en extremos dentro de cada bloque, permitiendo que SEList maneje redistribuciones (spread/gather) de manera eficiente sin reimplementar lógica de arrays.

10. Expliquen qué papel cumple `DengList` dentro de esta semana y por qué no reemplaza a las estructuras de Morin.

 DengList sirve como una implementación más simple y didáctica de listas basada en Deng, enfocada en operaciones básicas y algoritmos como ordenamiento. No reemplaza a las estructuras de Morin porque estas ofrecen análisis de complejidad más detallado, optimizaciones específicas (como dummy en DLList o bloques en SEList) y comparación directa con representaciones contiguas, siendo más adecuadas para estudiar trade-offs en el curso.

#### BLOQUE2 - DEMOSTRACION Y TRAZADO GUIADO

| Archivo |	Salida u observable importante | Idea estructural |	Argumento de costo, espacio o diseño |
|---|---|---|---|
|`demo_sllist.cpp` | `size = 3`, `peek = 5`, `pop = 5`, `remove = 20` | `SLList` combina operaciones de pila y cola en una sola lista enlazada simple |	`push` / `pop` trabaja como stack en el frente; `add` / `remove` aporta comportamiento de cola en el otro extremo.|
|`demo_dllist.cpp`|	Impresión `10 20 30` tras `add(0,10)`, `add(1,30)`, `add(1,20)` | `DLList` usa doble enlace + dummy para insertar en medio con eficiencia | `add(i,x)` en posición intermedia se justifica por recorrido desde el extremo cercano `O(1 + min(i,n-i))`.|
|`demo_selist.cpp`|	Impresión ordenada `0 10 20 30 40 50 60 70 80 90`| 	`SEList` mantiene el orden lógico de lista aunque internamente use bloques | El acceso lógico `get(i)` sigue devolviendo la secuencia ordenada, mostrando que la fragmentación en bloques es transparente.|
|`demo_deng_list.cpp` | `size`, `front`, `back`, luego lista ordenada tras `sort()` | `DengList` ofrece lista reforzada con operaciones de lista completas | `push_back`, `push_front`, `front`, `back` y `sort()` muestran un ADT de lista más rico que solo un contenedor básico.|
|`demo_morin_deng_bridge.cpp` | Salida con lista ordenada y `removed = ...` tras `stable_sort_with_deng` y `dedup_with_deng` | Algoritmos Deng aplicados sobre `DLList` sin reescribir la estructura base |	El uso de `stable_sort_with_deng(lista)` y `dedup_with_deng(lista)` demuestra reutilizar la estructura `DLList` para nuevos algoritmos.|
|`demo_min_structures.cpp` | `MinStack min=3`, `MinQueue min=2`, `MinDeque min=1` |	Estructuras que guardan elementos y metadata para responder `min()` | La diferencia es entre almacenar solo valores y almacenar información adicional (auxiliar) para responder `min()` en tiempo rápido.|
|`demo_linked_adapters.cpp` | Resultados de `LinkedStack`, `LinkedQueue`, `LinkedDeque` con operaciones adaptadas | Adaptadores que brindan interfaces nuevas sobre estructuras enlazadas |	Reutiliza la estructura enlazada subyacente para implementar interfaces de `Stack`, `Queue` y `Deque` sin reescribir los nodos básicos.|
|`demo_contiguous_vs_linked.cpp` | Comparación `ArrayDeque` vs `DLList`: FIFO, deque e índice |	Contrasta estructura contigua con estructura enlazada |	`ArrayDeque` gana en acceso por índice y localidad de memoria; `DLList` gana en inserción local y flexibilidad de enlaces.|

1. En `demo_sllist.cpp`, ¿qué secuencia deja más clara la coexistencia de comportamiento tipo pila y tipo cola dentro de `SLList`?

 `demo_sllist.cpp:` la secuencia `add(10)`, `add(20)`, `push(5)` seguida de `peek()`, `pop()` y `remove()` deja más clara la coexistencia de pila y cola.

2. En `demo_dllist.cpp`, ¿qué operación muestra mejor la inserción en una posición intermedia?

 La operación `add(1, 20)` es la que mejor muestra inserción en posición intermedia.

3. En `demo_selist.cpp`, ¿qué observable permite defender que la lista mantiene orden lógico aunque internamente trabaje por bloques?
 
 El observable `get(i)` que devuelve valores en orden lógico (`0 10 20 ... 90`) defiende que la lista mantiene orden aunque trabaje por bloques.

4. En `demo_deng_list.cpp`, ¿qué evidencia muestra que la lista reforzada por Deng ofrece operaciones más cercanas a un ADT de lista completo?
  
 La evidencia es que se muestran `front`, `back`, tamaño y luego `sort()` + `to_vector()`, lo que indica operaciones de lista completas.

5. En `demo_morin_deng_bridge.cpp`, ¿qué parte de la salida permite justificar que se reutilizan algoritmos sin reescribir la estructura base?

 La parte de salida que muestra la lista ordenada y el `removed = ...` tras aplicar `stable_sort_with_deng` y `dedup_with_deng` justifica la reutilización de algoritmos sobre la misma estructura base.

6. En `demo_min_structures.cpp`, ¿qué diferencia conceptual observan entre almacenar valores y almacenar información adicional para responder `min()`?
  
 La diferencia conceptual es que guardar valores permite solo operaciones normales, mientras que almacenar información adicional permite responder `min()`rápidamente sin recorrer toda la estructura.

7. En `demo_linked_adapters.cpp`, ¿qué adaptador representa mejor la idea de reutilizar una estructura existente para ofrecer una interfaz nueva?

 El adaptador `LinkedStack` representa mejor la idea de reutilizar una estructura existente para ofrecer una interfaz nueva, aunque `LinkedQueue` y `LinkedDeque` también lo hacen.

8. En `demo_contiguous_vs_linked.cpp`, ¿qué contraste se observa entre acceso por índice, inserción local y localidad de memoria?

 El contraste es que el acceso por índice es más directo en la estructura contigua (`ArrayDeque`), la inserción local es más natural en la estructura enlazada (`DLList`/`LinkedDeque`), y la memoria contigua ofrece mejor localidad frente a la dispersión de punteros en la lista enlazada.

#### BLOQUE3 - PRUEBAS PUBLICAS, STRESS Y CORRECTITUD

1. ¿Qué operaciones mínimas valida la prueba pública para `SLList`?

 En test_public_week3.cpp:

 - `add(x)` — agregar elemento
 - `push(x)` — operación tipo pila
 - `size()` — contar elementos
 - `peek()` — ver el tope
 - `pop()` — remover tope
 - `remove()` — remover primer elemento

 **Resultado:** Solo operaciones en los extremos (cabeza y cola) sin acceso por posición intermedia.

2. ¿Qué operaciones mínimas valida la prueba pública para `DLList`?
 
 En `test_public_week3.cpp`:

 - `add(i, x)` — agregar en posición `i`
 - `get(i)` — acceder en posición `i`
 - `remove(i)` — remover en posición `i`
 - `size()` — contar elementos

  **Resultado:** Acceso aleatorio y modificaciones puntuales en posiciones arbitrarias.

3. ¿Qué operaciones mínimas valida la prueba pública para `SEList`?
 
 En test_public_week3.cpp:

 - `add(i, x)` — agregar en posición `i`
 - `get(i)` — acceder en posición `i`
 - `set(i, x)` — reemplazar en posición `i` y devolver anterior
 - `remove(i)` — remover en posición `i`
 - `size()` — contar elementos

 **Resultado:** Operaciones fundamentales por índice, similar a DLList pero sin acceso a nodos interme­dios directamente.

4. ¿Qué operaciones nuevas quedan cubiertas por `test_public_extras.cpp`?
 
  Nuevas operaciones/métodos:

 - `to_vector()` — convertir a std::vector (SLList, DLList)
 - `secondLast()` — acceder penúltimo elemento (SLList)
 - `reverse()` — invertir orden (SLList, DLList)
 - `checkSize()` — validar consistencia interna (SLList, DLList)
 - `rotate(r)` — rotación circular (DLList)
 - `isPalindrome()` — validar estructura simétrica (DLList)
 - `min()` — operación especializada (MinStack, MinQueue, MinDeque)
 - `addFirst()`, `addLast()`, `removeLast()` — operaciones extremos (MinDeque, XorList)

5. ¿Qué valida específicamente `test_public_linked_adapters.cpp` sobre `LinkedStack`, `LinkedQueue` y `LinkedDeque`?

 - **LinkedStack**: `push()`, `pop()`, `top()`, `empty()`, `size()`     — comportamiento LIFO correcto
 
 - **LinkedQueue**: `add()`, `remove()`, `front()`, `empty()`, `size()` — comportamiento FIFO correcto

 - **LinkedDeque**: `addFirst()`, `addLast()`, `removeFirst()`, `removeLast()`, `front()`, `back()`, `empty()`, `size()` — todas las operaciones de extremos funcionan.

 **Idea central**: Valida que los adaptadores heredan correctamente el comportamiento de la estructura subyacente sin mutations semánticas.

6. ¿Qué demuestra `test_public_deng_bridge.cpp` sobre integración y reutilización?
- **DengList directo**:  `push_back() `,  `push_front() `,  `add() `,  `front() `,  `back() `,  `get() `,  `find_index() `,  `contains() ` funcionan

- **Algoritmos sobre Morin + Deng**:

   - `stable_sort_with_deng() ` convierte DLList/SEList a DengList, ordena, convierte de vuelta.
   -  `dedup_with_deng() ` elimina duplicados reutilizando el ADT de Deng
   -  `reverse_with_deng() ` invierte sin reimplementar

- **Bridge permite**:
   - Reutilizar **algoritmos de Deng** sin reescribir estructuras Morin
   - Conversión transparente entre representaciones

Los algoritmos son agnósticos a la estructura subyacente si existe un contrato claro.

7. En `stress_selist_week3.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, borrado y mantenimiento del tamaño lógico?
  
  1. Crecimiento orgánico de bloques: 500 inserciones consecutivas para forzar subdivisiones internas de celdas B

  2. Borrado frontal sostenido: 250 eliminaciones desde el inicio para validar reorganización de bloques y mantenimiento de invariantes

  3. Mantenimiento del tamaño lógico: Al final, debe cumplir exactamente size() == 350 (500 - 250 + 100), demostrando que nunca se pierde consistencia interno-externa

8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?

    ✅ Contrato funcional cumplido:

       - Las operaciones devuelven valores correctos

       - El tamaño se mantiene consistente
       
       - Las relaciones de orden (FIFO, LIFO) se respetan

       - La estructura no crash en operaciones secuenciales 

    ✅ Correctitud local:

       - Para los casos de uso probados, no hay fallos evidentes

    ✅ No hay memory leaks obvios (si corre sin SIGSEGV)


9. ¿Qué no demuestra una prueba pública por sí sola?

❌ No valida:

   - **Invariantes de punteros**: ¿Todos los nodos han sido visitables desde la cabeza?
   - **Integridad de enlaces**: ¿`next` de nodo i es realmente el nodo i+1?
   - **Complejidad temporal**: Las operaciones cumplen O(1),O(logn),(n)?
   - **Localidad de memoria**: ¿SEList mantiene caché-locality?
   - **Comportamiento en edge cases internos**: Nodos centinela, bloques vacíos, expansiones
   - **Eficiencia espacial**: ¿Hay fragmentación interna, overhead de punteros?
   - **Correctitud semántica profunda**: ¿Por qué get(i) es O(1+min(i,n−i)) en DLList?

10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, punteros y complejidad?

Porque:

  1. **Pruebas son casos finitos, teoría es universal**: Una prueba con n≤500 no garantiza corrección en n=10^6 

  2. **Invariantes son el "por qué"**:

     - Saber que DLList::remove(i) cuesta O(1+min(i,n−i))explica por qué la estructura es válida
     - Una prueba que "pasa" puede ser por suerte de acceso a posiciones balanceadas

  3. **Punteros son el mecanismo**:

     - Ver pasar assertions no explica cómo dummy y enlaces bidireccionales previenen segmentation faults
     - El enlace prev es esencial para rotate(), no opcional

  4. **Complejidad espacial oculta**:

     - Una prueba puede pasar pero el overhead de punteros hace SEList ineficiente en memoria

  5. **Reutilización confiable**: Cuando adaptes la estructura (ejemplo: SEList a BDeque), necesitas entender los invariantes para no romper la abstracción

#### BLOQUE4 - SLLIST, DLLIST Y SELIST: LECTURA CERCANA DEL CODIGO

1. En `SLList`, ¿qué papel cumplen `head`, `tail` y `n`?

 `head`: Puntero al primer nodo de la lista. Permite acceso rápido al inicio para operaciones de pila (`push` / `pop`).

 `tail`: Puntero al último nodo. Permite agregar elementos al final en tiempo constante sin recorrer toda la lista.

 `n`: Contador del número de elementos. Permite responder `size()` sin recorrer la estructura y facilita validaciones.

2. En `SLList::push`, `pop`, `add` y `remove`, ¿qué punteros cambian exactamente?

 | **Operación** | **Punteros que cambian** |
 |---|---|
 | `push(x)` |	`head` (apunta al nuevo nodo), `tail` (solo si `n==0`), `n` |
 | `pop()` | `head` (avanza al siguiente), `tail` (solo si `n==1`), `n` |
 | `add(x)` (al final) | `tail->next` (apunta al nuevo), `tail` (avanza), `n` |
 | `remove()` (frontal) | `head` (avanza), `tail` (solo si `n==1`), `n` |

3. Expliquen cómo funciona `secondLast()` y por qué no puede resolverse directamente con solo mirar `tail`.

 `secondLast()` recorre desde `head` hasta encontrar el nodo cuyo `next` es `tail`. No puede resolverse solo mirando `tail` porque en `SLList` los nodos solo apuntan hacia adelante; el último nodo no tiene referencia al anterior, así que no hay forma de acceder directamente al penúltimo sin recorrer la lista desde el inicio.

4. Expliquen paso a paso cómo funciona`reverse()` y por qué no necesita estructura auxiliar.

`reverse()` recorre la lista una vez y va invirtiendo cada enlace `next` en el camino.

 - Empieza con `prev = nullptr` y `curr = head`.
 - En cada iteración guarda `next = curr->next`, luego cambia `curr->next` para que apunte a `prev`.
 - Después avanza: `prev = curr`, `curr = next`.
 - Al terminar, el antiguo `head` quedó como `tail`, y `head` se actualiza a `prev`, que es el último nodo procesado.
 
No necesita estructura auxiliar porque invierte los enlaces sobre los propios nodos usando solo punteros temporales; no crea nodos nuevos ni copia los datos.

5. Expliquen qué verifica `checkSize()` y por qué esta función ayuda a defender correctitud.

 `checkSize()` recorre la lista contando nodos y luego compara ese conteo con el valor almacenado en `n`. También verifica que, si la lista está vacía, `head` y `tail` sean `nullptr`, y si no lo está, que `tail` apunte realmente al último nodo encontrado. Esto ayuda a defender correctitud porque detecta inconsistencias en el tamaño y en los punteros de la estructura antes de que se propaguen errores.

6. En `DLList`, expliquen por qué `getNode(i)` puede empezar desde el inicio o desde el final.

En `DLList`, `getNode(i)` puede empezar desde el inicio o desde el final porque cada nodo tiene punteros `next` y `prev`.

 - Si `i` está en la primera mitad de la lista, conviene partir desde `dummy.next` y avanzar hacia adelante.
 - Si i está en la segunda mitad, conviene partir desde `dummy`/final y retroceder con `prev`.

Así se usa el recorrido más corto posible, aprovechando la doble dirección de la lista para buscar en tiempo `O(1 + min(i, n-i))` en lugar de siempre recorrer desde un solo extremo.

7. En `DLList::addBefore`, ¿qué enlaces se actualizan y por qué el nodo centinela elimina casos borde?

En `DLList::addBefore`, se inserta un nuevo nodo justo antes de un nodo existente w actualizando estos enlaces:

 - El nuevo nodo recibe `w->prev` como su anterior y `w` como su siguiente.
 - El nodo que antes era previo de `w` ahora apunta hacia el nuevo nodo con su `next`.
 - El nodo `w` actualiza su `prev` para apuntar al nuevo nodo.
  
El centinela `dummy` elimina casos borde porque siempre existe un nodo
“ficticio” en los extremos. Así, insertar antes del primer elemento o antes del nodo `dummy` al final usa la misma lógica que insertar en el medio, sin tener que tratar por separado la lista vacía o el inicio y el fin.

8. Expliquen cómo funciona `rotate(r)` sin mover los datos elemento por elemento.

`Rotate(r)` cambia el “inicio lógico” de la lista realizando un ajuste de punteros, no moviendo los valores de los nodos.

  - Primero calcula el nuevo primer nodo como el nodo en posición `n - r`.
  - Luego toma el último nodo actual y lo enlaza con el primer nodo actual, cerrando temporalmente la lista circularmente.
  - Después corta la lista en el punto correcto: el nuevo último nodo pone su next en el nodo centinela `dummy`, y el nuevo primer nodo recibe `dummy` como su `prev`.
  - Finalmente actualiza `dummy.next` y `dummy.prev` para que reflejen el nuevo primer y último nodo.
     
De esta forma la secuencia lógica cambia de comienzo, pero los datos permanecen en los mismos nodos; solo se reorganizan los enlaces.

**Sin mover datos:**

  - Los valores dentro de los nodos permanecen intactos.
  - Solo se cambian los enlaces de 4-6 punteros.
  - Costo: O(1) después de encontrar `newFirst` (que cuesta `O(min(n-r, r))`).

9. Expliquen cómo `isPalindrome()` aprovecha la naturaleza doblemente enlazada de la estructura.

 `isPalindrome()` usa dos punteros: uno desde el inicio (`left = dummy.next`) y otro desde el final (`right = dummy.prev`). Luego compara elementos emparejados avanzando `left` hacia adelante y `right` hacia atrás. La lista doblemente enlazada hace esto posible porque cada nodo conoce tanto su siguiente como su anterior, de modo que se puede recorrer simultáneamente en ambos sentidos sin invertir la lista ni copiar sus datos.

**Ventaja de ser doblemente enlazada:**

  - Puede recorrer simultáneamente desde ambos extremos.
  - En una lista simple, verificar palíndrome requeriría almacenar valores o invertir.
  - Aquí: solo usa dos punteros y una comparación, costo **O(n/2)**.

10. En `SEList`, expliquen qué representa `Location`.

En `SEList`, `Location` representa una posición dentro de la estructura en dos partes: 

 - `u` es el bloque (`Node`) donde está el elemento.
 - `j` es el índice dentro de ese bloque.

Así, en lugar de buscar el elemento directamente por `i` en una lista enlazada simple, `Location` convierte ese índice global en la ubicación concreta: “está en el bloque `u` y en la posición `j` dentro de ese bloque”.
 
11. Expliquen qué hacen `spread()` y `gather()` y en qué situaciones aparecen.

`spread(Node* u)` - Expande cuando los bloques están llenos

     void spread(Node* u) {
          // Crea b nodos nuevos
          Node* w = u;
          for (int j = 0; j < b; ++j) w = w->next;
          w = addBefore(w);
    
          // Redistribuye elementos: mueve del penúltimo al nuevo bloque
          while (w != u) {
              while (w->d.size() < b) {
                  w->d.add(0, w->prev->d.remove(w->prev->d.size() - 1));
              }
              w = w->prev;
          }
     }

**Cuándo aparece:** Al insertar en una posición donde hay bloques llenos.

`gather(Node* u)` - Compacta cuando los bloques están vacíos

     void gather(Node* u) {
          // Mueve elementos hacia atrás desde bloques casi vacíos
          Node* w = u;
          for (int j = 0; j < b - 1; ++j) {
              while (w->d.size() < b) {
                  w->d.add(w->next->d.remove(0));
                }
         w = w->next;
         }
         removeNode(w);  // Elimina el bloque ahora vacío
     }

**Cuándo aparece:** Al eliminar, si un bloque cae por debajo del umbral mínimo.

12. Expliquen cómo el tamaño de bloque `b` afecta compromiso entre acceso, actualización y uso de espacio.

| **Aspecto** | **Pequeño** `b` | **Grande** `b` |
|---|---|---|
| **Acceso a índice** | Más saltos entre bloques (peor) | Menos saltos (mejor) |
| **Inserción/eliminación** | `spread`/`gather` menos frecuentes (mejor) |  Más costosos cuando ocurren (peor) |
| **Uso de memoria**| Menos desperdicio por sobrecarga de referencias |	Más bloques subutilizados (peor) |
|**Localidad de caché**| Peor (bloques pequeños) | Mejor (bloques grandes explotan caché) |
| **Costo amortizado** | O(n) peor distribución | O(n) mejor distribución |

Compromiso óptimo: b ≈ sqrt(n) o configuración estática (típicamente 3-5) da buen balance general.

#### BLOQUE5 - ADAPTADORES Y ESTRUCTURAS DERIVADAS

1. ¿Cómo reutiliza `LinkedStack` a `SLList`?

 `LinkedStack` reutiliza `SLList` delegando las operaciones principales: push llama a `list.push(x)`, `pop` a `list.pop()`, y `top` a `list.peek()`. Esto aprovecha la eficiencia de inserción y eliminación en el frente de la lista simplemente enlazada.

2. ¿Cómo reutiliza `LinkedQueue` a `SLList`?

 `LinkedQueue` reutiliza `SLList` de manera similar: `add` llama a `list.add(x)` (agrega al final), `remove` a `list.remove()` (elimina del frente), y `front` a `list.peek()`. Utiliza la lista como una cola FIFO, con inserción al final y eliminación del frente.

3. ¿Por qué `LinkedDeque` se construye naturalmente sobre `DLList` y no sobre `SLList`?

 `LinkedDeque` se construye sobre `DLList` porque un deque requiere acceso eficiente a ambos extremos (frente y atrás). `DLList` permite inserciones y eliminaciones en cualquier posición (incluyendo extremos) en tiempo constante, mientras que `SLList` solo es eficiente en un extremo, lo que haría las operaciones en el otro extremo costosas.

4. En `MinStack`, ¿por qué cada entrada guarda el valor y el mínimo acumulado?

 En `MinStack`, cada entrada guarda el valor y el mínimo acumulado para permitir consultas de mínimo en O(1). Al hacer `push`, se compara el nuevo valor con el mínimo actual del tope y se guarda el menor, acumulando el mínimo histórico sin necesidad de recorrer la pila.

5. En `MinQueue`, ¿por qué usar dos pilas permite mantener semántica FIFO y 
consulta de mínimo?

 En `MinQueue`, usar dos pilas (`in_` y `out_`) permite mantener semántica FIFO: `in_` recibe nuevos elementos, y `out_` se usa para remover del frente (moviendo elementos de `in_` a `out_` cuando es necesario, invirtiendo el orden). Cada pila mantiene su propio mínimo, y el mínimo global se obtiene comparando los mínimos de ambas pilas.

6. En `MinDeque`, ¿qué problema resuelve el rebalanceo entre `front_` y `back_`?

 En `MinDeque`, el rebalanceo entre `front_` y `back_` resuelve el problema de mantener operaciones eficientes en ambos extremos. Cuando una pila se vacía, se reconstruye el deque dividiendo los elementos en dos mitades equilibradas, asegurando que ambas pilas tengan elementos y evitando degradación de rendimiento en accesos consecutivos a un extremo.

7. Comparen "implementar una estructura" y "adaptar una estructura existente" usando ejemplos de este bloque.

 "Implementar una estructura" significa crearla desde cero con lógica específica, como `MinStack`, que extiende `SLList` con entradas que rastrean mínimos acumulados. "Adaptar una estructura existente" significa reutilizar una implementación base delegando operaciones, como `LinkedStack`, que adapta `SLList` para comportamiento LIFO sin modificar la lista subyacente.

8. ¿Qué operaciones pueden defender como constantes y cuáles deben defender como amortizadas?

 Operaciones constantes: `size()`, `empty()`, `top()` en `LinkedStack`, `front()` en `LinkedQueue`, `front()` y `back()` en `LinkedDeque` (sin rebalanceo), y `min()` en todas las estructuras min-. Amortizadas: `push()` y `pop()` en `MinStack` (debido a comparaciones), `add()` y `remove()` en `MinQueue` (por movimientos entre pilas), y operaciones en `MinDeque` (debido al rebalanceo periódico).

#### BLOQUE6 - DENG COMO REFUERZO ALGORITMICO Y PUENTE DE INTEGRACION 

1. ¿Qué operaciones del ADT de lista aparecen reforzadas en `DengList`?

 `DengList` refuerza operaciones avanzadas como `sort()` (ordenamiento estable), `dedup()` (eliminación de duplicados consecutivos), `uniquify()` (eliminación de todos los duplicados) y `reverse()` (inversión de la lista), que no están presentes en las listas básicas de Semana 3 como `DLList` o `SEList`. Estas se implementan aprovechando la interfaz rica de `CleanList`.

2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar el resto de estructuras de Semana 3?

 Permite agregar funcionalidades avanzadas (como algoritmos de ordenamiento y deduplicación) sin modificar el código existente de `DLList`, `SEList` u otras estructuras, manteniendo compatibilidad, reutilización y evitando riesgos de introducir errores en implementaciones ya probadas.

3. Expliquen qué hacen `to_deng` y `assign_from_deng`.

 `to_deng` convierte una `DLList` o `SEList` en una `DengList` copiando todos los elementos mediante iteración y `push_back`.
 `assign_from_deng` copia los elementos de una `DengList` de vuelta a una `DLList` o `SEList`, limpiando primero la estructura destino y agregando elementos uno por uno.

4. Expliquen por qué `stable_sort_with_deng` no obliga a reimplementar ordenamiento dentro de `DLList` o `SEList`.

 Porque reutiliza el método `sort()` de `DengList`, que está implementado en `CleanList`. La función convierte la estructura original a `DengList`, aplica el ordenamiento y luego asigna los resultados de vuelta, evitando reescribir la lógica de ordenamiento en cada estructura base.

5. Expliquen qué hace `dedup_with_deng` y qué relación guarda con `deduplicate()
` o `uniquify()` de la teoría.

 `dedup_with_deng` elimina duplicados consecutivos en una `DLList` o `SEList` usando el método `dedup()` de `DengList`, que opera sobre la conversión temporal.
 Se relaciona con `deduplicate()` o `uniquify()` de la teoría, ya que ambas eliminan duplicados, pero `dedup` se enfoca en consecutivos (más eficiente), mientras que `uniquify` elimina todos, requiriendo orden previo.

6. Expliquen por qué `reverse_with_deng` es un ejemplo de reutilización de algoritmos sobre una interfaz común.

 `reverse_with_deng` aplica el método `reverse()` de `DengList` a estructuras de Morin (`DLList` o `SEList`) mediante conversión, demostrando reutilización al aprovechar una interfaz común (`DengList`) para algoritmos que no están implementados directamente en las estructuras base, sin duplicar código.

7. ¿Qué costo adicional introduce la conversión entre estructuras y cuándo vale la pena aceptarlo?

 Introduce costo adicional en tiempo (O(n) para copiar elementos) y espacio (duplicación temporal de la lista).
 Vale la pena cuando el algoritmo es complejo o no implementado en la estructura original, priorizando reutilización y mantenibilidad sobre rendimiento en casos donde n es pequeño o las operaciones son infrecuentes.

#### BLOQUE7 - COMPARACION ENLAZADO VS CONTIGUO, VARIANTES Y EVIDENCIA EXPERIMENTAL

1. Comparen `ArrayDeque` y `LinkedDeque`: ¿qué cambia en representación y qué cambia en costo observable?

 `ArrayDeque` usa un arreglo dinámico contiguo para almacenar elementos, con índices para acceso directo y redimensionamiento cuando es necesario. `LinkedDeque` usa nodos enlazados con referencias prev/next, permitiendo inserciones/eliminaciones eficientes en extremos. En costo observable, `ArrayDeque` tiene acceso O(1) por índice y mejor localidad de memoria (más rápido en recorridos secuenciales), pero inserciones/eliminaciones en posiciones intermedias son O(n) por desplazamientos. `LinkedDeque` tiene inserciones/eliminaciones O(1) en extremos, pero acceso por índice O(n) y peor localidad (más overhead por punteros).

2. ¿Qué significa que una representación contigua tenga mejor localidad de memoria?

 Significa que los elementos están almacenados en posiciones consecutivas de memoria, lo que mejora el aprovechamiento del caché del procesador, reduce fallos de caché y acelera accesos secuenciales o cercanos, ya que el hardware puede prefetch datos eficientemente.

3. ¿Qué tipo de operaciones favorecen más a la representación enlazada?

 Operaciones que involucran inserciones y eliminaciones frecuentes en posiciones arbitrarias (especialmente extremos), donde el costo de ajuste de referencias es bajo comparado con el desplazamiento de elementos en arreglos contiguos.

4. En el benchmark, ¿qué comparación sirve mejor para discutir acceso aleatorio y cuál sirve mejor para discutir operaciones en extremos?

 Para acceso aleatorio: `random_get_arraydeque` vs `random_get_dllist`, ya que mide tiempos de acceso por índice en estructuras contigua vs enlazada. Para operaciones en extremos: `deque_contiguo_arraydeque` vs `deque_enlazado_linkeddeque`, que evalúa inserciones/eliminaciones en extremos (add/remove en ambos lados).

5. ¿Por qué el benchmark no debe leerse como prueba absoluta de superioridad de una estructura sobre otra?

 Porque los resultados dependen de factores como tamaño de datos, patrón de operaciones, hardware (caché, memoria), implementación específica y constantes ocultas; es evidencia experimental para patrones concretos, no una comparación universal, ya que estructuras pueden ser superiores en contextos diferentes.

6. ¿Qué idea intenta mostrar `XorList` respecto al ahorro de punteros?

 Muestra cómo usar XOR para combinar punteros prev y next en un solo campo por nodo, reduciendo el espacio de memoria al eliminar un puntero explícito, aprovechando que prev ^ next = link, permitiendo navegación bidireccional con menos overhead.

7. ¿Qué desventaja práctica introduce una estructura como `XorList` aunque sea interesante desde el punto de vista del espacio?.

 Esta estructura eleva la dificultad técnica tanto en su desarrollo como en su conservación, conlleva el peligro de fallos por la gestión de punteros XOR, carece de soporte nativo para la recolección automática de memoria y complica el rastreo de errores al ser un diseño poco convencional que exige una precisión extrema.

#### BLOQUE8 - CIERRE COMPARATIVO Y PREPARACION DE SUSTENTACION

¿Qué cambia cuando pasamos de "usar arreglos dinámicos" a "diseñar estructuras enlazadas y adaptadores sobre nodos"?

 - **Una afirmación sobre representación**: La representación cambia de un bloque contiguo de memoria en arreglos dinámicos a nodos independientes conectados por punteros en estructuras enlazadas, lo que permite crecimiento flexible pero introduce overhead por referencias.
 - **Una afirmación sobre acceso por rango frente a acceso por posición**: En arreglos dinámicos, el acceso por rango (índice directo) es O(1), mientras que en estructuras enlazadas el acceso por posición requiere traversal O(n) desde un extremo o enlace, priorizando referencias sobre índices.
 - **Una afirmación sobre inserciones y eliminaciones locales**: Las inserciones y eliminaciones locales son más eficientes en estructuras enlazadas (O(1) en extremos), ya que solo ajustan punteros, en contraste con arreglos dinámicos que requieren desplazamientos O(n) para mantener contigüidad.
 - **Una afirmación sobre complejidad de `SLList`, `DLList` y `SEList`**: `SLList` ofrece complejidad O(1) para operaciones de pila y cola; `DLList` permite acceso y modificación en O(1 + min(i, n-i)) aprovechando enlaces bidireccionales; `SEList` combina bloques para acceso amortizado O(1 + i/b) y actualizaciones locales eficientes, equilibrando espacio y tiempo.
 - **Una afirmación sobre reutilización mediante adaptadores o puentes**: La reutilización mediante adaptadores (como `LinkedStack` sobre `SLList`) o puentes (como `MorinDengBridge`) permite implementar interfaces nuevas sobre estructuras existentes sin reescribir lógica, facilitando composición y evitando duplicación de código.
 - **Una comparación entre representación contigua y enlazada**: La representación contigua (arreglos) favorece acceso aleatorio y localidad de memoria para recorridos secuenciales, mientras que la enlazada prioriza modificaciones locales y flexibilidad espacial, con trade-offs en complejidad y overhead.

#### AUTOEVALUCION BREVE

**Qué podemos defender con seguridad**:

 - SLList: push/pop O(1); buena para Stack/Queue, no para Deque
 - DLList: getNode(i) → O(1 + min(i, n-i)); centinela elimina casos especiales
 - Adaptadores reutilizan estructuras sin reescribir
 - MinStack/MinQueue: min() en O(1) guardando mínimo acumulado
 
**Qué todavía confundimos**:

 - Por qué DLList es O(1 + min(i, n-i)) y SLList es O(i)
 - Caso especial: pop() con 1 elemento → head = tail = nullptr
 - Rol exacto del centinela `dummy`
 - Cuándo SEList vale la pena vs DLList simple
 
**Qué evidencia usaríamos**:

 - Ejecutar demos: `sem3_demo_sllist`, `sem3_demo_dllist`, `sem3_demo_selist`
 - Mostrar código: qué punteros cambian en push(), reverse(), getNode(i)
 - Pasar `test_public_week3` con casos borde (lista vacía, 1 elemento)
 - Defender invariante: head → primer nodo, tail → último nodo, n = count

