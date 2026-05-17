### CC232 - Evaluacion Parcial 1 (Version C)
Nombre: Joel Gustavo Carhuarica Aguilar 

#### Pregunta 2 

`**a)Trace sumRec([2,4,6,8],4) mostrando llamadas y retornos.**`

  **Llamadas:**

  Paso 1: Llamada inicial
  sumRec(A, 4)
   → Como n=4 ≠ 0, ejecuta: return sumRec(A, 3) + A[3]
   → A[3] = 8
   → Se detiene aquí, necesita el valor de sumRec(A, 3)

  Paso 2: 
  sumRec(A, 3)
   → n=3 ≠ 0, ejecuta: return sumRec(A, 2) + A[2]
   → A[2] = 6
   → Necesita sumRec(A, 2)

  Paso 3:
  sumRec(A, 2)
   → n=2 ≠ 0, ejecuta: return sumRec(A, 1) + A[1]
   → A[1] = 4
   → Necesita sumRec(A, 1)

  Paso 4:
  sumRec(A, 1)
   → n=1 ≠ 0, ejecuta: return sumRec(A, 0) + A[0]
   → A[0] = 2
   → Necesita sumRec(A, 0)

  Paso 5:
  sumRec(A, 0)
   → n=0, ejecuta: return 0
   → Este es el caso base, ya no llama más

  **Retornos:**

  Paso 5 (retorno): sumRec(A, 0) = 0

  Paso 4 (retorna a paso 3):
  sumRec(A, 1) = sumRec(A, 0) + A[0] = 0 + 2 = 2

  Paso 3 (retorna a paso 2):
  sumRec(A, 2) = sumRec(A, 1) + A[1] = 2 + 4 = 6

  Paso 2 (retorna a paso 1):
  sumRec(A, 3) = sumRec(A, 2) + A[2] = 6 + 6 = 12

  Paso 1 (retorna al llamador original):
  sumRec(A, 4) = sumRec(A, 3) + A[3] = 12 + 8 = 20

  Mostrandonos el Resultado final = **20**

`**b) Pruebe correctitud por induccion sobre n.**`

  Lo que queremos probar: sumRec(A, n) = A[0] + A[1] + ... + A[n-1].

  Caso base n = 0:La función retorna 0. Una suma vacía vale 0.
  
  Hipótesis inductiva:Supongamos que para algún k ≥ 0, la 
  función es correcta:

  sumRec(A, k) = A[0] + A[1] + ... + A[k-1]

  Paso inductivo n = k+1:Por el código, línea 3:

  sumRec(A, k+1) = sumRec(A, k) + A[k]

  Aplicando la hipótesis inductiva:

  = (A[0] + A[1] + ... + A[k-1]) + A[k]

  = A[0] + A[1] + ... + A[k]

  Que es exactamente la suma de los primeros k+1 elementos.

  Por inducción, la función es correcta para todo **n ≥ 0.**

`**c) Analice tiempo y espacio adicional. Distinga memoria del arreglo y pila de llamadas.**`
  
  Cada llamada aca hace O(1) trabajo(una suma,una comparacion). La funcion se llama **n+1** veces(desde **n** hasta **0**).

         T(n) = T(n-1) + O(1)  →  T(n) = O(n)
  Espacio ,hay que distinguir dos cosas:
  | Tipo de memoria | Tamaño | Explicacion | 
  | :--- | :--- | :--- |
  | Memoria del arreglo **A[]** | O(n) | El arreglo ya existía antes, la función no lo crea, solo lo recibe como puntero. No es espacio adicional de la función. |
  | Pila de llamadas (call stack) | O(n) | Cada llamada recursiva apila un frame con **{A, n, dirección de retorno}**. Se apilan **n+1** frames simultáneamente antes de empezar a retornar. Este sí es espacio adicional. |

 Observacion: La distinción es importante: la función usa O(1) espacio propio por frame, pero O(n) espacio adicional total por la profundidad de la recursión.

