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

#### Bloque 6 - Lectura cercana: `BinNode`, `BinTree` y `BinaryTree`

1. En `BinNode`, ¿qué invariantes deben mantenerse entre `parent`, `left` y `right`?

 Para que el árbol sea estructuralmente válido, los punteros deben ser siempre recíprocos. Es decir:

   - Si un nodo **A** tiene un hijo izquierdo **B** (**A->left == B**), entonces el padre de **B** debe ser **A** (**B->parent == A**).

   - Si un nodo A tiene un hijo derecho **C** (**A->right == C**), entonces el padre de **C** debe ser **A** (**C->parent == A**).

   - Si un nodo no tiene padre (**parent == nullptr**), obligatoriamente debe ser la raíz del árbol.

2. ¿Por qué `insertAsLC` e `insertAsRC` deben rechazar una inserción cuando el hijo correspondiente ya existe?

 Los métodos **insertAsLC** e **insertAsRC** lanzan una excepción (**std::logic_error**) si el hijo ya existe para prevenir la pérdida de memoria (memory leaks) y la desconexión del árbol. Si sobreescribieran el puntero directamente sin liberar el subárbol existente, todos los nodos que colgaban de ese hijo quedarían flotando en la memoria (inaccesibles pero ocupando espacio). Para reemplazar un hijo de forma segura, primero se debe usar explícitamente **removeSubtree** o **secede**.

3. Explica cómo `size()` de `BinNode` recorre el subárbol.

 El método **size()** de **BinNode** calcula de forma recursiva el tamaño total del subárbol del cual dicho nodo es raíz (recorrido en postorden):
 ```C++
 const std::size_t ls = (left == nullptr) ? 0U : left->size();
 const std::size_t rs = (right == nullptr) ? 0U : right->size();
 return 1U + ls + rs;
 ```
   1. Si tiene hijo izquierdo, delega la llamada a **left->size()** (obtiene **ls**).

   2. Si tiene hijo derecho, delega la llamada a **right->size()** (obtiene **rs**).

   3. Finalmente, suma **1U** (el nodo actual) más el tamaño de ambos lados (**ls + rs**) y devuelve el total.

4. Explica cómo funcionan `leftmost()` y `rightmost()`.

 `leftmost():` Se ubica en el nodo actual y se desplaza iterativamente a través de los punteros **left** (**u = u->left**) mientras estos no sean **nullptr**. Retorna el nodo que se encuentra más a la izquierda, que equivale al primer elemento en inorden de ese subárbol.

 `rightmost():` Realiza el proceso inverso. Se desplaza iterativamente a través de los punteros **right** (**u = u->right**) hasta llegar al final. Retorna el nodo más a la derecha, el cual es el último elemento en inorden de ese subárbol.

5. Explica paso a paso cómo funciona `succ()`.

  1. `Tiene hijo derecho (right != nullptr)`: El sucesor es el nodo más a la izquierda de ese subárbol derecho. El código salta a **right** y ejecuta un bucle hacia la izquierda (**while (s->left != nullptr) s = s->left;**).

  2. `No tiene hijo derecho:` El sucesor está hacia arriba. El código sube por la línea de padres mediante un bucle (**while (s->isRightChild()) s = s->parent;**). El bucle se detiene en el primer nodo que no sea un hijo derecho (es decir, que sea un hijo izquierdo de alguien). El padre de este último nodo (**s->parent**) es el sucesor. Si se llega a la raíz y nunca fue hijo izquierdo, **s->parent** será **nullptr**, lo que significa que el nodo original era el último del árbol.

6. Explica paso a paso cómo funciona `pred()`.

 Es el espejo exacto de **succ()**, buscando el nodo anterior en inorden:

   1. `Tiene hijo izquierdo (left != nullptr):` El predecesor es el nodo más a la derecha de ese subárbol izquierdo. Salta a **left** y hace un bucle hacia la derecha (**while (s->right != nullptr) s = s->right;**).
 
   2. `No tiene hijo izquierdo:` Sube por el árbol mientras el nodo actual sea un hijo izquierdo (**while (s->isLeftChild()) s = s->parent;**). Al salir del bucle (cuando encuentra un nodo que es hijo derecho de su padre), el predecesor final es ese padre (**s->parent**).

