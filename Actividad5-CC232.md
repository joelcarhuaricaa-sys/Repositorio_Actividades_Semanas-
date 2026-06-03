# Actividad 5 - CC232

### INTEGRANTES
 - Joel Gustavo Carhuarica Aguilar

#### Bloque 1 - Núcleo conceptual de la semana
 
1. Explica con tus palabras qué diferencia hay entre un árbol binario enlazado y un árbol binario almacenado implícitamente en un arreglo.

 Árbol binario enlazado:

   Cada nodo es una estructura que contiene explícitamente punteros a su hijo izquierdo, hijo derecho y padre.
   La forma del árbol se representa mediante estos enlaces dinámicos.
   Permite que el árbol tenga cualquier forma balanceada o degenerada sin restricciones sobre posiciones.
   Ocupa memoria dinámica distribuida en la memoria heap.
   Acceso a padres e hijos es directo (O(1)) mediante punteros.

Árbol binario implícito en arreglo:

   Los nodos se almacenan secuencialmente en un arreglo.
   La estructura jerárquica se codifica mediante índices: para un nodo en posición i:
   Hijo izquierdo está en posición 2*i + 1
   Hijo derecho está en posición 2*i + 2
   Padre está en posición (i-1)/2
   Requiere que el árbol esté relativamente completo para evitar desperdicio de espacio.
   Es ideal para heaps porque garantiza complejidad espacial óptima.
   No requiere punteros explícitos, lo que mejora la localidad de caché.

2. Explica qué información guarda un `BinNode`: dato, padre, hijo izquierdo, hijo derecho y altura.

  Según BinNode.h, cada nodo almacena:
   
 ```C++
 T data;           // El dato genérico almacenado
 Node* parent;     // Puntero al padre (nullptr si es raíz)
 Node* left;       // Puntero al hijo izquierdo (nullptr si no existe)
 Node* right;      // Puntero al hijo derecho (nullptr si no existe)
 int height;       // Altura del subárbol enraizado en este nodo
 ```

 Propósito de cada campo:

 - data: Almacena el valor de tipo T que el nodo representa.
 - parent: Permite navegar hacia la raíz y calcular profundidad sin recursión.
 - left, right: Definen la estructura binaria del árbol y permiten recorridos descendentes.
 - height: Se mantiene actualizado para operaciones de balanceo, cálculo de altura eficiente, y diseño de AVLs/rotaciones. Almacenar altura evita recalcularla cada vez (O(n) → O(1)).

3. Explica por qué el puntero `parent` permite implementar operaciones como `succ()`, `pred()` y actualización ascendente de alturas.

   Para succ() (sucesor inorden):
   El sucesor inorden de un nodo tiene dos casos:

  - Si tiene hijo derecho: Es el nodo más a la izquierda del subárbol derecho.
  - Si no tiene hijo derecho: Debe subir por los ancestros hasta encontrar el primer giro hacia la izquierda (cuando un nodo es hijo izquierdo de su padre, ese padre es el sucesor).
  
  Sin parent, subir es imposible. Con parent, implementamos:

 ```C++
 if (right != nullptr) {
     return right->leftmost();  // Buscar el nodo más a la izquierda
 }
 while (this->isRightChild()) {
     this = this->parent;       // Subir mientras seamos hijo derecho
 }
 return this->parent;           // El padre es el sucesor
 ```

   Para pred() (predecesor inorden):

 Simétricamente, buscamos el nodo más a la derecha del subárbol izquierdo, o subimos por ancestros hasta encontrar un giro hacia la derecha.

 Para actualización ascendente de alturas:
   Después de insertar/eliminar un nodo, necesitamos actualizar la altura de todos los ancestros:

  ```C++
  void updateHeightAbove(Node* node) {
  while (node != nullptr) {
  updateHeight(node);
  node = node->parent;  // Subir al padre
  }
  }
  ```
 Sin parent, habría que recorrer desde la raíz nuevamente, lo que es ineficiente.

4.  Explica qué responsabilidad tiene `BinTree` frente a `BinNode`.
   
 BinNode es la estructura de datos primitiva: solo define qué contiene un nodo individual (datos, enlaces, altura).

 BinTree es el contenedor y administrador de la estructura completa:

  - Mantiene una referencia a la raíz (root_) y el tamaño total (size_).
  - Gestiona la creación y destrucción de nodos (insertAsRoot, insertAsLC,   insertAsRC, clear).
  - Realiza operaciones estructurales: adjunción de subárboles (attachAsLC, attachAsRC), separación (secede), y eliminación de subárboles (removeSubtree).
  - Actualiza invariantes globales: altura, tamaño, conectividad.
  - Proporciona interface para recorridos que deleguen a los métodos de BinNode.

 Analogía:**BinNode** es como una célula; **BinTree** es el organismo que coordina células.