`**d) Escriba una version iterativa equivalente y proponga una invariante del ciclo.**`

  Acordanonos lo que avanzamos en la semana 1 del archivo **sum.cpp**

 Version iterativa: 

  int sumIter(const int A[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++)
        s += A[i];
    return s;
  }

  **El Invariante del ciclo:**
  Al inicio de cada iteración con valor i:

  s = A[0] + A[1] + ... + A[i-1]

  Verificacion:

  - Inicio (i=0): s = 0, suma vacía. 
  - Mantenimiento: si al inicio de la iteración i se cumple s = A[0]+...+A[i-1], entonces tras ejecutar s += A[i], al inicio de la iteración i+1 tenemos s = A[0]+...+A[i]. 
  - Terminación (i=n): el ciclo termina, y por la invariante s = A[0]+...+A[n-1], que es el resultado correcto. 
  
  Observacion: Ventaja de la versión iterativa: usa O(1) de espacio adicional (solo la variable s e i), sin pila de llamadas.

`e) ¿Por qué const int A[] comunica una intención útil para correctitud?`

  Porque el calificador const le dice al compilador y al lector que la función se compromete a no modificar el arreglo. Esto es útil por tres razones:

  1. Garantía formal: el compilador rechazará cualquier línea dentro de la función que intente escribir en A[i]. Así se detectan bugs accidentales en tiempo de compilación, no en ejecución.
  2. Razonamiento más simple: al probar correctitud (como en el inciso b), podemos asumir que A no cambia entre llamadas recursivas. Sin const, tendríamos que verificar además que ninguna llamada altera el arreglo.
  3. Composabilidad: permite pasar arreglos declarados como const sin errores de tipo, haciendo la función más reutilizable.

`**f) Indique dos casos borde y como deberian probarse.**`

  Caso borde 1 —> arreglo vacío (n = 0):
  
  int A[] = {}; //....(1)

  assert(sumRec(A, 0) == 0); //....(2)

  Por qué es borde: es el caso base de la recursión. Si falla aquí, toda la inducción colapsa. Se espera retorno 0.

  Caso borde 2 —> arreglo con un solo elemento (n = 1):

  int A[] = {42}; //.....(1)

  assert(sumRec(A, 1) == 42); //....(2)

  Por qué es borde: es el primer paso inductivo real. La llamada hace sumRec(A,0) + A[0] = 0 + 42 = 42. Verifica que el caso base y el paso recursivo interactúan correctamente.

#### Pregunta 3
 
`**a) Para r=5, dibuje los bloques y ubique los indices logicos 0 a 14. **` 
   
   Bueno recordando la semana 2 que vimos RootishArrayStack.
   
   capacidad total = 1+2+3+4+5 = r(r+1)/2 = 5×6/2 = 15 (índices 0 a 14)

   r=0 o Bloque 0 (tamaño 1): [ 0 ]

   r=1 o Bloque 1 (tamaño 2): [ 1 | 2 ]
   
   r=2 o Bloque 2 (tamaño 3): [ 3 | 4 | 5 ]
   
   r=3 o Bloque 3 (tamaño 4): [ 6 | 7 | 8 | 9 ]
   
   r=4 o Bloque 4 (tamaño 5): [ 10 | 11 | 12 | 13 | 14 ]

`**b) Para los indices i=0,1,2,5,9,14, indique el bloque y el desplazamiento dentro del bloque.**`

  La fórmula central es **i2b(i)** que resuelve **b(b+1)/2 ≤ i**:
  
  b = ceil( (-3 + sqrt(9 + 8i)) / 2 )
  
  j = i - b*(b+1)/2
 
  | indice i | calculo de b | b(bloque) | j=i-b(b+1)/2 | resultado | 
  | :--- | :--- | :--- | :--- | :--- |
  | 0 | ceil((-3+√9)/2) = ceil(0) = 0 | bloque 0 | 0-0=0 | b=0,j=0 |
  | 1 | ceil((-3+√17)/2) = ceil(0.56) = 1 | bloque 1 | 1 − 1 = 0 | b=1, j=0 |
  | 2 | ceil((-3+√25)/2) = ceil(1.0) = 1 | bloque 1 | 2 − 1 = 1 | b=1, j=1 |
  | 5 | ceil((-3+√49)/2) = ceil(2.0) = 2 | bloque 2 | 5 − 3 = 2 | b=2, j=2 |
  | 9 | ceil((-3+√81)/2) = ceil(3.0) = 3 | bloque 3 | 9 − 6 = 3 | b=3, j=3 |
  | 14 | ceil((-3+√121)/2) = ceil(4.0) = 4 | bloque 4 | 14 − 10 = 4 | b=4, j=4 |

  una observacion es que los indices 0,5,9,14 son exactamente el último elemento del bloque (j = b), lo que explica que la fórmula da un valor exacto sin necesidad de ceil.
  