7. En `BinTree`, ¿qué papel cumplen `root_` y `size_`?

  - `root_:` Es un puntero al nodo raíz del árbol (`BinNode<T>*`). Es el único punto de entrada para cualquier operación de recorrido, búsqueda, inserción o destrucción. Si es **nullptr**, el árbol está vacío.
  
  - `size_:` Es un contador entero de tipo **std::size_t** que mantiene el número actual de nodos en el árbol. Permite que la función **empty()** y el método **size()** de la clase **BinTree** respondan en tiempo constante O(1) en lugar de tener que recorrer todo el árbol para contarlos.

8. Explica qué hace `updateHeight(Node*)`.

 Calcula y actualiza la propiedad **height** (altura) de un nodo específico basándose en la altura de sus hijos directos. La altura de un nodo es la distancia más larga hacia una hoja.
 
  - Utiliza la función auxiliar **stature()**, que devuelve **-1** si el hijo es **nullptr**.
  - Aplica la fórmula: height = 1 + max(altura izquierda,altura derecha)$.
  - Almacena este valor en **node->height** y lo retorna.

9. Explica qué hace `updateHeightAbove(Node*)` y por qué sube hacia la raíz.

 Este método recibe un nodo y ejecuta un bucle **while (node != nullptr)** que llama a **updateHeight(node)** y luego avanza a **node = node->parent**.

 `Por qué sube hacia la raíz:` Al insertar, eliminar o modificar un nodo, la altura de ese subárbol específico puede cambiar. Este cambio potencialmente altera la altura de su padre, la del abuelo, y así sucesivamente hacia arriba. Sube por la cadena de ancestros recalculando las alturas para garantizar que la propiedad **height** de todos los nodos afectados se mantenga matemáticamente correcta hasta llegar a la raíz.

10. Explica cómo `attachAsLC` o `attachAsRC` transfieren un subárbol desde un árbol hacia otro.

 Supongamos **attachAsLC(parent, subtree)**:

   1. Valida que el **parent** no sea nulo y que no tenga ya un hijo izquierdo.
   2. Extrae la raíz del árbol secundario y la conecta: **parent->left = subtree.root_**.
   3. Establece el puntero hacia arriba: **subtree.root_->parent = parent**.
   4. Absorbe el tamaño: **size_ += subtree.size_**.
   5. Actualiza las alturas del árbol principal desde **parent** hacia arriba (**updateHeightAbove(parent)**).
   6. Desconexión segura: Para evitar que el objeto **subtree** intente borrar estos nodos cuando sea destruido (salga de alcance), se limpian sus variables internas: **subtree.root_ = nullptr**; y **subtree.size_ = 0;**. El subárbol ha cambiado de dueño completamente.

11. Explica qué diferencia hay entre `removeSubtree` y `secede`.

  - `removeSubtree(node):` Desconecta el nodo seleccionado de su padre y elimina físicamente de la memoria (usando **delete**) toda la estructura de nodos que cuelga de él. Reduce el **size_** del árbol original según la cantidad de nodos destruidos.

  - `secede(node):` Desconecta el nodo de su padre pero no destruye nada. En su lugar, empaqueta ese nodo y todo su subárbol dentro de una nueva instancia de **BinTree<T>** independiente que es devuelta por la función. El árbol original reduce su **size_**, pero los nodos siguen vivos en el nuevo árbol.

12. Explica por qué `secede` no debe destruir los nodos desprendidos.

 Porque el propósito de **secede** es la escisión o separación, no la eliminación. Su objetivo es aislar una rama para que el usuario pueda seguir utilizándola como un árbol binario completamente nuevo y válido. Si destruyera los nodos, la función devolvería un árbol roto lleno de punteros colgantes (dangling pointers).

13. Explica por qué `removeSubtree` sí debe liberar nodos.

 Porque el propósito de este método es la eliminación definitiva. En C++, la memoria dinámica asignada con **new** no se libera sola. Si **removeSubtree** simplemente desconectara los nodos sin llamar a la función destructora recursiva **destroy(node)**, esos bloques de memoria se quedarían permanentemente bloqueados en el sistema sin que nadie pueda acceder a ellos ni reutilizarlos.