5. Explica qué agrega `BinaryTree` sobre la infraestructura base de `BinTree`.

 BinaryTree hereda de BinTree y añade una capa de navegación y utilidades de Morin:

  - Métodos de cálculo de propiedades:

     - depth(node): Calcula la profundidad desde la raíz subiendo por parent.
     - height(node): Calcula altura recursivamente.
     - subtreeSize(node): Calcula tamaño de un subárbol.

  - Navegación eficiente:

     - firstNode(): Retorna el nodo más a la izquierda (mínimo inorden).
     - lastNode(): Retorna el nodo más a la derecha (máximo inorden).
     - nextNode(), prevNode(): Acceso a sucesor y predecesor.

  - Iteradores:

     - iterator y node_iterator para recorrer el árbol inorden como una secuencia.
     - begin(), end() para bucles for.

  - Métodos de iteración alternativos:

     - iterateBySuccessor(), iterateByPredecessor(): Usan sucesor/predecesor.
     - traverseInorder(), traverseBreadthFirst(): Wraps de los métodos base.

  - Representación visual:

     - asciiArt(): Imprime el árbol en formato ASCII.

 BinaryTree no añade propiedades estructurales, solo comodidades para trabajar con árboles binarios ya construidos.

6. Explica qué propiedad adicional convierte un árbol binario en un `BinarySearchTree`.

 La propiedad de búsqueda binaria (BST property):

 Para todo nodo u con dato data(u):

     - Todo nodo en el subárbol izquierdo satisface: data(nodo) < data(u) (usando el comparador). 
     - Todo nodo en el subárbol derecho satisface: data(u) < data(nodo) (usando el comparador).

 Esto implica:

     - No hay duplicados (un elemento no puede ser < u y > u simultáneamente).
     - El inorden produce secuencia ordenada.
     - Búsqueda es logarítmica en árboles balanceados.

 La clase BinarySearchTree mantiene esta propiedad mediante:

     - findLast(): Encuentra dónde insertar un nuevo valor.
     - addChild(): Inserta respetando la propiedad.
     - remove() y splice(): Eliminan sin violar la propiedad.
     - isBST(): Valida la propiedad.

7. Explica qué propiedad adicional convierte un arreglo en un `BinaryHeap` mínimo.
 
 La propiedad de heap mínimo (min-heap property):

 Para todo nodo u en posición i:

     - El valor en u es ≤ que los valores de sus hijos.
     - Específicamente: data[i] ≤ data[2*i+1] y data[i] ≤ data[2*i+2] (cuando existen).

 - Esto implica:

     - El mínimo está siempre en la raíz (posición 0): Acceso O(1).
     - Inserción y eliminación en O(log n) usando bubbleUp y trickleDown.
     - Construcción desde arreglo en O(n) usando heapify().

 Para máximo heap, la propiedad es inversa: data[i] ≥ data[hijos].
 
8. Compara la propiedad de orden de un BST con la propiedad de prioridad de un heap.

  | Aspecto | BST | Heap |  
  | :--- | :--- | :--- | 
  | Representacion | Arbol enlazado | Arreglo implicito | 
  | Propiedad | Izquierda< nodo < derecha | Padre ≤ hijos (min-heap) |
  | Alcance	| Global: toda la estructura | Local: solo relación padre-hijo | 
  | Orden inorden | Secuencia completamente ordenada | Sin orden garantizado | 
  | Búsqueda de elemento | O(log n) en balanceado | 
  | Búsqueda de elemento | O(log n) en balanceado |	O(n) (no hay búsqueda eficiente) |
  | Búsqueda de extremo | O(log n) | O(1) |
  | Inserción |	O(log n) en balanceado | O(log n) |
  | Eliminación | O(log n) en balanceado | O(log n) |
  | Duplicados | No permitidos (típicamente) | Permitidos |
  | Caso de uso | Ordenamiento, búsqueda, rango | Colas de prioridad, heapsort |

9. Explica por qué un recorrido inorden de un BST produce una secuencia ordenada.

 Razón fundamental: La propiedad BST define una relación de orden entre subárboles.

 Prueba por inducción estructural:

     Base: Un árbol con un solo nodo produce la secuencia con ese único elemento, que trivialmente está ordenada.

 Paso inductivo: Sea u un nodo no vacío. El inorden de u es:

     1.Inorden del subárbol izquierdo
     2. El valor de u
     3. Inorden del subárbol derecho

 Por hipótesis inductiva:

     - El subárbol izquierdo produce una secuencia ordenada con todos los valores < data(u).
     - El subárbol derecho produce una secuencia ordenada con todos los valores > data(u).

 Al concatenar: [valores < u] + [u] + [valores > u], el resultado es una secuencia ordenada.

10. Explica por qué un heap no permite, por sí solo, recorrer los elementos en orden sin destruir o copiar la estructura.

 Razón: La propiedad de heap solo garantiza el mínimo en la raíz; no ordena globalmente.

 Problema: Para obtener elementos en orden sin modificar la estructura, habría que:

   1. Copiar el heap completo.
   2. Extraer todos los elementos con remove(), que destruye el heap mientras extrae.

 Costo de extracción ordenada:

   - Usar remove() n veces: O(n log n) pero destruye la estructura.
   - Usar heapsort: O(n log n) con copia destructiva.
 
 Los heaps son óptimos para acceso rápido al mínimo/máximo, no para recorrido ordenado.

#### Bloque 2 - Navegación, altura, profundidad y tamaño