`**c) Explique por que se necesita una funcion i2b(i) o locate (i).**`
   
   A diferencia de **ArrayStack**, donde acceder al elemento **i** es simplemente **a[i]** en O(1) directo, en **RootishArrayStack** la memoria está repartida en bloques separados. No hay un único arreglo contiguo.

   **i2b(i)** es como un GPS, resuelve la pregunta: ¿en qué bloque está el índice lógico i, y en qué posición dentro de ese bloque? Sin esta función, sería imposible saber a qué puntero de blocks[] acceder ni con qué índice interno. 

`**d)Justifique por que el espacio desperdiciado es O(√n) cuando hay n elementos.**`

   Con r bloques, la capacidad total es r(r+1)/2. Si hay n elementos entonces r ≈ √(2n).

   El espacio desperdiciado es la diferencia entre la capacidad y los elementos reales:

       desperdicio = r(r+1)/2 − n ≤ r(r+1)/2 − (r−1)r/2 = r

   Como r ≈ √(2n), el desperdicio es a lo sumo O(r) = O(√n).

   Esto es la ventaja clave sobre ArrayStack: cuando ArrayStack hace resize(), puede desperdiciar hasta n/2 slots (O(n)). RootishArrayStack nunca desperdicia más de O(√n), porque los bloques crecen de a uno y son pequeños.

`**e)Compare el acceso por indice con ArrayStack.¿Que se conserva y que costo adicional aparece?.**`
   
   | Aspecto | ArrayStack | RootishArrayStack | 
   | :--- | :--- | :--- | 
   | Acceso get(i) | a[i] O(1) puro, un solo derreferenciamiento | blocks[b][j]  O(1) con costo aritmético: calcular b y j vía i2b() implica una raíz cuadrada y un ceil |
   | Lo que se conserva | O(1) asintotico | O(1) asintótico (igual de rápido en teoría) |
   | Costo adicional | Ninguno | Dos indirecciones: primero blocks[b], luego [j]; más las operaciones de sqrt y ceil en cada acceso |
   | Cache locality | Excelente (un arreglo contiguo) | Peor: los bloques están dispersos en memoria |

   En resumidas palabras:  el acceso sigue siendo O(1) pero con una constante mayor por la aritmética de i2b y la doble indirección.

`**f) Explique que ocurre cuando se necesita crecer o reducir el numero de bloques.**`

  Al crecer —> **grow()**:

   void grow() {
    blocks.add(blocks.size(), new T[blocks.size() + 1]);
   }

  Se agrega un nuevo bloque al final de blocks[]. Si había r bloques, el nuevo bloque tiene tamaño r+1. El costo es O(r) = O(√n) para alocar el nuevo arreglo, más O(1) amortizado para insertar el puntero en blocks[] (que es un ArrayStack y puede necesitar su propio resize()). No se copia ningún dato existente.

  Al encoger —> **shrink()**:

  void shrink() {
    int r = blocks.size();
    while (r > 0 && (r-2)*(r-1)/2 >= n) {
        delete[] blocks.remove(blocks.size()-1);
        r--;
    }
  }

  Se eliminan bloques del final mientras la capacidad con r-2 bloques sea suficiente para los n elementos actuales. Cada bloque eliminado libera su memoria con delete[]. La condición (r-2)(r-1)/2 >= n asegura que siempre queda capacidad suficiente.

  La diferencia crucial con ArrayStack::resize() es que aquí nunca se copian todos los elementos al crecer o encoger: solo se agrega o elimina un bloque. Eso hace que grow() sea O(√n) en vez de O(n).

#### Pregunta 4

front = [30, 20, 10]  y back  = [40, 50, 60, 70], su secuencia logia seria [10, 20, 30, 40, 50, 60, 70] —> índices 0 al 6.