14. Explica qué verifica `checkParentLinks()`.

 Es una función de aserción para depuración. Recorre recursivamente todo el árbol verificando que para cada nodo **N**, el puntero **N->left->parent** (si existe) y **N->right->parent** (si existe) apunten de vuelta exactamente a **N**. También verifica que la raíz del árbol tenga **parent == nullptr**. Retorna **true** si todas las relaciones de parentesco son bilaterales y correctas, o **false** si el árbol sufre de corrupción de punteros.

15. En `BinaryTree`, explica cómo se implementan `firstNode`, `lastNode`, `nextNode` y `prevNode`.

 - `firstNode():` Retorna el primer nodo del recorrido inorden. Si el árbol no está vacío, invoca de manera directa a **root_->leftmost()**.

 - `lastNode():` Retorna el último nodo del recorrido inorden. Invoca a **root_->rightmost()**.

 - `nextNode(node):` Retorna el sucesor inorden llamando internamente a **node->succ()**.

 - `prevNode(node):` Retorna el predecesor inorden llamando internamente a **node->pred()**.

16. Explica por qué un iterador basado en `succ()` produce recorrido inorden.

 Por definición matemática, el recorrido inorden visita un árbol en la secuencia: Subárbol Izquierdo -> Raíz-> Subárbol Derecho.
 La función **succ()** está diseñada específicamente para calcular cuál es el "siguiente" nodo respetando estrictamente esta secuencia. Al inicializar el iterador en **firstNode()** (**leftmost()**) y hacer que el operador de incremento (**operator++**) avance asignando **current_ = current_->succ()**, el iterador se ve forzado a visitar los nodos en el orden exacto de la secuencia inorden.

17. Explica qué aporta `asciiArt()` para depuración y sustentación.

 El método **asciiArt()** genera una representación visual en formato de texto plano (utilizando caracteres como **├──**, **└──**, **│**) que muestra la estructura jerárquica del árbol rotada 90 grados.

   - `Para depuración (Debugging):` Permite al desarrollador ver de un solo vistazo la forma real del árbol en la consola tras realizar inserciones, rotaciones o eliminaciones. Es infinitamente más rápido detectar un hijo mal colocado viendo el dibujo que inspeccionando punteros en un depurador línea por línea.

    - `Para sustentación:` Sirve para demostrar de forma empírica y didáctica el comportamiento del árbol ante un evaluador o usuario. Se puede imprimir el estado del árbol antes y después de una operación compleja para validar visualmente que las reglas de la estructura de datos se cumplen.

#### Bloque 7 - Árbol binario de búsqueda: búsqueda, eliminación y rotaciones

1. Define formalmente la propiedad BST.

 Para cualquier nodo $u$ en un Árbol Binario de Búsqueda (BST):
 - Si v es un nodo en el subárbol izquierdo de u, entonces v.data<=u.data(o v.data < u.data si no se permiten duplicados).
 - Si v es un nodo en el subárbol derecho de u, entonces v.data=>u.data(o v.data > u.data si no se permiten duplicados).

2. Explica por qué el recorrido inorden de un BST debe producir una secuencia no decreciente.

 El recorrido inorden sigue el patrón: Izquierda -> Raíz -> Derecha.
 Por la propiedad BST, todos los elementos a la izquierda son menores que la raíz, y todos los de la derecha son mayores. Al aplicar esta definición de manera recursiva, garantizamos que ningún elemento procesado más tarde sea menor que uno procesado tempranamente, resultando estrictamente en una secuencia no decreciente (ordenada).

3. Explica la diferencia entre `find`, `findEQ`, `lowerBound` y `upperBound`.

 - `findEQ(x):` Busca una coincidencia exacta. Si no existe un nodo con valor idéntico a **x**, devuelve **nullptr**.
 - `lowerBound(x):` Busca el primer elemento que sea mayor o igual a **x** (=>x).
 - `upperBound(x):` Busca el primer elemento que sea estrictamente mayor que **x** (> x).
 - `find(x):` En tu implementación, está mapeado directamente para comportarse igual que **lowerBound(x)**.

