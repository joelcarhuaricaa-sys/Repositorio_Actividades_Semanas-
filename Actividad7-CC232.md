### Actividad 7 - CC232

#### Estudiante

- Nombre: Joel Gustavo Carhuarica Aguilar

#### Bloque 1 - Diagnóstico inicial de la Semana 7

1. ¿Qué targets de demostración aparecen para Semana 7?
 
 ```bash
 cc232_add_sem7_target(sem7_demo_avl_deng_core "demos/demo_avl_deng_core.cpp")
 cc232_add_sem7_target(sem7_demo_avl_compact_rotations "demos/demo_avl_compact_rotations.cpp")
 cc232_add_sem7_target(sem7_demo_bst_deng_vs_avl "demos/demo_bst_deng_vs_avl.cpp")
 cc232_add_sem7_target(sem7_demo_redblack_morin "demos/demo_redblack_morin.cpp")
 cc232_add_sem7_target(sem7_demo_redblack_llrb "demos/demo_redblack_llrb.cpp")
 cc232_add_sem7_target(sem7_demo_compare_avl_vs_redblack "demos/demo_compare_avl_vs_redblack.cpp")
 cc232_add_sem7_target(sem7_demo_compare_with_semana5 "demos/demo_compare_with_semana5.cpp")
 cc232_add_sem7_target(sem7_demo_capitulo7_panorama "demos/demo_capitulo7_panorama.cpp")
 ```

2. ¿Qué pruebas públicas e internas aparecen?
 
 ```bash
 add_test(NAME semana7_public COMMAND sem7_test_public)
 add_test(NAME semana7_internal COMMAND sem7_test_internal)
 ```

3. ¿Qué archivos incluye `Capitulo7.h`?

 ```bash
 #include "Entry.h"
 #include "BinNode.h"
 #include "BinTree.h"
 #include "BST.h"
 #include "AVL.h"
 #include "BinaryTree.h"
 #include "BinarySearchTree.h"
 #include "RedBlackTree.h"
 #include "AVLTreeCompact.h"
 #include "RedBlackTreeLLRB.h"
 ```

4. ¿Qué relación conceptual hay entre Semana 5, Semana 6 y Semana 7?
 
 Esta carpeta continúa el trabajo de `Semana5` y `Semana6` dentro de `Libreria_cc232`. El objetivo principal es estudiar cómo un árbol binario de búsqueda puede mantener altura logarítmica mediante rotaciones, reglas de balance y correcciones locales después de insertar o eliminar.

 La semana se organiza como una continuación natural de las semanas anteriores:

 * `Semana5` introduce la infraestructura de árboles binarios, recorridos, heaps y árboles binarios de búsqueda.
 * `Semana6` extiende esa base con colas de prioridad, heaps, Huffman, rotaciones y Treap como puente entre búsqueda ordenada y prioridad.
 * `Semana7` estudia árboles de búsqueda balanceados: **AVL** y **Red-Black Tree**.


5. ¿Por qué no es correcto decir que una carpeta "hereda" de otra carpeta?

 Porque la herencia es una propiedad de la Programación Orientada a Objetos (POO) que aplica estrictamente a clases y tipos de datos (relación "es-un"). Las carpetas son simplemente contenedores en el sistema de archivos; la relación entre la carpeta Semana7 y las anteriores es de continuidad del temario y reutilización de diseño/código, mas no de herencia sintáctica.

6. ¿Qué clases sí usan herencia dentro del código?

 Dentro del código de esta semana se estructuran dos cadenas principales de herencia:

    Línea Deng: AVL hereda públicamente de BST.

    Línea Morin: RedBlackTree hereda públicamente de BinarySearchTree.

7. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?.

 ```bash
 Test project /home/gustavo/CC-232-main/Libreria_cc232/Semana7/build-debug
    Start 1: semana7_public
 1/2 Test #1: semana7_public ...................   Passed    0.00 sec
    Start 2: semana7_internal
 2/2 Test #2: semana7_internal .................   Passed    0.01 sec

 100% tests passed, 0 tests failed out of 2

 Total Test time (real) =   0.02 sec
 ```

 | Comando Ejecutivo | Resultado de la Terminal(Salida) | Error | Interpretacion/ |
 | :--- | :--- | :--- | :--- |
 | grep "cc232_add_sem7_target(sem7_demo" CMakeLists.txt | Muestra 8 líneas con los nombres de los objetivos que empiezan con sem7_demo_.... | Ninguno | Existen exactamente 8 targets de demostración configurados para comparar AVL, BST y Red-Black Tree. | 
 | grep "add_test" CMakeLists.txt | add_test(NAME semana7_public COMMAND sem7_test_public)add_test(NAME semana7_internal COMMAND sem7_test_internal) | Ninguno | Aparecen 2 suites de pruebas: una pública (semana7_public) y una interna (semana7_internal). | 
 | cat include/Capitulo7.h grep "#include" | Devuelve una lista de 10 líneas de código con archivos .h (desde Entry.h hasta RedBlackTreeLLRB.h). | Ninguno | Capitulo7.h incluye 10 archivos de cabecera que componen las dos líneas pedagógicas del curso. | 
 | grep -A 8 "Semana5" README.md | Despliega un diagrama de texto (text) que conecta Semana 5 → Semana 6 → Semana 7. | Ninguno | La relación es una evolución del balanceo. S5 introduce BST (riesgo lineal), S6 introduce rotaciones locales (Treap) y S7 consolida el balance estricto (O(logn)) con AVL y Red-Black. | 
 | grep -A 5 "una carpeta no hereda" README.md | Muestra el fragmento de texto que aclara que las carpetas no heredan, sino las clases. | Ninguno | No se hereda entre carpetas porque la herencia es un concepto de POO para tipos de datos. Las carpetas solo organizan de forma continua y reutilizan código. | 
 | grep -r "public BinarySearchTree" include/ && grep -r "public BST" include/ | include/AVL.h: class AVL : public BST... include/RedBlackTree.h: class RedBlackTree : public BinarySearchTree... | Ninguno | Las clases que sí usan herencia real en el código son AVL (hereda de BST) y RedBlackTree (hereda de BinarySearchTree). | 
 | cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build-debug && ctest --test-dir build-debug --output-on-failure | Generación exitosa de archivos, compilación al 100% y salida de CTest: 100% tests passed, 0 tests failed out of 2. | Ninguno | Pregunta 7: La evidencia inicial demuestra que el código base está sano y pasa la totalidad de los tests preconfigurados sin necesidad de realizar modificaciones previas. | 

 Archivos revisados primero: 

 - CMakeLists.txt (Para identificar los nombres exactos de los targets y archivos fuente).

 - README.md (Para entender el contexto conceptual y las reglas de diseño).

 - include/Capitulo7.h (Para verificar las directivas #include directas).

#### Bloque 2 - BST como punto de partida

1. Define formalmente la propiedad BST.
 
   Un árbol binario de búsqueda cumple la siguiente propiedad:

 - Para cada nodo v, todo valor del subárbol izquierdo es menor que v.
 - Todo valor del subárbol derecho es mayor que v.
 - Además, cada subárbol también debe ser un BST.
  
  En forma formal, si L(v) y R(v) son los subárboles de v, entonces:

            ∀x∈L(v), x<v
            ∀x∈R(v), x>v
 
  y ambos subárboles cumplen la misma regla de forma recursiva.

2. Explica por qué el recorrido inorder de un BST produce una secuencia ordenada.

 El recorrido inorder visita en este orden:

     1. subárbol izquierdo,
     2. nodo actual,
     3. subárbol derecho.
 Como en un BST todos los elementos del izquierdo son menores que el nodo y todos los del derecho son mayores, al recorrer así se obtiene una secuencia creciente o bien ordenada de forma no decreciente.
 
3. Explica por qué insertar claves ordenadas puede producir un BST degenerado.

 Si se insertan claves ya ordenadas, por ejemplo:
  
       10, 20, 30, 40, 50, 60, 70

 cada nuevo valor es mayor que todos los anteriores, por lo que queda como hijo derecho del nodo anterior. Eso forma una cadena larga, es decir, un árbol muy sesgado o degenerado.

 Este caso es problemático porque deja al árbol casi como una lista enlazada.

4. Construye manualmente el BST resultante de insertar:

 ```cpp
 10, 20, 30, 40, 50, 60, 70
 ```
 El árbol queda así:

     10
     └── 20
          └── 30
              └── 40
                  └── 50
                      └── 60
                          └── 70

 
5. Indica la altura del árbol anterior si no hay balanceo.

 Si no hay balanceo, la altura es:

   -  6 si se cuenta en aristas,
   - 7 si se cuenta en nodos.
 
 En la convención más usada en estructuras de datos, la altura es 6.

6. Explica por qué una búsqueda en ese árbol puede costar `O(n)`.

 En un BST degenerado, una búsqueda puede recorrer todos los nodos de la cadena antes de encontrar el valor o determinar que no existe. Por eso, en el peor caso, la búsqueda toma tiempo lineal:
      
        O(n)

7. Explica qué problema intenta resolver AVL.

 AVL intenta resolver el problema de la pérdida de eficiencia en un BST cuando se desbalancea. Mantiene el árbol balanceado por altura, usando rotaciones para garantizar que la altura sea O(logn) y, por tanto, que búsqueda, inserción y eliminación sean eficientes en el peor caso.

8. Explica qué problema intenta resolver Red-Black Tree.

 Red-Black Tree también busca evitar el desbalanceo de un BST, pero lo hace con un criterio de balance más relajado basado en colores. Su objetivo es mantener operaciones eficientes, especialmente inserciones y eliminaciones, con menos reequilibrio que AVL, aunque con un balance un poco menos estricto.

 **Dibujo del BST degenerado**

 El dibujo ya está mostrado arriba: una cadena vertical de nodos hacia la derecha.

 **Explicación breve de costo**

 En este árbol degenerado, la búsqueda, inserción y eliminación pueden llegar a ser 
 O(n) porque el árbol deja de tener estructura “casi balanceada” y se comporta como una lista.

 **Relación con Semana 5**

 La Semana 5 introduce el BST como estructura básica de búsqueda ordenada. La Semana 7 amplía esa idea mostrando que un BST simple puede volverse ineficiente si se inserta en orden y que por eso aparecen estructuras como AVL y Red-Black Tree para conservar el orden y mantener eficiencia.

#### Bloque 3 - AVL: balance por altura

1. ¿Qué significa que un nodo esté balanceado en un AVL?
 
 Un nodo está balanceado si la diferencia entre las alturas de sus dos subárboles es como máximo 1. Es decir:
  
    ∣h(izq)−h(der)∣≤1
 
 Si esa condición se cumple para todos los nodos, el árbol está balanceado según AVL.
 
2. ¿Cómo se calcula el factor de balance?

 El factor de balance de un nodo v se calcula como:

      bf(v)=h(v.left)−h(v.right)

 En la implementación, se usa la altura del subárbol izquierdo menos la altura del derecho. Un valor de:

   -  -1,0 o 1 → nodo balanceado
   -  menor que -1 o mayor que 1 → nodo desbalanceado

3. ¿Qué información de altura debe mantenerse después de insertar o eliminar?

 Después de insertar o eliminar, el árbol debe actualizar la altura de cada nodo afectado. La altura de un nodo se define como:
  
     h(v)=1+max(h(v.left),h(v.right))

 La altura de un árbol vacío suele tomarse como −1 y la altura de una hoja como 0.

4. ¿Qué representa `_hot` dentro de la implementación estilo Deng?

 En la implementación estilo Deng, _hot es el “nodo caliente”: el último nodo visitado durante la búsqueda, que sirve como padre del nodo que se va a insertar o como punto de referencia para reacomodar la estructura después de una eliminación. En otras palabras, es el nodo que queda cerca del cambio realizado.

5. ¿Por qué AVL puede heredar de `BST<T, Compare>`?

 AVL puede heredar de BST<T, Compare> porque conserva la base del BST:

   - mantiene la propiedad de orden,
   - usa la misma búsqueda por comparación,
   - comparte la estructura de nodos y la lógica de inserción/eliminación básica.

 Lo que agrega AVL es una condición extra: mantener balance por altura. Por eso hereda la lógica del BST y la complementa con reequilibrio.

6. ¿Qué operación restaura localmente la forma del árbol?

 La operación que restaura la forma del árbol es la rotación. En la implementación se invoca rotateAt(...).
 Esta operación reestructura un subárbol pequeño alrededor de un nodo desbalanceado y recupera el equilibrio local.

7. ¿Por qué una rotación no destruye la propiedad BST?

 Una rotación no rompe la propiedad BST porque solo cambia la posición relativa de los nodos dentro de un subárbol pequeño, pero conserva el orden de los valores:

  - todos los elementos del subárbol izquierdo siguen siendo menores que el nodo raíz del subárbol,
  - todos los del derecho siguen siendo mayores,
  - y el inorder sigue siendo el mismo en términos de secuencia ordenada.
8. Después de insertar, ¿por qué suele bastar reparar el primer ancestro desbalanceado?

 Después de una inserción, solo los ancestros del nodo insertado pueden cambiar de altura. Si el primer ancestro desbalanceado se corrige con una rotación, el equilibrio del resto del camino queda restaurado en ese punto, porque la altura del subárbol reestructurado ya queda consistente. Por eso suele bastar con reparar el primer problema encontrado.

9. Después de eliminar, ¿por qué puede ser necesario seguir revisando hacia la raíz?.

 En una eliminación, la altura de un subárbol puede disminuir y ese cambio puede afectar varios ancestros. A diferencia de la inserción, donde un solo ajuste suele resolver el problema, en la eliminación el desbalance puede propagarse hacia arriba y requerir revisar varios nodos hasta llegar a la raíz o hasta encontrar un punto estable.

 **Invariantes AVL**
 
 Un AVL debe cumplir estas propiedades:
   - Mantiene la propiedad BST.
   - Cada nodo conserva su altura real.
   - El factor de balance de cada nodo está en {−1,0,1}.
   - La altura del árbol se mantiene en O(logn).
 
 **Trazado de inserción con rotación**

 Un ejemplo simple es insertar:

     30, 20, 10

   - Se inserta 30 como raíz.
   - Se inserta 20 como hijo izquierdo.
   - Se inserta 10 como hijo izquierdo de 20.

 Eso deja al nodo 30 desbalanceado hacia la izquierda. El AVL detecta ese desbalance y aplica una rotación simple de tipo LL:

 Antes:
       30
      /
     20
    /
   10

 Después:
       20
      /  \
     10   30

 Esta rotación restaura el equilibrio local sin romper el orden BST.

 **Evidencia de salida de la demostración**

 El programa en demo_avl_deng_core.cpp está diseñado para imprimir:
  
    AVL inorder: ...
    AVL level-order: ...
    Valido AVL: si
    Tras borrar 20 y 40: ...
    Valido AVL: si

 La idea central es que, tras las inserciones y borrados, el árbol siga siendo válido como AVL y como BST.

#### Bloque 4 - Rotaciones AVL: casos LL, RR, LR y RL


 Tabla de rotaciones

 | Caso	 | Secuencia insertada | Nodo desbalanceado | Rotación aplicada | Inorder antes | Inorder después | Altura final | 
 | :--- | :--- | :--- | 
 | LL	| 30, 20, 10 | 30 |	Rotación simple a la derecha | 10, 20, 30 | 10, 20, 30 |	1 |
 | RR	| 10, 20, 30 | 10 | Rotación simple a la izquierda | 10, 20, 30 | 10, 20, 30 | 1 |
 | LR | 30, 10, 20 | 30 | Rotación doble: izquierda luego derecha | 10, 20, 30 | 10, 20, 30 | 1 |
 |RL | 10, 30, 20| 10 | Rotación doble: derecha luego izquierda | 10, 20, 30 | 10, 20, 30 | 1 |

 Dibujos pequeños

 LL
  
      Antes:        Después:
        30            20
       /             /  \
      20            10   30
      /
      10

 RR

       Antes:        Después:
       10             20
        \            /  \
        20           10   30
         \
          30

 LR

       Antes:        Después:
       30             20
       /              /  \
       10             10   30
        \
        20

 RL

       Antes:        Después:
       10              20
        \             /  \
        30            10   30
        /
       20       

1. ¿Qué diferencia hay entre una rotación simple y una rotación doble?

 - Una rotación simple corrige el desequilibrio con un solo giro alrededor de un enlace.
 - Una rotación doble requiere dos rotaciones simples consecutivas para dejar el subárbol equilibrado.

2. ¿Por qué LL y RR se corrigen con una sola rotación?

 - En LL y RR el desbalanceo se presenta en la forma de una cadena sencilla hacia la izquierda o hacia la derecha.
 - Ese patrón se resuelve con una sola rotación: derecha para LL y izquierda para RR.

3. ¿Por qué LR y RL requieren dos pasos?

 - En LR y RL el nodo desbalanceado tiene un hijo que está desbalanceado en el sentido contrario.
 - Primero se corrige el hijo interno y luego el nodo padre, por eso necesitan dos rotaciones.

4. ¿Qué parte del árbol cambia y qué parte permanece igual?

 - Cambia la estructura local del subárbol afectado: raíz, hijo y nietos se reacomodan.
 - Permanece igual el conjunto de valores y, por tanto, el orden relativo de los elementos.

5. ¿Por qué el inorder debe ser el mismo antes y después de reestructurar?.

 - La rotación solo reestructura la forma del árbol, no cambia los valores ni su distribución relativa bajo la propiedad BST.
 - Por eso, el recorrido inorder sigue siendo la misma secuencia ordenada.

 **Argumento de preservación del orden BST**

 Una rotación no rompe la propiedad BST porque:

   - el subárbol izquierdo de la nueva raíz sigue teniendo valores menores,
   - el subárbol derecho sigue teniendo valores mayores,
   - y los subárboles que se reubican conservan sus respectivos intervalos de valores.

 En otras palabras, la rotación cambia la forma, pero no cambia el orden de los elementos. Por eso el inorder sigue siendo el mismo y el árbol sigue siendo un BST.

#### Bloque 5 - Red-Black Tree: balance por colores

1. ¿Qué propiedad BST mantiene Red-Black Tree?

  Red-Black Tree conserva la propiedad de un BST:

   - Todo nodo del subárbol izquierdo es menor que el nodo actual.
   - Todo nodo del subárbol derecho es mayor que el nodo actual.
   - Cada subárbol también es un BST.
 Es decir, el orden de búsqueda sigue siendo el mismo que en un árbol binario de búsqueda normal.

2. ¿Qué propiedades de color debe cumplir un Red-Black Tree?

 Un Red-Black Tree debe cumplir estas reglas de color:

 - La raíz es negra.
 - Todo nodo hoja (o nulo) es negro.
 - Un nodo rojo no puede tener hijo rojo.
 - Por lo tanto, no puede haber dos nodos rojos consecutivos.
 - Todos los caminos desde un nodo a sus hojas descendientes tienen la misma cantidad de nodos negros.

3. ¿Por qué la raíz debe terminar negra?

 La raíz debe ser negra para mantener la propiedad de equilibrio global y evitar que la altura negra se vea alterada desde la raíz. Además, esto simplifica la conservación de las propiedades de color al insertar o eliminar.

4. ¿Qué significa que no pueda haber dos nodos rojos consecutivos?

 Significa que no puede haber un padre y un hijo ambos rojos.
 En otras palabras, entre dos nodos rojos no puede haber una relación directa de padre-hijo.

 Esto evita que el árbol se vuelva demasiado “ancho” en términos de profundidad relativa y ayuda a mantener el balance.

5. ¿Qué representa la altura negra?

 La altura negra es el número de nodos negros que se recorren en cualquier camino desde un nodo hasta una hoja externa (nula), contando el nodo inicial o no según la convención usada.
 La idea importante es que todos esos caminos deben tener la misma cantidad de nodos negros.

6. ¿Por qué Red-Black Tree permite un balance menos estricto que AVL?

 AVL exige que el factor de balance sea muy estricto, es decir:
 
     ∣h(left)−h(right)∣≤1

 Red-Black Tree, en cambio, usa colores y la altura negra como criterio. Eso da un balance más relajado, pero suficiente para garantizar que la altura sea O(logn).

7. ¿Qué correcciones pueden aparecer después de insertar?

 Después de insertar, pueden aparecer:
 
 - recoloreos,
 - rotaciones simples,
 - rotaciones dobles.

 En la implementación, el ajuste suele hacerse con addFixup, que corrige violaciones de color y estructura.

8. ¿Qué correcciones pueden aparecer después de eliminar?

 Después de eliminar, pueden aparecer:

 - recoloreos,
 - rotaciones,
 - reequilibrio por casos especiales de la eliminación.

 En la implementación, removeFixup se encarga de restaurar las propiedades cuando la eliminación deja un desequilibrio de color o de altura negra.

9. ¿Qué papel cumplen las rotaciones en Red-Black Tree?

 Las rotaciones sirven para reestructurar el árbol manteniendo la propiedad BST y redistribuyendo subárboles para restaurar las propiedades de color y balance.
 No cambian el orden de los elementos; solo cambian la forma del árbol.

10. ¿Qué papel cumple el cambio de colores?.
 
 El cambio de colores ayuda a preservar las propiedades sin necesidad de reestructurar siempre.
 Por ejemplo, cambiar un nodo a negro o rojo puede corregir una violación local de “rojo-rojo” o de altura negra.

 **Lista de invariantes Red-Black**

 Un Red-Black Tree debe mantener:
 
 - Propiedad BST.
 - La raíz es negra.
 - Los nodos hojas nulas son negras.
 - No hay dos rojos consecutivos.
 - Todos los caminos desde un nodo a una hoja tienen la misma altura negra.

 **Explicación de una inserción que requiera recoloreo**

 En una inserción, el nodo nuevo suele comenzar en rojo.
 Si su padre también es rojo, aparece una violación de “rojo-rojo”. Entonces el árbol puede corregirse con:

 - cambio de colores en el abuelo y en sus hijos,
 - o una rotación si el patrón lo requiere.
 
 Por ejemplo, si el padre es rojo y el tío también es rojo, se recolorean los nodos del caso para restaurar la propiedad. Si el patrón es más complejo, se combina con una rotación.

 **Evidencia de salida de la demostración**

  En demo_redblack_morin.cpp se imprime:

     RB inorder: ...
     Valido RedBlack: si
     Tras borrar 18 y 11: ...
     Valido RedBlack: si

 Eso muestra que, tras las inserciones y eliminaciones, el árbol sigue siendo válido y conserva el recorrido inorder ordenado.