`**a) Muestre como se calcula get(i) para i=0,2,3,6.**`

  get(i) para i = 0, 2, 3, 6
   
  Si recordamos en la semana 2 el DualArrayDeque
  La regla del código es:
  
  ```C++
  if (i < front.size())  →  front.get(front.size() - i - 1)
  else                   →  back.get(i - front.size())
  ```
  
  Con front.size() = 3:

  | i | ¿i<3? | Calculo | Resultado | 
  | :--- | :--- | :--- | :--- |
  | 0 | Si | front.get(3-0-1) = front[2] = 10 | 10 |
  | 2 | Si | front.get(3-2-1) = front[0] = 30 | 30 |
  | 3 | No | back.get(3-3) = back[0] = 40 | 40 |
  | 6 | No | back.get(6-3) = back[3] = 70 | 70 |

`**b) Ejecute add(1,15) y add (6,55) indicando en cual arreglo se inserta y como cambia la representacion**`
 
 add(1, 15) —> i=1 < front.size()=3, va a front:

 front.add(front.size() - i, x)  =  front.add(3-1, 15)  =  front.add(2, 15)

 **front**pasa de [30,20,10] a [30,20,15,10].
 Secuencia lógica: [10, 15, 20, 30, 40, 50, 60, 70] —> ahora n=8, front.size()=4.

 add(6, 55) —> sobre la nueva secuencia de 8 elementos, i=6 >= front.size()=4, va a back:
 
 back.add(i - front.size(), x)  =  back.add(6-4, 55)  =  back.add(2, 55)

 **back** pasa de [40,50,60,70] a [40,50,55,60,70].
 Secuencia lógica: [10, 15, 20, 30, 40, 50, 55, 60, 70].

`**c) Explique porque front guarda su contenido en orden inverso.**`

 Porque **front** representa el extremo izquierdo de la deque y se opera por su extremo derecho (que es el extremo más eficiente de un **ArrayStack**). Si guardáramos front en orden normal **[10, 20, 30]**, añadir al frente de la deque (índice 0) requeriría insertar al inicio del arreglo, desplazando todos los elementos — O(n). Al guardarlo invertido **[30, 20, 10]**, el elemento lógico **i=0** (que es **10**) está en **front[last]**, y agregar/quitar al frente de la deque equivale a un **push/pop** al final del **ArrayStack**, que es O(1) amortizado.

`**d) Defina una condicion razonable de balance entre front y back. Explique que debe hacer balance() cuando se viola.*`

 Una condición razonable es que ninguno de los dos arreglos tenga más de 3 veces el tamaño del otro:

 NO desbalanceado:

  front.size() ≤ 3 × back.size()
  
  back.size()  ≤ 3 × front.size()

 El código lo verifica como:
 
 Si nos vamos de nuevo al DualArrayDeque.h, nos fijamos que :

 ```C++
 if (3*front.size() < back.size() || 3*back.size() < front.size())
  ```
 Cuando se viola, **balance()** redistribuye todos los **n** elementos equitativamente:

 - Calcula **nf = n/2** (mitad para front) y nb = n - nf (resto para **back**).
 - Reconstruye **front** con los primeros **nf** elementos lógicos, en orden inverso.
 - Reconstruye **back** con los **nb** elementos restantes, en orden normal.
 - El costo es O(n) pero ocurre raramente.

`**e) Justifique que el rebalanceo puede mantener costos amortizados aceptables si no ocurre en cada operacion.**`

 **balance()** cuesta O(n), pero solo puede dispararse después de que se hayan hecho al menos n/3 operaciones desde el último balance. Para que un arreglo triplique al otro partiendo de un estado balanceado, necesitas insertar o eliminar por lo menos **n/3** veces del mismo lado. Eso significa que hay al menos **n/3** operaciones "baratas" que "pagan" el costo del rebalanceo.

 Formalmente: cada operación deposita crédito O(1). Cuando se acumulan suficientes créditos (al menos O(n) acumulados), se dispara el balance de costo O(n) exactamente cubierto. El resultado es O(1) amortizado por operación a pesar de que el rebalanceo individual sea O(n).

 Si **balance()** se llamara en cada operación, el costo sería O(n) por operación y todo se arruinaría. La condición **3×** garantiza que el rebalanceo sea infrecuente, preservando el costo amortizado.



 









