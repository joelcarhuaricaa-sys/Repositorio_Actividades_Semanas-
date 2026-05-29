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
  | Propiedad | Izquierda< nodo < derecha | Padre ≤ hijos (min-heap)
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
3. Explica el caso en que `succ()` sube por los ancestros hasta encontrar el primer giro hacia la izquierda.
4. Explica simétricamente cómo debe funcionar `pred()`.
5. Dibuja un árbol de al menos 7 nodos y marca el sucesor y predecesor inorden de tres nodos distintos.
6. Explica qué calcula `depth(u)` y por qué puede implementarse subiendo por `parent`.
7. Explica qué calcula `height(u)` y por qué suele implementarse bajando recursivamente por los hijos.
8. Explica qué calcula `subtreeSize(u)`.
9. Demuestra que para todo nodo `u` se cumple `depth(u) + height(u) <= height(T)`.
10. Indica la condición necesaria y suficiente para que se alcance la igualdad anterior.