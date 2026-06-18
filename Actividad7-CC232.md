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
 | grep "add_test" CMakeLists.txt | add_test(NAME semana7_public COMMAND sem7_test_public)
 add_test(NAME semana7_internal COMMAND sem7_test_internal) | Ninguno | Aparecen 2 suites de pruebas: una pública (semana7_public) y una interna (semana7_internal). | 
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