4. Explica por qué `findEQ(x)` puede fallar aunque `lowerBound(x)` no falle.

 Si buscas un valor **x** que no existe en el árbol, pero sí existen valores mayores a él:

   - **findEQ(x)** recorrerá el árbol hasta chocar con un **nullptr** y devolverá **nullptr** (falla).

   - **lowerBound(x)** guardará el último nodo donde giró a la izquierda (el ancestro más cercano que es mayor que x) en la variable **candidate** y lo devolverá con éxito.

5. Construye manualmente el BST que se obtiene al insertar: `7, 3, 10, 1, 5, 8, 12, 4, 6`.

 Insertando secuencialmente: 7, 3, 10, 1, 5, 8, 12, 4, 6

         7
        / \
       3   10
      / \  / \
     1   5 8  12
        / \
       4   6

6. Escribe el inorden, preorden, postorden y recorrido por niveles de ese árbol.

 - Inorden: **1, 3, 4, 5, 6, 7, 8, 10, 12** (Siempre ordenado de menor a mayor).

 - Preorden: **7, 3, 1, 5, 4, 6, 10, 8, 12** (Raíz, Izquierda, Derecha).

 - Postorden: **1, 4, 6, 5, 3, 8, 12, 10, 7** (Izquierda, Derecha, Raíz).

 - Por niveles: **7, 3, 10, 1, 5, 8, 12, 4, 6** (Lectura horizontal por capas).

7. Simula `lowerBound(9)` y `upperBound(8)` paso a paso.

 `Simulación de` **lowerBound(9)**
 - Inicio en raíz **7**. Como 9 > 7, vamos a la derecha. **candidate = nullptr**.
 - Nodo actual **10**. Como 9 < 10, guardamos **candidate = 10** y vamos a la izquierda.
 - Nodo actual **8**. Como 9 > 8, vamos a la derecha.
 - Llegamos a **nullptr**. Finaliza el ciclo.
 - Resultado: Devuelve **candidate** que es **10**.
 
 `Simulación de` **upperBound(8)**
 - Inicio en raíz **7**. Como 8 > 7, vamos a la derecha.
 - Nodo actual **10**. Como 8 < 10, guardamos **candidate = 10** y vamos a la izquierda.
 - Nodo actual **8**. Al evaluar **comp_(8, 8)** da falso, entra al **else** y vamos a la derecha.
 - Llegamos a **nullptr**. Finaliza el ciclo.
 - Resultado: Devuelve **candidate** que es **10**.

8. Explica qué casos de eliminación existen en un BST: hoja, un hijo, dos hijos.

 - Nodo Hoja: No tiene hijos. Se desconecta de su padre y se elimina directamente.

 - Nodo con un solo hijo: Se puentea al hijo directamente con el padre del nodo a eliminar.

 - Nodo con dos hijos: No se puede eliminar su posición física directamente. Se busca su sucesor inorden (el nodo más a la izquierda de su subárbol derecho). Se copia el valor del sucesor en el nodo original, y luego se elimina físicamente el sucesor (el cual garantizadamente cae en el caso de "hoja" o "un solo hijo").

9. Explica qué papel cumple `splice` durante una eliminación.

 **splice(node)** es la función encargada de realizar la desconexión física de un nodo que tiene como máximo un hijo. Conecta directamente al único hijo vivo (o **nullptr**) con el padre del nodo que se va a eliminar, reestructurando los punteros y actualizando las alturas correspondientes mediante **updateHeightAbove**.

10. Después de eliminar una clave, ¿qué invariantes deben seguir siendo ciertos?

 Tras un **remove**, se deben preservar tres cosas:

   1. Propiedad BST: El orden relativo de todos los nodos remanentes debe seguir intacto.

   2. Integridad de enlaces: Los punteros **left**, **right** y **parent** deben apuntar correctamente a sus nuevos familiares directos.

   3. Consistencia de metadata: El tamaño (**size_**) debe disminuir en 1 y las alturas (**height**) de los ancestros afectados deben recalcularse.

