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