1. En `BinNode`, explica qué significan `hasLeft()`, `hasRight()`, `isRoot()`, `isLeaf()`, `isLeftChild()` e `isRightChild()`.

 - **hasLeft()**
     Verifica si el nodo tiene hijo izquierdo
 ```C++
 bool hasLeft() const { return left != nullptr; }
 ```
 Retorna true cuando left apunta a un nodo válido.

 - **hasRight()**
     Verifica si el nodo tiene hijo derecho.
 ```C++
 bool hasRight() const { return right != nullptr; }
 ```

 - **isRoot()**
     Determina si el nodo es la raíz del árbol.
 ```C++
 bool isRoot() const { return parent == nullptr; }
 ```
 La raíz no tiene padre.

 - **isLeaf()**
     Verifica si el nodo es hoja.
 ```C++
 bool isLeaf() const { return left == nullptr && right == nullptr; }
 ```
 Un nodo hoja no tiene hijos.

 - **isLeftChild()**
     Determina si el nodo es hijo izquierdo de su padre.
 ```C++
 bool isLeftChild() const {
    return parent != nullptr && parent->left == this;
 }
 ```

 - **isRightChild()**
     Determina si el nodo es hijo derecho de su padre.
 ```C++
 bool isRightChild() const {
    return parent != nullptr && parent->right == this;
 }
 ```

2. Explica el caso en que `succ()` baja al subárbol derecho y luego busca el nodo más a la izquierda.

 El sucesor inorden de un nodo es el siguiente nodo que aparecería en un recorrido inorden.

 En un recorrido inorden:

  1. Subárbol izquierdo
  2. Nodo actual
  3. Subárbol derecho

 Si un nodo tiene hijo derecho, entonces su sucesor estará dentro de ese subárbol derecho.
 
 ```C++
 if (right != nullptr) {
    s = right;
    while (s->left != nullptr) {
        s = s->left;
    }
    return s;
 }
 ```
 Proceso:

 - Baja al hijo derecho.
 - Luego avanza todo lo posible hacia la izquierda.
 - El nodo más izquierdo del subárbol derecho es el  siguiente en inorden.

 Ejemplo:

         7
        / \
       3   10
          /  \
         8   12

 Sucesor de 7:

 - Va a 10
 - Luego busca el más izquierdo -> 8
 - Resultado: sucesor de 7 es 8.  

3. Explica el caso en que `succ()` sube por los ancestros hasta encontrar el primer giro hacia la izquierda.
 
 Si el nodo NO tiene hijo derecho, el sucesor no está debajo de él.

 Entonces se sube usando parent.

 ```C++
 while (s->isRightChild()) {
    s = s->parent;
 }
 return s->parent;
 ```

4. Explica simétricamente cómo debe funcionar `pred()`.

 El predecesor inorden es el nodo inmediatamente anterior en el recorrido. Funciona de manera exactamente inversa (espejo) a **succ()**:
 
   1. Si tiene subárbol izquierdo (**left != nullptr**): El predecesor será el nodo que esté más a la derecha dentro de ese subárbol izquierdo. El algoritmo baja a **left** y luego ejecuta un bucle **while (s->right != nullptr) { s = s->right; }.**
  
   2. Si no tiene subárbol izquierdo (**left == nullptr**): Significa que debemos buscar hacia arriba en los ancestros. Subimos por los padres mientras el nodo actual sea un hijo izquierdo (**while (s->isLeftChild()) { s = s->parent; }**). El bucle se detiene en el primer giro a la derecha, y el predecesor será el padre de ese nodo (**s->parent**).

5. Dibuja un árbol de al menos 7 nodos y marca el sucesor y predecesor inorden de tres nodos distintos.

 Utilizando la misma estructura del árbol del código proporcionado en tu demo_binary_tree.cpp, este es el esquema de sus 9 nodos:

          7
        /   \
       3     10
      / \   /  \
     1   5 8    12
        / \
       4   6

 Evaluemos el sucesor y predecesor inorden de tres nodos distintos (recorrido inorden completo: **1, 3, 4, 5, 6, 7, 8, 10, 12**):

 Nodo [5]:

    Predecesor: Tiene hijo izquierdo (4). El más a la derecha de ese subárbol es 4.

    Sucesor: Tiene hijo derecho (6). El más a la izquierda de ese subárbol es 6.

 Nodo [6]:

    Predecesor: No tiene hijo izquierdo. Sube. Como 6 es hijo derecho de 5, el bucle de pred() no entra, y se detiene inmediatamente. Su padre es 5.

    Sucesor: No tiene hijo derecho. Sube. Como 6 es hijo derecho de 5, sube a 5. Como 5 es hijo derecho de 3, sube a 3. 3 es hijo izquierdo de 7 (rompe el bucle de succ()), por lo tanto el sucesor es el padre de 3, que es 7.

 Nodo [8]:

    Predecesor: No tiene hijo izquierdo. Sube. 8 es hijo izquierdo de 10. Sube a 10. 10 es hijo derecho de 7. Sube a 7. Como 7 es raíz, el bucle termina. El padre de 7 es nullptr, pero la condición se rompió en 8 (que es hijo izquierdo de 10), devolviendo el padre de 8 que es 7.

    Sucesor: No tiene hijo derecho. Sube. 8 es hijo izquierdo de 10 (rompe el bucle). El padre es 10.