11. Explica por qué `remove(3)` en las pruebas debe conservar el inorden ordenado.

 El nodo 3 tiene dos hijos (1 y 5). El algoritmo busca su sucesor inorden, que es 4. Copia el valor 4 a la posición donde estaba el 3, y luego hace un splice del nodo 4 original. El árbol resultante mantiene la propiedad BST de manera perfecta:

         7
        / \
       4   10
      / \  / \
     1   5 8  12
          \
           6

12. Explica qué hace `rotateLeft`.

 Realiza una rotación hacia la izquierda sobre el nodo u. El hijo derecho de u (llamémoslo w) pasa a ocupar la posición de u, u se convierte en el hijo izquierdo de w, y el antiguo subárbol izquierdo de w se transfiere para convertirse en el nuevo subárbol derecho de u.

13. Explica qué hace `rotateRight`.

 Realiza una rotación hacia la derecha sobre el nodo u. El hijo izquierdo de u (w) sube a tomar el lugar de u, u baja a ser el hijo derecho de w, y el antiguo subárbol derecho de w pasa a ser el nuevo subárbol izquierdo de u.

14. Demuestra que una rotación local preserva la propiedad BST.

 Tomemos una estructura genérica para **rotateLeft(A)**:
 - `Antes:` El nodo A tiene un hijo derecho B. Los subárboles son Tsub1 (izq de A), Tsub2 (izq de B), y Tsub3 (der de B).
 - `Orden inicial:` Tsub1 < A < Tsub2 < B < Tsub3.
 - `Después de rotateLeft(A):` B es la raíz, su hijo izquierdo es A. Los subárboles quedan: Tsub1 (izq de A), Tsub2 (der de A), y Tsub3 (der de B).
 - `Nuevo orden:` Tsub1 < A < Tsub2 (se cumple para A) y todo eso es menor que B, que a su vez es menor que Tsub3 (se cumple para B).
 - `Conclusión:` El orden lógico Tsub1 < A < Tsub2 < B < Tsub3 no varió en absoluto.

15. Explica para qué sirve construir un BST balanceado desde un arreglo ordenado.

 Construir un árbol desde un vector ordenado dividiendo recursivamente por la mitad (**mid**) asegura que el árbol resultante tenga la mínima altura posible (O(log n)). Esto previene que el árbol sufra el peor caso de degradación si los elementos se hubieran insertado uno por uno en orden secuencial.

16. Compara el costo de búsqueda en un BST balanceado y en un BST degenerado.

 | Operacion/Caso | BST Perfectamente Balanceado | BST Degenerado(Lista Enlazada) |
 | :--- | :--- | :--- | 
 | Altura estructural (h) | O(logn) | O(n) | 
 | Búsqueda (Peor Caso) | O(log n) | O(n) |
 | Inserción (Peor Caso) | O(log n) | O(n) |
 | Eliminación (Peor Caso) | O(log n) | O(n) |

#### Bloque 8 - Heap binario y representación implícita

1. Explica por qué un heap binario puede almacenarse en un `std::vector` sin punteros.

 Un heap binario es un árbol binario completo (todos los niveles llenos excepto posiblemente el último, que se llena de izquierda a derecha). Esta estructura regular permite mapear el árbol a posiciones secuenciales en un vector:

 Nivel 0: índice 0 (1 elemento)
 Nivel 1: índices 1-2 (2 elementos)
 Nivel 2: índices 3-6 (4 elementos)
 Nivel k: índices 2^(k) −1 a 2^(k+1) −2

 Al no haber espacios, se elimina la necesidad de punteros explícitos. Las posiciones se determinan mediante cálculos aritméticos, no referencias.

2. Demuestra las fórmulas:

 Dado un nodo en posición i:

 `Left child en posición 2i+1:`
 - El nodo en posición i tiene i nodos antes de él
 - Cada uno tiene 2 hijos, más los de niveles anteriores
 - Nivel de i:[logsub2(i+1)]
 - Total de nodos en niveles completos anteriores: 2^(k)-1
 donde k=[logsub2(i+1)]
 - Posicion del primer hijo del nodo en posicion i resulta en 2i +1 
 
 `Right child en posición 2i+2:`
 - Simplemente el siguiente después del hijo izquierdo:2i+1+1=2i+2
 
 `Parent en posición (i−1)/2:`
 - Si i es hijo izquierdo: i=2p+1, entonces p=(i−1)/2 
 - Si i es hijo derecho: i=2p+2, entonces p=(i−2)/2=(i−1)/2 (división entera) 
 