6. Explica qué calcula `depth(u)` y por qué puede implementarse subiendo por `parent`.

 La profundidad **depth(u)** calcula la distancia (número de aristas) desde la raíz del árbol hasta el nodo u. La raíz tiene profundidad 0.Se puede implementar subiendo por **parent** porque la relación jerárquica de un árbol binario garantiza que cada nodo (excepto la raíz) tiene exactamente un único padre. Por lo tanto, existe un camino lineal e inequívoco desde cualquier nodo hacia la raíz. Simplemente se cuenta cuántas veces podemos saltar a **node->parent** antes de llegar a **root_** o a un puntero nulo. Su complejidad temporal es O(d) donde $d$ es la profundidad del nodo.

7. Explica qué calcula `height(u)` y por qué suele implementarse bajando recursivamente por los hijos.

 La altura **height(u)** calcula la distancia de la trayectoria más larga desde el nodo $u$ hasta una hoja de su subárbol. Una hoja tiene altura 0 (y un nodo nulo tiene altura -1).
 
 Se implementa bajando recursivamente porque un nodo puede tener dos caminos/subárboles distintos (izquierdo y derecho). No se puede conocer la altura de un nodo sin explorar ambas ramas, ya que la altura está determinada por el máximo de las alturas de sus hijos:

      height(u) = 1 + max(height(u.left),height(u.right))
   
 La recursión divide el problema descendiendo hasta las hojas para calcular el tamaño de los caminos y luego "arrastra" de vuelta el valor máximo hacia arriba.

8. Explica qué calcula `subtreeSize(u)`.

 Calcula el número total de nodos que componen el subárbol cuya raíz es $u$ (incluyendo al propio nodo $u$).
 Se define matemáticamente de forma recursiva como:
 
     subtreeSize(u) = 1 + subtreeSize(u.left) + subtreeSize(u.right)

 Donde el tamaño de un nodo nulo (nullptr) es 0.