3. Define la propiedad de min-heap.

 Un min-heap satisface: para cada nodo, su valor es ≤ al de sus hijos.

 Formalmente: data[i]≤data[left(i)] y data[i]≤data[right(i)] para todo i.

 En `BinaryHeap.h`, la función **isHeap()** verifica esto comparando cada nodo con sus hijos.

4. Explica por qué `top()` devuelve el mínimo.

 Porque en un min-heap válido:

 - Cada padre es ≤ sus hijos (propiedad min-heap)
 - La raíz (índice 0) es el único nodo sin padre
 - Por transitoriedad, la raíz es ≤ cualquier otro nodo

5. Explica paso a paso cómo `bubbleUp(i)` restaura la propiedad de heap después de insertar.
 
 ```C++
 bubbleUp(i):
  mientras i > 0:
    p = parent(i)
    si data[i] >= data[p]:  // relación restaurada
      break
    intercambiar data[i] y data[p]
    i = p
 ```
 Paso a paso con inserción de 0 en **{1,3,2,7,5,8,10}**:
 1. Insertar 0 al final -> **{1,3,2,7,5,8,10,0}**
 2. **bubbleUp(7)**: i=7, p=3, data[7]=0 < data[3]=7 → intercambiar
     - Resultado: **{1,3,2,0,5,8,10,7}**, i=3
 3. **bubbleUp(3)**: i=3, p=1, data[3]=0 < data[1]=3 → intercambiar
     - Resultado: **{1,0,2,3,5,8,10,7}**, i=1
 4. **bubbleUp(1)**: i=1, p=0, data[1]=0 < data[0]=1 → intercambiar
     - Resultado: **{0,1,2,3,5,8,10,7}**, i=0
 5. i=0: bucle termina

 **Invariante**: Cada paso mueve el nuevo elemento hacia la raíz hasta restaurar la propiedad
 
6. Explica paso a paso cómo `trickleDown(i)` restaura la propiedad de heap después de eliminar la raíz.

 ```C++
 trickleDown(i):
  mientras true:
    best = i
    l = left(i), r = right(i)
    si l existe y comp(data[l], data[best]):
      best = l
    si r existe y comp(data[r], data[best]):
      best = r
    si best == i:
      break  // propiedad restaurada
    intercambiar data[i] y data[best]
    i = best
 ```
 Paso a paso: Eliminar raíz de **{1,3,2,7,5,8,10}**, mover 10 a raíz -> **{10,3,2,7,5,8}**:

   1. **trickleDown(0)**: i=0, best=0
     - l=1: comp(3, 10)=true -> best=1
     - r=2: comp(2, 3)=true -> best=2
     - best≠i: intercambiar 10↔2 -> **{2,3,10,7,5,8}**, i=2

   2. **trickleDown(2)**: i=2, best=2
     - l=5: comp(8, 10)=true -> best=5
     - r=6: no existe
     - best≠i: intercambiar 10↔8 → {2,3,8,7,5,10}, i=5
   
   3. trickleDown(5): i=5, best=5
     - l=11: no existe
     - Termina 

7. Explica por qué `remove()` debe mover el último elemento a la raíz antes de aplicar `trickleDown(0)`.

 ```C++
 T out = data_.front();        // guardar raíz
 data_.front() = data_.back(); // mover último a raíz
 data_.pop_back();             // eliminar último
 if (!data_.empty()) {
   trickleDown(0);             // restaurar
 } 
 ```
 Razones:

 - **Eficiencia:** Eliminar de cualquier posición interna requeriría reorganización lineal. El último nodo es O(1).

 - **Mantiene estructura:** El árbol sigue siendo completo (todos los niveles llenos excepto el último, que se llena de izquierda a derecha).

 - **Parcialmente válido:** Mover el último viola potencialmente la propiedad solo en la raíz y su rama. **trickleDown** restaura eficientemente.

 Si se eliminara un nodo interno directamente, se crearían huecos y se destruiría la estructura de vector continuo.