9. Demuestra que para todo nodo `u` se cumple `depth(u) + height(u) <= height(T)`.

  Definiciones:

  - height(T) es la longitud del camino más largo desde la raíz de T hasta cualquier hoja del árbol completo.
  - depth(u) es la longitud del camino único desde la raíz hasta u.
  - height(u) es la longitud del camino más largo desde $u$ hasta una hoja en el subárbol de u.
 
 Demostración:
 Si unimos el camino único desde la raíz hasta el nodo $u$ (de longitud depth(u) con el camino más largo desde $u$ hasta una hoja de su propio subárbol (de longitud (u)), formamos un camino completo y continuo que va desde la raíz del árbol T hasta una hoja.
 Por definición de altura de un árbol, height(T) es el máximo absoluto de las longitudes de todos los caminos posibles desde la raíz hasta cualquier hoja. Como el camino que pasa por $u$ y sigue su rama más profunda es solo uno de los tantos caminos posibles del árbol, su longitud combinada no puede superar al máximo absoluto del árbol. Por lo tanto:

     depth(u) + height(u) <= height(T)

10. Indica la condición necesaria y suficiente para que se alcance la igualdad anterior.

Para que se cumpla de forma exacta la igualdad:

     depth(u) + height(u) = height(T)

 La condición necesaria y suficiente es que el nodo $u$ debe pertenecer a uno de los caminos más largos (más profundos) del árbol T.
 Es decir, debe existir al menos una hoja con la profundidad máxima del árbol (depth(hoja) = height(T)) que sea descendiente de u (o que sea el propio u). Si u se encuentra en una rama "corta" o menos profunda del árbol, la suma será estrictamente menor a height(T).

#### Bloque 3 - Recorridos y trazado guiado

          7
        /   \
       3     10
      / \   /  \
     1   5 8    12
        / \
       4   6

 | Recorrido | Versión revisada | Estructura auxiliar usada | Secuencia producida en el árbol de prueba | Argumento de correctitud y costo |
 |---|---|---|---|---|
 | Preorden recursivo | **travPre** | Ninguna explícita (Pila de llamadas del sistema). | **7 3 1 5 4 6 10 8 12** | Correctitud: Procesa la raíz, luego el subárbol izquierdo y finalmente el derecho de forma auto-similar.Costo: Tiempo O(n), Memoria O(h). |
 | Preorden iterativo | **travPreIterative2** | **std::stack<Node*>** explícita. | **7 3 1 5 4 6 10 8 12** | Correctitud: Simula la recursión guardando los hijos. Apila primero el derecho y luego el izquierdo para que el izquierdo se procese antes.Costo: Tiempo O(n), Memoria O(h). |
 | Inorden recursivo | **travInRecursive** | Ninguna explícita (Pila de llamadas del sistema). | **1 3 4 5 6 7 8 10 12** | Correctitud: Visita el subárbol izquierdo, procesa la raíz y luego el subárbol derecho. En un BST, genera la secuencia ordenada.Costo: Tiempo O(n), Memoria O(h). |
 | Inorden iterativo #1 | **travInIterative1** | **std::stack<Node*>** explícita. | **1 3 4 5 6 7 8 10 12** | Correctitud: Baja por la izquierda metiendo nodos a la pila hasta el extremo inferior. Al desapilar, procesa el nodo y se desplaza a su derecha.Costo: Tiempo O(n), Memoria O(h). |
 | Inorden iterativo #2 | **travInIterative2** | Ninguna (usa punteros **parent** de la estructura). | **1 3 4 5 6 7 8 10 12** | Correctitud: Utiliza una máquina de estados comparando **prev** y **curr** para saber si está bajando (por izq/der) o subiendo desde un hijo.Costo: Tiempo O(n), Memoria O(1) constante. | 
 | Inorden iterativo #3 | **travInIterative3** | Ninguna (usa los métodos **leftmost()** y **succ()**). | **1 3 4 5 6 7 8 10 12** | Correctitud: Se posiciona en el primer nodo inorden (**leftmost**) y avanza a través de la función del sucesor directo (**succ**) basada en punteros.Costo: Tiempo O(n) amortizado, Memoria O(1). |
 | Postorden recursivo | **travPost** | Ninguna explícita (Pila de llamadas del sistema). | **1 4 6 5 3 8 12 10 7** | Correctitud: Procesa recursivamente ambos hijos (izquierdo y luego derecho) antes de procesar el nodo actual (raíz).Costo: Tiempo O(n), Memoria O(h). | 
 | Postorden iterativo | **travPostIterative** | Dos pilas (**s1** y **s2**). | **1 4 6 5 3 8 12 10 7** | Correctitud: **s1** genera un recorrido "raíz-derecha-izquierda" que al transferirse inversamente a **s2** resulta en "izquierda-derecha-raíz".Costo: Tiempo O(n), Memoria O(n) (debido a **s2**). |
 | Por niveles | **travLevel** | **std::queue<Node*>** explícita. | **7 3 10 1 5 8 12 4 6** | Correctitud: Implementa un recorrido BFS (Breadth-First Search). Encola los hijos de izquierda a derecha conforme extrae los padres.Costo: Tiempo O(n), Memoria O(w) (ancho máximo del árbol). |

1. ¿Qué significa visitar un nodo en preorden?

 Significa procesar o evaluar la información del nodo antes de explorar sus subárboles. El orden estricto de ejecución es: Raíz -> Subárbol Izquierdo -> Subárbol Derecho.
  
2. ¿Qué significa visitar un nodo en inorden?

 Significa procesar el nodo en el punto medio de la exploración estructural. Se exploran todos los elementos del Subárbol Izquierdo, luego se procesa la Raíz, y finalmente se explora el Subárbol Derecho. En árboles binarios de búsqueda (BST), este recorrido garantiza extraer los elementos en orden ascendente.

3. ¿Qué significa visitar un nodo en postorden?

 Significa posponer el procesamiento de la raíz hasta que todos sus descendientes directos hayan sido completamente visitados. El orden es: Subárbol Izquierdo -> Subárbol Derecho -> Raíz. Es ideal para operaciones de destrucción (como el método **destroy** de tu código) porque no puedes borrar un padre sin haber borrado sus hijos primero.

4. ¿Qué significa visitar un árbol por niveles?

 Significa realizar un recorrido horizontal (BFS). Se procesan los nodos en orden estrictamente creciente de su profundidad (Nivel 0, luego Nivel 1, Nivel 2, etc.) y, dentro de un mismo nivel, se leen de izquierda a derecha.

5. ¿Por qué los recorridos recursivos tienen tiempo `O(n)`?

 Porque cada nodo del árbol es visitado una cantidad finita y constante de veces (entrando a la función, y retornando de los hijos izquierdo y derecho). Al haber exactamente $n$ nodos, el trabajo total es directamente proporcional a la cantidad de elementos: T(n) = c .n.

6. ¿Por qué las versiones iterativas también tienen tiempo `O(n)`?

 Porque simulan exactamente la misma lógica sin el overhead de la recursión. En las versiones con pila/cola, cada nodo es insertado (**push**) y extraído (**pop**) exactamente una vez. En la versión **Iterative3** (por sucesor), aunque el algoritmo sube y baja buscando el sucesor, ninguna arista del árbol se recorre más de 2 o 3 veces en total durante todo el proceso, lo que resulta en un tiempo total amortizado lineal de O(n).

7. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol balanceado?

 En un árbol perfectamente balanceado, la altura del árbol está acotada por h = log sub2(n). Como la pila de llamadas del sistema (call stack) crece proporcionalmente a la profundidad máxima alcanzada, el consumo de memoria auxiliar será de O(log n).

8. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol degenerado?

 Un árbol degenerado (o "skewer") se comporta como una lista enlazada, donde cada nodo tiene un solo hijo. Su altura es h = n - 1. Por lo tanto, la pila de llamadas del sistema acumulará todos los nodos antes de empezar a retornar, consumiendo una memoria de O(n).

9. ¿Qué diferencia hay entre usar una pila explícita y usar la pila de llamadas?

 - Pila de llamadas (Recursión): Es manejada automáticamente por el sistema operativo y la arquitectura de hardware. Guarda no solo el puntero al nodo, sino también variables locales, registros de la CPU y la dirección de retorno. Puede provocar un error de desbordamiento de pila (stack overflow) si el árbol es excesivamente profundo.

 - Pila explícita (**std::stack**): Se aloja en la memoria dinámica (heap). Almacena únicamente la información estrictamente necesaria (en tu caso, un puntero Node* de 8 bytes). Es mucho más eficiente en uso de memoria real y es virtualmente inmune al stack overflow, limitada únicamente por la RAM total del sistema.

10. ¿Por qué la cola del recorrido por niveles puede crecer mucho más en un árbol completo que en un árbol degenerado?.

 La memoria de la cola depende del ancho máximo (w) del árbol.
 
  - En un árbol degenerado, el ancho de cada nivel es siempre 1. La cola nunca tendrá más de 1 o 2 elementos al mismo tiempo.
  - En un árbol completo, el último nivel contiene aproximadamente la mitad de todos los nodos del árbol ([n/2]). Cuando el algoritmo procesa el penúltimo nivel, añade todos los hijos a la cola simultáneamente, provocando que esta almacene hasta O(n) nodos en su punto crítico.
 
#### Bloque 4 - Demostración: evidencia observable

 | Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |  
 | :--- | :--- | :--- | :--- |
 | **demo_binary_tree.cpp** | Impresión de los 3 tipos de inorden iterativo coincidiendo exactamente con el inorden recursivo. Coincidencia de **succ()** y **pred()** con los vecinos del vector. | Árbol binario enlazado explícitamente (**insertAsLC**, **insertAsRC**) con punteros al padre (**checkParentLinks**). | Los recorridos iterativos avanzados (como la estrategia 3 usando el puntero **parent**) logran un costo espacial de O(1) adicional frente al O(h) de la recursión. | 
 | **demo_bst.cpp** | **bst.inorder()** produce los elementos estrictamente ordenados **{1, 3, 4, 5, 6, 7, 8, 10, 12}**. La salida de **buildBalancedFromSorted** muestra un árbol balanceado. | Árbol Binario de Búsqueda (BST) con propiedad de orden de claves:izq < nodo < der. Operaciones de rotación. | Las búsquedas toman O(h). **buildBalancedFromSorted** construye un árbol óptimo con h = [logsub2(n)] a partir de un vector en O(n) tiempo y espacio. | 
 | **demo_capitulo5_panorama.cpp** | Uso de un bucle **for (int x : bst)** directo sobre el árbol binario de búsqueda. | Integración de iteradores estándar (estilo STL) sobre estructuras de árboles enlazados mediante el uso de operadores **++**. | El diseño del iterador encapsula la lógica de **succ()**, permitiendo un recorrido completo del árbol en tiempo O(n) y con la flexibilidad sintáctica de C++. |
 | **demo_heap.cpp** | El vector inicial se transforma en **[1, 3, 2, 7, 5, 8, 10]**. Las sucesivas llamadas a **remove()** extraen los elementos en orden ascendente estricto. | Montículo binario (Min-Heap) representado implícitamente sobre un arreglo/vector secuencial indexado. | El constructor (**heapify**) toma O(n) en tiempo "bottom-up", una mejora de diseño frente a realizar $n$ inserciones individuales (**add**), que costarían O(nlogn). | 

1. En `demo_binary_tree.cpp`, ¿qué salida permite verificar que los recorridos visitan los nodos en el orden esperado?
 
 La salida impresa por **printVector** para cada una de las estrategias. Específicamente, el hecho de que las 4 líneas de salida correspondientes al Inorden coincidan exactamente en su contenido, sin importar si se ejecutaron de manera recursiva o mediante las tres variantes iterativas (**Iterative1**, **Iterative2**, **Iterative3**).

2. ¿Qué parte de la demo permite defender que `succ()` y `pred()` respetan el orden inorden?

 La sección final donde se evalúa el nodo con valor **5**:

   - El inorden teórico del árbol es: **1 4 5 6 7 8 10 12**.

   - La demo evalúa **n5->succ()** y **n5->pred()**, imprimiendo **Sucesor de 5: 6** y **Predecesor de 5: 4**. Estos resultados coinciden con sus vecinos inmediatos en el recorrido inorden.

3. ¿Qué evidencia produce la representación ASCII del árbol?

 Produce la estructura jerárquica y el balance visual del árbol (**std::cout << tree;**). Permite verificar de forma empírica y directa las relaciones de parentesco (cuáles nodos son hijos izquierdos o derechos de quién) y constatar visualmente la altura y profundidad de la estructura antes de que se calculen programáticamente.

4. En `demo_bst.cpp`, ¿qué observable permite defender que el inorden del BST queda ordenado?

 La salida de la función **printVector("BST inorden", bst.inorder());**. Al pasarle al BST el conjunto desordenado **{7, 3, 10, 1, 5, 8, 12, 4, 6}**, el método **inorder()** devuelve un vector cuyos elementos están ordenados de menor a mayor de forma matemática perfecta (**1 3 4 5 6 7 8 10 12**).

5. ¿Qué operaciones de búsqueda se distinguen mejor en la demo del BST: `find`, `findEQ`, `lowerBound` o `upperBound`?

 Se distinguen mejor **lowerBound** y **upperBound**. La demo busca el valor **9** (que no existe en el árbol) y **lowerBound(9)** devuelve exitosamente **10** (el menor elemento mayor o igual a 9). Asimismo, busca **upperBound(8)** y devuelve **10** (el primer elemento estrictamente mayor a 8). Esto demuestra el comportamiento de rango de estas funciones por encima de una búsqueda exacta ordinaria.

6. En `demo_heap.cpp`, ¿qué salida permite defender que el mínimo queda en la raíz?

  1.  La primera posición del vector (índice 0) devuelta por **heap.data()** tras el constructor es el elemento **1** (el mínimo del conjunto inicial).

  2.  La salida consecutiva de **heap.remove()** en el bucle **while**, que extrae e imprime el elemento mínimo disponible en cada paso, vaciando el heap en orden estrictamente ascendente (**0 1 2 3 5 7 8 10**).

7. ¿Qué evidencia permite distinguir entre insertar con `add()` y construir con `heapify()`?

 La disposición interna del vector (**heap.data()**). Al construir con el vector inicial mediante heapify, los elementos se organizan eficientemente desde abajo hacia arriba resultando en una estructura válida para el árbol pero compacta. Al ejecutar **heap.add(0)**, el elemento nuevo rompe momentáneamente la propiedad de orden en la última posición y es forzado a "flotar" (bubble-up) hasta la raíz, alterando el vector a **[0, 1, 2, 3, 5, 8, 10, 7]**.

8. En `demo_capitulo5_panorama.cpp`, ¿qué comparación resume mejor la semana: árbol enlazado, BST o heap?.

 La comparación que demuestra cómo el BST une las ventajas del árbol enlazado con la capacidad de ordenación.
 Mientras el árbol enlazado genérico carece de orden semántico y el Heap restringe el acceso solo al mínimo (raíz) sacrificando la visibilidad del resto de nodos, el BST provee una estructura enlazada dinámica que permite un recorrido de elementos ordenados lineal y directo (**for (int x : bst)**) compatible con las abstracciones de la biblioteca estándar (STL).

#### Bloque 5 - Pruebas públicas, pruebas internas e invariantes

1. ¿Qué operaciones del BST valida la prueba pública?

 Valida las operaciones principales de un Árbol Binario de Búsqueda (BST):
   
   - `Inserción:` **add(x)**.

   - `Eliminación:` **remove(x)**.

   - `Búsqueda y límites:` **findEQ(x)**, **find(x)**, **lowerBound(x)**, **upperBound(x)**, **minNode()**, **maxNode()** y **contains(x)**.

   - `Recorridos:` **inorder()** (en su versión recursiva y 3 variantes iterativas).

   - `Validación estructural:` **isBST()** y **checkParentLinks()**.

   - `Construcción:` **buildBalancedFromSorted()**.

2. ¿Qué casos validan que el BST no acepta duplicados?

 Se valida explícitamente en el primer bloque del archivo público con la línea:
 ```C++
         expect(!bst.add(5), "BST no debe aceptar duplicados");
 ```
 Previamente ya se había insertado el elemento **5** en la lista inicial **{7, 3, 10, 1, 5, 8, 12, 4, 6}**. Al intentar añadirlo por segunda vez, el método **add(5)** debe retornar **false**.

3. ¿Qué se verifica al comparar el inorden recursivo con las versiones iterativas?

 Se verifica la equivalencia funcional de los algoritmos. Asegura que las tres implementaciones iterativas diferentes (**Iterative1**, **Iterative2**, **Iterative3**) recorren el árbol exactamente en el mismo orden que la versión recursiva estándar, produciendo la secuencia ordenada correcta sin omitir ni duplicar nodos: **{1, 3, 4, 5, 6, 7, 8, 10, 12}**.

4. ¿Qué se espera de `findEQ(8)` en la prueba pública?

 Se espera que localice exactamente el nodo que contiene la clave **8**. La prueba verifica que el puntero devuelto no sea nulo (**nullptr**) y que el valor del campo de datos de ese nodo sea estrictamente igual a **8** (**bst.findEQ(8)->data == 8**).

5. ¿Qué se espera de `lowerBound(9)` y `upperBound(8)`?

 - **lowerBound(9)** (o **find(9)**): Se espera que devuelva el nodo con la clave más pequeña que sea mayor o igual a 9. En este árbol, ese valor es **10**.

 - **upperBound(8)**: Se espera que devuelva el nodo con la clave más pequeña que sea estrictamente mayor que 8. En este árbol, ese valor también es **10**.

6. ¿Qué propiedad se valida con `isBST()`?

 Valida la propiedad de orden del BST: para cualquier nodo N, todos los valores en su subárbol izquierdo deben ser estrictamente menores que el valor de N, y todos los valores en su subárbol derecho deben ser estrictamente mayores que el valor de N.

7. ¿Qué se valida después de eliminar un nodo con `remove()`?

 Tras eliminar el nodo con la clave **3**, la prueba valida tres cosas:

   1. Que el método retorne **true** (borrado exitoso).

   2. Que el árbol mantenga su propiedad de orden (el **inorder()** resultante debe seguir perfectamente ordenado y sin el 3: **{1, 4, 5, 6, 7, 8, 10, 12}**).

   3. Que **contains(3)** devuelva **false**.

   4. Que las conexiones hacia los padres sigan siendo íntegras mediante **checkParentLinks()**.

8. ¿Qué valida `checkParentLinks()` después de borrar, separar o adjuntar subárboles?

 Valida la consistencia bidireccional de los punteros. Asegura que si un nodo A tiene como hijo izquierdo o derecho a un nodo B(A->left == B o A->right == B), entonces el puntero al padre de B apunte correctamente de vuelta a A (B->parent == A). Esto es crucial para garantizar que las operaciones que modifican la estructura del árbol no dejen punteros huérfanos o desactualizados.

9. ¿Qué operaciones del heap valida la prueba pública?

 Valida el algoritmo de construcción masiva u ordenación del heap (**heapify**) al pasarle un vector desordenado en el constructor, la validación de la propiedad de min-heap mediante **isHeap()** e **isHeapArray()**, y la extracción del elemento mínimo a través de **remove()**.

10. ¿Qué demuestra extraer repetidamente de un min-heap hasta vaciarlo?

 Demuestra que el algoritmo de reordenamiento interno tras una remoción (**trickleDown / siftDown**) funciona correctamente. Al vaciar el heap y obtener los elementos en un orden estrictamente ascendente (**{1, 2, 3, 5, 7, 8, 10}**), se comprueba que el elemento en la raíz (**top()**) siempre fue efectivamente el mínimo global remanente. Esto equivale a demostrar el correcto funcionamiento de un Heapsort.

11. ¿Qué operaciones de `BinTree` se validan con `attachAsRC`, `secede` y `removeSubtree`?

 Valida operaciones de cirugía y manipulación de subárboles:

   - **attachAsRC**: Une un árbol externo como el hijo derecho de un nodo, verificando que el tamaño del árbol receptor aumente y el árbol origen quede vacío.

   - **secede**: Desconecta un subárbol completo a partir de un nodo dado, convirtiéndolo en un nuevo árbol independiente, verificando que los tamaños de ambos árboles se actualicen correctamente.

   - **removeSubtree**: Elimina y libera la memoria de un subárbol completo (en este caso la raíz remanente), dejando el árbol anfitrión vacío (**empty()**).

12. ¿Qué agregan las pruebas internas respecto a rotaciones, `bubbleUp`, `trickleDown`, profundidad, altura, sucesor y predecesor?

 Las pruebas internas añaden validaciones de bajo nivel y primitivas estructurales que las pruebas públicas solo asumen indirectamente:

   - `Rotaciones:` Valida **rotateLeft** y **rotateRight**, asegurando que alteren la estructura (cambiando la raíz) pero preserven el orden del BST.

   - **bubbleUp:** Al insertar elementos uno a uno en el heap **{5, 4, 3, 2, 1}**, se valida que el camino flotante hacia arriba funcione llevando el 1 a la raíz.

   - `Propiedades métricas:` Valida el cálculo exacto de la profundidad de un nodo (**depth()**), la altura estructural (**height**), y el tamaño de un subárbol específico (**subtreeSize()**).

   - `Navegación por punteros:` Valida la obtención de los extremos inorden (**firstNode()** y **lastNode()**) y la capacidad de iterar el árbol de forma secuencial sin usar recursión ni pilas auxiliares, saltando directamente a través de **iterateBySuccessor()** (sucesor) y **iterateByPredecessor()** (predecesor).

13. ¿Qué sí demuestra pasar las pruebas públicas?

 Demuestra que la interfaz externa de tus estructuras de datos cumple con los requisitos funcionales básicos para los casos de prueba específicos provistos (caminos felices y operaciones estándar de inserción, borrado y ordenamiento sobre conjuntos de datos pequeños controlados).

14. ¿Qué no demuestra pasar las pruebas públicas?

 No demuestra:
 - `Ausencia de errores en casos esquina (edge cases):` Como árboles vacíos, árboles con un solo nodo, borrado de nodos inexistentes, o inserciones en orden estrictamente decreciente/creciente (árboles degenerados en listas).
 - `Correcta complejidad temporal (O):` Un método podría estar implementado de manera ineficiente (por ejemplo, un **find** lineal O(n) en vez de logarítmico O(log n)) y aun así pasar la prueba si el resultado final es correcto.
 - `Gestión eficiente de memoria:` Podría haber fugas de memoria (memory leaks) al destruir nodos o subárboles (como en **removeSubtree** o **secede**) que los asserts de C++ no detectan directamente a menos que se use una herramienta como Valgrind o Sanitizers.

15. ¿Por qué una defensa correcta debe mencionar invariantes y complejidad además de resultados observables?.

 Porque en estructuras de datos, un resultado observable correcto (un test en "OK") es solo la mitad del trabajo.
 
   1. `Invariantes:` Son las reglas fundamentales que garantizan que la estructura se mantiene estable tras cualquier operación (ej. la propiedad del BST o los enlaces al padre). Si una operación rompe temporalmente un invariante y no lo repara, el siguiente método fallará catastróficamente.
   2. `Complejidad:` El propósito de usar árboles o heaps en lugar de vectores simples es mejorar la eficiencia de las búsquedas, inserciones y extracciones de O(n) a O(logn). Una defensa técnica sólida debe probar que el código no solo es correcto matemáticamente, sino que cumple con las cotas de rendimiento asintótico requeridas para procesar grandes volúmenes de datos.
   