8. Explica qué verifica `isHeap()`.

 ```C++
 for (int i = 0; i < size; ++i) {
  int l = left(i), r = right(i);
  if (l < size && comp(data[l], data[i]))
    return false;  // hijo izquierdo viola propiedad
  if (r < size && comp(data[r], data[i]))
    return false;  // hijo derecho viola propiedad
 }
 return true;
 ```
 Comprueba que ningún hijo es menor que su padre, asegurando la integridad de la estructura.

9. Compara construir un heap insertando `n` elementos con construirlo usando `heapify()`.

 | Aspecto | Inserccion individual | heapify() | 
 | :--- | :--- | :--- | 
 | Algoritmo | Agregar elemento, bubbleUp()	| Desordenar luego trickleDown() |
 | Complejidad | O(nlogn) peor caso	| O(n) siempre |
 | Usar cuando | Inserción incremental | Construcción de una sola vez |
 | Overhead	| Múltiples rebalanceos	| Un solo recorrido |
 
10. Justifica por qué insertar `n` elementos uno por uno cuesta `O(n log n)` en el peor caso.
 
 Cada inserción en el heap coloca el nuevo valor al final del vector y luego hace **bubbleUp**.

  - En el peor caso, el nuevo elemento sube desde la hoja hasta la raíz.
  - La altura del heap con n elementos es O(log n).
  - Por tanto, cada inserción puede costar hasta O(log n) comparaciones/intercambios.
 
 Si haces eso **n** veces:

   - operaciones totales = **n * O(log n)** = **O(n log n)**
 
 Otra forma de verlo:

  - El primer elemento no necesita subir.
  - El elemento **k** puede recorrer hasta la altura actual del heap, que es **O(log k)**.
  - La suma de alturas desde k=1 hasta n es aproximadamente:
          
          log 1 + log 2 + ... + log n = log(n!)
 
  Y por Stirling, **log(n!) = Θ(n log n)**.

  Así, insertar todos los elementos uno a uno lleva **Θ(n log n)** en el peor caso.

11. Justifica por qué `heapify()` puede ejecutarse en `O(n)`.

 ```C++
 for (int i = data_.size() / 2 - 1; i >= 0; --i) {
  trickleDown(i);
 }
 ```
 - **heapify()** no hace **bubbleUp** para cada elemento, sino que recorre los nodos internos desde el último padre hacia la raíz y aplica **trickleDown**.
 - Los nodos más cerca de las hojas son muchos, pero cada uno recorre muy poco: casi 0 niveles.
 - Los nodos cercanos a la raíz son pocos, y aunque cada uno pueda bajar más niveles, hay muy pocos de ellos.
 - El costo total se puede ver como:
     - muchos nodos con costo pequeño +
     - pocos nodos con costo grande.
 - Esa suma converge a una cantidad proporcional a **n**, no a **nlogn**.

 En otras palabras: **heapify()** aprovecha la estructura completa del árbol para equilibrar más trabajo en nodos baratos y menos trabajo en nodos caros, lo que da un costo total lineal **O(n)**.

12. Ejecuta una extracción completa del heap construido con `{7, 3, 10, 1, 5, 8, 2}` y explica por qué la secuencia extraída sale ordenada.

 Construcción inicial (heapify):

 Entrada: {7, 3, 10, 1, 5, 8, 2}
        
         7             ->  After trickleDown(2): 7 -> 8
        / \                                      / \
       3  10           ->  After trickleDown(1): 10 -> 3
      / \ /  \                                 / \
     1  5 8  2         ->  After trickleDown(0): 7 -> 1
    
 Heap válido: {1, 3, 2, 7, 5, 8, 10}

 Extracciones:
 | Paso | **remove** | heap despues | Operacion |  
 | :--- | :--- | :--- | :--- |
 | 1 | 1 | {2,3,10,7,5,8} | Mover 10 a raíz, trickleDown |
 | 2 | 2 | {3,7,8,10,5}	| Mover 8 a raíz, trickleDown |
 | 3 | 3 | {5,7,8,10} | Mover 10 a raíz, trickleDown | 
 | 4 | 5 | {7,10,8}	| Mover 8 a raíz, trickleDown |
 | 5 | 7 | {8,10} | Mover 10 a raíz, trickleDown | 
 | 6 | 8 | {10} | Único nodo |
 | 7 | 10 | {} | Vacio | 

 Secuencia extraída: {1, 2, 3, 5, 7, 8, 10}  ORDENADA
 
 ¿Por qué sale ordenada?

  - Cada **remove()** extrae el mínimo actual (propiedad min-heap)
  - El heap se revalida tras cada extracción
  - El mínimo de cada subconjunto restante sale secuencialmente
  - Esto es equivalente a HeapSort

13. Compara el heap con el BST: ¿cuál estructura conviene para consultar mínimo repetidamente y cuál conviene para búsquedas ordenadas?.

  - Para consultar el mínimo repetidamente, el heap es mejor porque la raíz siempre contiene el menor elemento y **top()** es **O(1)**.
  - Para búsquedas ordenadas o para recorrer todos los elementos en orden, el BST es mejor porque mantiene la relación de orden completa y su recorrido inorden produce la secuencia ordenada.
  - En resumen:
     - si necesitas extraer o mirar prioridades a menudo -> usa un heap,
     - si necesitas buscar valores específicos o generar un orden completo -> usa un BST.

#### Bloque 9 - Cierre comparativo y preparación de sustentación

 Al pasar de listas, pilas y colas a árboles binarios, heaps y BST cambia el enfoque de estructuras lineales a estructuras jerárquicas.

 - En árboles enlazados cada nodo guarda punteros a sus hijos y a veces a su padre, lo que permite navegar la forma del árbol sin usar índices.
 - En heaps y otras representaciones implícitas, el árbol se guarda en un arreglo contiguo y las relaciones padre/hijo se deducen por fórmulas como **2*i+1**, **2*i+2** y **(i-1)/2**.
 - La propiedad estructural es que el árbol sea completo o bien formado; la propiedad de orden es que los valores respeten una relación entre padres e hijos (por ejemplo, BST o min-heap).
 - Los recorridos convierten un árbol en una secuencia porque visitan nodos en un orden definido: preorden, inorden, postorden o por niveles generan listas lineales de valores.
 - Mantener alturas y enlaces **parent** es importante en árboles enlazados para calcular depth/height, actualizar subárboles y soportar operaciones como **succ()/pred()**.
 - En un BST, la propiedad de orden completa permite búsqueda ordenada y hace que el recorrido inorden produzca una secuencia ordenada de valores.
 - En un heap, la prioridad es lo importante: **add** y **remove** cuestan **O(log n)** en el peor caso porque restauran la propiedad de heap, mientras que **heapify** puede construirse en **O(n)** usando **trickleDown** desde los nodos internos.
 - Para defender correctitud, usaría evidencia combinada: pruebas públicas/internas, demos que muestran salidas esperadas, invariantes como **isBST()/isHeap()**, trazados manuales de operaciones y argumentos de complejidad.

### Autoevaluación breve
 
 - Qué puedo defender con seguridad:
     - La diferencia entre representación enlazada y representación implícita.
     - Por qué **BinaryHeap** usa **bubbleUp** y **trickleDown** y cómo mantienen la propiedad de heap.
     - Por qué el recorrido inorden en un BST produce una secuencia ordenada.
     - La complejidad de **add/remove** en heap y de **heapify()**.
 
 - Qué todavía confundo:
     - Detalles específicos de los tres métodos de inorden iterativo.
     - El comportamiento exacto de **splice** en la eliminación de un BST.
     - Cómo se actualizan las alturas en todos los casos de **BinTree**.

 - Qué evidencia usaría en una sustentación:
     - Resultados de **demo_heap.cpp** y **demo_bst.cpp**.
     - Pruebas públicas e internas (**test_public_week5.cpp** y **test_internal_week5.cpp**).
     - Invariantes **isBST()** e **isHeap()**.
     - Trazados manuales de **bubbleUp**, **trickleDown**, **remove()** y recorrido inorden.

 - Qué parte del código me parece más importante para revisar otra vez:

     - **Semana5/include/BinaryHeap.h** 
     - **Semana5/include/BinarySearchTree.h**
     - **Semana5/include/BinaryTree.h**
     - **Semana5/include/BinTree.h**