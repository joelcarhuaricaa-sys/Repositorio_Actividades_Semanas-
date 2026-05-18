### CC232 - Evaluacion Parcial 1 (Version C)
Nombre: Joel Gustavo Carhuarica Aguilar 

#### Pregunta 1

**`a) Distinga ADT, representacion e implementacion usando este ejemplo.`**

  El ADT (Tipo Abstracto de Datos): es el contrato observable  qué hace cada operación, sin decir cómo. Para **IndexedBag<T>** el ADT es exactamente la interfaz dada:

  - **size()** : cuántos elementos hay
  - **add(x)** : agrega x al final lógico, permite repetidos
  - **get(i)** : retorna el elemento en posición i
  - **contains(x)** : true si x existe al menos una vez
  - **removeOne(x)** : elimina una ocurrencia de x si existe
  - **uniqueStable()** : elimina duplicados conservando la primera aparición

  El ADT no nos dice si se usa un arreglo, una lista, ni cómo se maneja la memoria.

  **Representación:** es la estructura de datos elegida para almacenar los elementos internamente. Para **IndexedBag** hay tres candidatas: **ArrayStack**, **RootishArrayStack** y **SLList**. La representación responde a "¿cómo se guardan los datos?".

  **Implementación:** es el código concreto que conecta el ADT con la representación elegida,los cuerpos de cada método usando las operaciones de la estructura subyacente. Por ejemplo, implementar add(x) sobre ArrayStack se traduce en a.add(a.size(), x). La implementación responde a "¿cómo se ejecuta cada operación?".

       Usando este mismmo ejemplo: IndexedBag es el ADT, ArrayStack es una representación posible, y el cuerpo de add que llama a ArrayStack::add(size(), x) es la implementación.
  
**`b) Complete y justifique costos para add,get,contains y removeOne en las tres representaciones.`**
  
  Para analizar los costos tenemos que  entender qué hace cada operación sobre cada estructura:

  **add(x)** , agrega al final lógico:
  
     En **ArrayStack**, agregar al final es **add(n, x)**: no desplaza nada, solo incrementa **n**. El único costo extra ocurre cuando el arreglo está lleno y hay que hacer **resize()**, que copia todos los elementos, pero esto ocurre cada vez que **n** dobla, así que el costo se amortiza. Resultado: O(1) amortizado.

     En **RootishArrayStack**, agregar al final tampoco desplaza elementos, y **grow()** solo crea un nuevo bloque sin copiar. Resultado: O(1) amortizado, con mejor constante espacial **que ArrayStack**.

     En **SLList**, **add(x)** inserta en **tail** directamente gracias al puntero de cola. Sin copias, sin desplazamientos, sin redimensionar. Resultado: O(1) estricto.

  **get(i)** , acceso por indice:

     En **ArrayStack**, **a[i]** es acceso directo a memoria contigua. Resultado: O(1) estricto.

     En **RootishArrayStack**, hay que calcular **b = i2b(i)** (raíz cuadrada y **ceil**) y luego indexar **blocks.get(b)[j]**. Son operaciones aritméticas constantes más dos indirecciones. Resultado: O(1) con constante mayor.

     En **SLList**, no hay acceso directo. **nodeAt(i)** recorre desde **head** hasta el nodo **i**. Resultado: O(n) en el peor caso.
 
  **contains(x)**  busca si existe al menos una ocurrencia:
  
  En las tres representaciones hay que recorrer todos los elementos comparando con x, porque no hay ningún orden ni tabla de búsqueda. En ArrayStack y RootishArrayStack se itera sobre índices 0 a n-1. En SLList se recorre enlace por enlace. En todos los casos: O(n).

  **removeOne(x)**  eliminar una ocurrencia si existe:

 Primero hay que encontrar x (O(n)), luego eliminarlo.
 
     En **ArrayStack**, encontrar el índice es O(n), luego **remove(i)** desplaza los elementos siguientes, O(n) en el peor caso. Resultado: O(n).
 
     En **RootishArrayStack**, encontrar es O(n), y **remove(i)** también desplaza con **set/get** sobre bloques. Resultado: O(n).
 
     En **SLList**, encontrar el nodo previo al que se quiere eliminar es O(n), luego el enlace se reencadena en O(1). Resultado: O(n) igual, pero con mejor constante al no desplazar elementos físicamente.

 Tabla resumida: 
  | Operacion | **ArrayStack** | RootishArrayStack | SLList |
  | :--- | :--- | :--- | :--- | 
  | **add(x)** | O(1) amort. | O(1) amort. | O(1) estricto |
  | **get(i)** | O(1) | O(1) con √n aritmética | O(n) | 
  | **contains(x) | O(n) | O(n) | O(n) | 
  | **removeOne(x)** | O(n) | O(n) | O(n) | 

**`c) Explique que trade-off espacial introduce RootishArrayStack frente a ArrayStack.`**
 
 Para un **ArrayStack** mantiene un único arreglo contiguo. Cuando hace **resize()**, puede llegar a tener hasta el doble de la capacidad necesaria, en el peor caso desperdicia O(n) slots vacíos. Por ejemplo, justo después de un **resize**, el arreglo tiene capacidad **2n** pero solo **n** elementos ocupados: **n** slots desperdiciados.
 
 Para un **RootishArrayStack** organiza los elementos en bloques de tamaños **1, 2, 3, ..., r**. Con r bloques la capacidad es **r(r+1)/2** y **r ≈ √(2n)**. El espacio desperdiciado entre la capacidad y los **n** elementos reales es a lo sumo **r = O(√n)** slots.

 El trade-off es : **RootishArrayStack** desperdicia mucho menos espacio (O(√n) vs O(n)), pero a cambio **get(i)** requiere calcular **i2b(i)** con una raíz cuadrada, y hay overhead de **r = O(√n)** punteros adicionales para el arreglo **blocks**. Para **IndexedBag** con muchos elementos, **RootishArrayStack** es la opción más eficiente en memoria.

**`d) Indique que operacion es mas incomoda para SLList y por que.`**
 
 La operación más incómoda es **get(i)**, porque **SLList** no tiene acceso aleatorio. Al ser una lista enlazada simple, para llegar al elemento de índice **i** hay que recorrer desde **head** nodo por nodo hasta el i-ésimo, esto es O(n) en el peor caso.

 Esto hace que cualquier operacion que dependa de **get** tambien se vea perjudicada.
 Un ejemplo claro podria ser, **removeOne(x)** en **ArrayStack** sobre arreglo encuentra el indice y borra; en **SLList** hay que recorrer enlace por enlace, y además al eliminar un nodo interior hay que llegar al nodo anterior, lo que requiere otro recorrido desde **head**.

 **SLList** solo guarda el puntero **next**, no **prev**. Por eso retroceder o saltar a una posición arbitraria es imposible en O(1). Una **DLList** (doblemente enlazada) alivia un poco esto pero no resuelve el O(n) del acceso por índice.

**`e) Diseñe a alto nivel uniqueStable() y analice su costo si no se permite usar tablas hash ni estructuras externas no vistas.`**

 **uniqueStable()** debe eliminar todos los duplicados conservando la primera aparición de cada elemento, manteniendo el orden original.

 Su diseño a alto nivel es que se recorre la colección con dos índices: un índice **i** que avanza elemento por elemento de izquierda a derecha, y para cada elemento en posición **i** se busca si ya apareció en las posiciones **0** a **i-1**. Si ya apareció, se elimina; si no, se conserva y se avanza.

 Para cada posición **i** de **0** a **n-1** (ajustando **n** dinámicamente):

 - Se recorre el subarreglo **[0, i-1]** buscando si algún elemento es igual a **get(i)**.
 - Si se encuentra un duplicado, se llama a **removeOne** sobre la posición **i** y se repite el chequeo en la misma posición **i** (que ahora tiene el siguiente elemento).
 - Si no se encuentra duplicado, se avanza **i**.

 Análisis de costo:

 Para cada uno de los **n** elementos, la búsqueda hacia atrás recorre hasta i elementos -> costo O(i). Sumando sobre todos los índices:

     costo total = O(0) + O(1) + O(2) + ... + O(n-1) = O(n²)

 Además, cada **removeOne** desplaza elementos (en **ArrayStack** o **RootishArrayStack**) con costo O(n), lo que no cambia el orden asintótico pero sí la constante.

 En conclusion sin las estructuras iniciales como tablas hash,**uniqueStable()** tiene costo O(n²) en cualquiera de las tres representaciones, porque la búsqueda de duplicados requiere comparar cada elemento con todos los anteriores.

#### Pregunta 2 

**`a)Trace sumRec([2,4,6,8],4) mostrando llamadas y retornos.`**

  **Llamadas:**

  Paso 1: Llamada inicial
  sumRec(A, 4)
   -> Como n=4 ≠ 0, ejecuta: return sumRec(A, 3) + A[3]
   -> A[3] = 8
   -> Se detiene aquí, necesita el valor de sumRec(A, 3)

  Paso 2: 
  sumRec(A, 3)
   -> n=3 ≠ 0, ejecuta: return sumRec(A, 2) + A[2]
   -> A[2] = 6
   -> Necesita sumRec(A, 2)

  Paso 3:
  sumRec(A, 2)
   -> n=2 ≠ 0, ejecuta: return sumRec(A, 1) + A[1]
   -> A[1] = 4
   -> Necesita sumRec(A, 1)

  Paso 4:
  sumRec(A, 1)
   -> n=1 ≠ 0, ejecuta: return sumRec(A, 0) + A[0]
   -> A[0] = 2
   -> Necesita sumRec(A, 0)

  Paso 5:
  sumRec(A, 0)
   -> n=0, ejecuta: return 0
   -> Este es el caso base, ya no llama más

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

**`b) Pruebe correctitud por induccion sobre n.`**

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

**`c) Analice tiempo y espacio adicional. Distinga memoria del arreglo y pila de llamadas.`**
  
  Cada llamada aca hace O(1) trabajo(una suma,una comparacion). La funcion se llama **n+1** veces(desde **n** hasta **0**).

         T(n) = T(n-1) + O(1)  →  T(n) = O(n)
  Espacio ,hay que distinguir dos cosas:
  | Tipo de memoria | Tamaño | Explicacion | 
  | :--- | :--- | :--- |
  | Memoria del arreglo **A[]** | O(n) | El arreglo ya existía antes, la función no lo crea, solo lo recibe como puntero. No es espacio adicional de la función. |
  | Pila de llamadas (call stack) | O(n) | Cada llamada recursiva apila un frame con **{A, n, dirección de retorno}**. Se apilan **n+1** frames simultáneamente antes de empezar a retornar. Este sí es espacio adicional. |

 Observacion: La distinción es importante: la función usa O(1) espacio propio por frame, pero O(n) espacio adicional total por la profundidad de la recursión.

**`d) Escriba una version iterativa equivalente y proponga una invariante del ciclo.`**

  Acordanonos lo que avanzamos en la semana 1 del archivo **sum.cpp**

 Version iterativa: 

  ```C++
  int sumIter(const int A[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++)
        s += A[i];
    return s;
  }
  ```

  **El Invariante del ciclo:**
  Al inicio de cada iteración con valor i:

      s = A[0] + A[1] + ... + A[i-1]

  Verificacion:

  - Inicio (i=0): s = 0, suma vacía. 
  - Mantenimiento: si al inicio de la iteración i se cumple s = A[0]+...+A[i-1], entonces tras ejecutar s += A[i], al inicio de la iteración i+1 tenemos s = A[0]+...+A[i]. 
  - Terminación (i=n): el ciclo termina, y por la invariante s = A[0]+...+A[n-1], que es el resultado correcto. 
  
  Observacion: Ventaja de la versión iterativa: usa O(1) de espacio adicional (solo la variable s e i), sin pila de llamadas.

**`e) ¿Por qué const int A[] comunica una intención útil para correctitud?`**

  Porque el calificador const le dice al compilador y al lector que la función se compromete a no modificar el arreglo. Esto es útil por tres razones:

  1. Garantía formal: el compilador rechazará cualquier línea dentro de la función que intente escribir en A[i]. Así se detectan bugs accidentales en tiempo de compilación, no en ejecución.
  2. Razonamiento más simple: al probar correctitud (como en el inciso b), podemos asumir que A no cambia entre llamadas recursivas. Sin const, tendríamos que verificar además que ninguna llamada altera el arreglo.
  3. Composabilidad: permite pasar arreglos declarados como const sin errores de tipo, haciendo la función más reutilizable.

**`f) Indique dos casos borde y como deberian probarse.`**

  Caso borde 1 —> arreglo vacío (n = 0):
  
     int A[] = {}; //....(1)

     assert(sumRec(A, 0) == 0); //....(2)

  Por qué es borde: es el caso base de la recursión. Si falla aquí, toda la inducción colapsa. Se espera retorno 0.

  Caso borde 2 —> arreglo con un solo elemento (n = 1):

     int A[] = {42}; //.....(1)

     assert(sumRec(A, 1) == 42); //....(2)

  Por qué es borde: es el primer paso inductivo real. La llamada hace sumRec(A,0) + A[0] = 0 + 42 = 42. Verifica que el caso base y el paso recursivo interactúan correctamente.

#### Pregunta 3
 
**`a) Para r=5, dibuje los bloques y ubique los indices logicos 0 a 14.`** 
   
   Bueno recordando la semana 2 que vimos RootishArrayStack.
   
   capacidad total = 1+2+3+4+5 = r(r+1)/2 = 5×6/2 = 15 (índices 0 a 14)

   r=0 o Bloque 0 (tamaño 1): [ 0 ]

   r=1 o Bloque 1 (tamaño 2): [ 1 | 2 ]
   
   r=2 o Bloque 2 (tamaño 3): [ 3 | 4 | 5 ]
   
   r=3 o Bloque 3 (tamaño 4): [ 6 | 7 | 8 | 9 ]
   
   r=4 o Bloque 4 (tamaño 5): [ 10 | 11 | 12 | 13 | 14 ]

**`b) Para los indices i=0,1,2,5,9,14, indique el bloque y el desplazamiento dentro del bloque.`**

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
  
**`c) Explique por que se necesita una funcion i2b(i) o locate (i).`**
   
   A diferencia de **ArrayStack**, donde acceder al elemento **i** es simplemente **a[i]** en O(1) directo, en **RootishArrayStack** la memoria está repartida en bloques separados. No hay un único arreglo contiguo.

   **i2b(i)** es como un GPS, resuelve la pregunta: ¿en qué bloque está el índice lógico i, y en qué posición dentro de ese bloque? Sin esta función, sería imposible saber a qué puntero de blocks[] acceder ni con qué índice interno. 

**`d)Justifique por que el espacio desperdiciado es O(√n) cuando hay n elementos.`**

   Con r bloques, la capacidad total es r(r+1)/2. Si hay n elementos entonces r ≈ √(2n).

   El espacio desperdiciado es la diferencia entre la capacidad y los elementos reales:

       desperdicio = r(r+1)/2 − n ≤ r(r+1)/2 − (r−1)r/2 = r

   Como r ≈ √(2n), el desperdicio es a lo sumo O(r) = O(√n).

   Esto es la ventaja clave sobre ArrayStack: cuando ArrayStack hace resize(), puede desperdiciar hasta n/2 slots (O(n)). RootishArrayStack nunca desperdicia más de O(√n), porque los bloques crecen de a uno y son pequeños.

**`e)Compare el acceso por indice con ArrayStack.¿Que se conserva y que costo adicional aparece?.`**
   
   | Aspecto | ArrayStack | RootishArrayStack | 
   | :--- | :--- | :--- | 
   | Acceso get(i) | a[i] O(1) puro, un solo derreferenciamiento | blocks[b][j]  O(1) con costo aritmético: calcular b y j vía i2b() implica una raíz cuadrada y un ceil |
   | Lo que se conserva | O(1) asintotico | O(1) asintótico (igual de rápido en teoría) |
   | Costo adicional | Ninguno | Dos indirecciones: primero blocks[b], luego [j]; más las operaciones de sqrt y ceil en cada acceso |
   | Cache locality | Excelente (un arreglo contiguo) | Peor: los bloques están dispersos en memoria |

   En resumidas palabras:  el acceso sigue siendo O(1) pero con una constante mayor por la aritmética de i2b y la doble indirección.

**`f) Explique que ocurre cuando se necesita crecer o reducir el numero de bloques.`**

  Al crecer —> **grow()**:
   ```C++
   void grow() {
    blocks.add(blocks.size(), new T[blocks.size() + 1]);
   }
   ```
 Se agrega un nuevo bloque al final de blocks[]. Si había r bloques, el nuevo bloque tiene tamaño r+1. El costo es O(r) = O(√n) para alocar el nuevo arreglo, más O(1) amortizado para insertar el puntero en blocks[] (que es un ArrayStack y puede necesitar su propio resize()). No se copia ningún dato existente.

  Al encoger —> **shrink()**:
   ```C++
  void shrink() {
    int r = blocks.size();
    while (r > 0 && (r-2)*(r-1)/2 >= n) {
        delete[] blocks.remove(blocks.size()-1);
        r--;
    }
  }
   ```
  Se eliminan bloques del final mientras la capacidad con r-2 bloques sea suficiente para los n elementos actuales. Cada bloque eliminado libera su memoria con delete[]. La condición (r-2)(r-1)/2 >= n asegura que siempre queda capacidad suficiente.

  La diferencia crucial con ArrayStack::resize() es que aquí nunca se copian todos los elementos al crecer o encoger: solo se agrega o elimina un bloque. Eso hace que grow() sea O(√n) en vez de O(n).

#### Pregunta 4

front = [30, 20, 10]  y back  = [40, 50, 60, 70], su secuencia logia seria [10, 20, 30, 40, 50, 60, 70] —> índices 0 al 6.

**`a) Muestre como se calcula get(i) para i=0,2,3,6.`**

  get(i) para i = 0, 2, 3, 6
   
  Si recordamos en la semana 2 el DualArrayDeque
  La regla del código es:
  
  ```C++
  if (i < front.size())  ->  front.get(front.size() - i - 1)
  else                   ->  back.get(i - front.size())
  ```
  
  Con front.size() = 3:

  | i | ¿i<3? | Calculo | Resultado | 
  | :--- | :--- | :--- | :--- |
  | 0 | Si | front.get(3-0-1) = front[2] = 10 | 10 |
  | 2 | Si | front.get(3-2-1) = front[0] = 30 | 30 |
  | 3 | No | back.get(3-3) = back[0] = 40 | 40 |
  | 6 | No | back.get(6-3) = back[3] = 70 | 70 |

**`b) Ejecute add(1,15) y add (6,55) indicando en cual arreglo se inserta y como cambia la representacion.`**
 
 add(1, 15) —> i=1 < front.size()=3, va a front:

 front.add(front.size() - i, x)  =  front.add(3-1, 15)  =  front.add(2, 15)

 **front**pasa de [30,20,10] a [30,20,15,10].
 Secuencia lógica: [10, 15, 20, 30, 40, 50, 60, 70] —> ahora n=8, front.size()=4.

 add(6, 55) —> sobre la nueva secuencia de 8 elementos, i=6 >= front.size()=4, va a back:
 
 back.add(i - front.size(), x)  =  back.add(6-4, 55)  =  back.add(2, 55)

 **back** pasa de [40,50,60,70] a [40,50,55,60,70].
 Secuencia lógica: [10, 15, 20, 30, 40, 50, 55, 60, 70].

**`c) Explique porque front guarda su contenido en orden inverso.`**

 Porque **front** representa el extremo izquierdo de la deque y se opera por su extremo derecho (que es el extremo más eficiente de un **ArrayStack**). Si guardáramos front en orden normal **[10, 20, 30]**, añadir al frente de la deque (índice 0) requeriría insertar al inicio del arreglo, desplazando todos los elementos O(n). Al guardarlo invertido **[30, 20, 10]**, el elemento lógico **i=0** (que es **10**) está en **front[last]**, y agregar/quitar al frente de la deque equivale a un **push/pop** al final del **ArrayStack**, que es O(1) amortizado.

**`d) Defina una condicion razonable de balance entre front y back. Explique que debe hacer balance() cuando se viola.`**

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

**`e) Justifique que el rebalanceo puede mantener costos amortizados aceptables si no ocurre en cada operacion.`**

 **balance()** cuesta O(n), pero solo puede dispararse después de que se hayan hecho al menos n/3 operaciones desde el último balance. Para que un arreglo triplique al otro partiendo de un estado balanceado, necesitas insertar o eliminar por lo menos **n/3** veces del mismo lado. Eso significa que hay al menos **n/3** operaciones "baratas" que "pagan" el costo del rebalanceo.

 Formalmente: cada operación deposita crédito O(1). Cuando se acumulan suficientes créditos (al menos O(n) acumulados), se dispara el balance de costo O(n) exactamente cubierto. El resultado es O(1) amortizado por operación a pesar de que el rebalanceo individual sea O(n).

 Si **balance()** se llamara en cada operación, el costo sería O(n) por operación y todo se arruinaría. La condición **3×** garantiza que el rebalanceo sea infrecuente, preservando el costo amortizado.

#### Pregunta 5
  
**`a) Explique la idea de representacion de SEList y como difiere de una DLList simple.`**

 **DLList** almacena cada elemento en un nodo separado:

     dummy <-> [10] <-> [20] <-> [30] <-> [40] <-> dummy

 Cada nodo tiene dos punteros (prev, next) -> overhead de 2 punteros por elemento.
 Acceso al elemento i cuesta O(n) porque hay que recorrer nodo a nodo.

 **SEList** agrupa los elementos en bloques (pequeños BDeque basados en ArrayDeque), y esos bloques se encadenan en una lista doblemente ligada:

     dummy <-> [10,20,30] <-> [40,50,60] <-> [70,80,90] <-> dummy
          
                bloque 0       bloque 1       bloque 2
 
 Cada bloque tiene capacidad b+1. Los punteros se pagan una vez por bloque, no por elemento. El acceso a **i** primero salta de bloque en bloque (O(n/b)) y luego indexa dentro del bloque (O(b)) -> total O(b + n/b).

**`b) Indique que invariante deberia cumplirse sobre el tamaño de los bloques, salvo quiza en extremos.`**

 Todo bloque interior (no el primero ni el último) debe tener exactamente b elementos:
  
     b ≤ bloque_interior.size() ≤ b+1

 Más precisamente, en el código la capacidad máxima de cada BDeque es b+1. La invariante útil es:

 - Bloques interiores: exactamente **b** elementos (llenos).
 - Extremos (primer y último bloque): pueden tener entre **1** y **b+1** elementos, son los únicos que pueden estar parcialmente llenos.

 Esto garantiza que con r bloques el total de elementos es aproximadamente r·b, y el overhead de punteros es O(r) = O(n/b).

**`c) Describa que ocuree al insertar en un bloque lleno:busqueda de espacio, desplazamientos entre bloques o creacion de bloque nuevo.`**

 Cuando add(i, x) encuentra que el bloque destino tiene b+1 
 elementos (lleno), el código busca espacio así:

 Primero haremos búsqueda hacia adelante: recorre hasta b bloques siguientes buscando uno con **size() < b+1**. Si lo encuentra en **r < b** pasos, hace un efecto dominó hacia atrás: mueve el último elemento de cada bloque al inicio del siguiente, abriendo un hueco en el bloque destino.

     [A B C|] <- bloque lleno   ->   insertar X en pos 1

     [A B C D] [E F G|]
     
     desplazar

     [A B C] [D E F] [G|]   <- X se inserta en el hueco
 
 Luego si no hay espacio en **b** bloques (r==b): se llama a **sprea(l.u)** que crea un nuevo bloque vacío **b** posiciones adelante y redistribuye los elementos uniformemente entre los **b+1** bloques afectados.

 Finalmente, si se llega al **dummy**: se crea un nuevo bloque vacio al final y se inserta ahi.

 El costo es O(b) en el caso normal (desplazamiento domino) y O(b²) amortizado cuando ocurre **spread**.

**`d) Compare SEList con ArrayDeque para muchas insercciones cerca del centro.`**

 | Aspecto | **ArrayDeque** | **SEList** |
 | :--- | :--- | :--- | 
 | Insertar en posición i | O(n): desplaza hasta n/2 elementos | O(b + n/b): salta n/b bloques + desplaza b elementos dentro del bloque | 
 | Óptimo con b=√n | no aplica | O(√n) por inserción |
 | Memoria | Un arreglo contiguo, muy cache-friendly | Bloques dispersos, peor localidad | 
 | Overhead de punteros | O(1) (un arreglo) | O(n/b) punteros de nodos |
 | Rebalanceo/resize | O(n) amortizado | **spread**/**gather** O(b²) amortizado |

 Para muchas inserciones en el centro, **SEList** con **b ≈ √n** gana: cada inserción cuesta O(√n) en vez de O(n). La desventaja es peor localidad de caché y la complejidad del código.

**`e) Explique por que la interfa puede aparecer la de una lista aunque internamente use arreglos pequeños.`**

 La interfaz parece una lista indexada común porque expone exactamente los mismos métodos estándar (get(i), add(i,x), remove(i)). Esto se basa en el principio de encapsulamiento: la representación interna de bloques encadenados es un detalle de implementación oculto para el código cliente.

 El usuario interactúa únicamente mediante un índice lógico. Internamente, funciones como getLocation(i) traducen de forma transparente ese índice a la coordenada real (bloque, posición_dentro_del_bloque). De este modo, aunque la estructura interna sea compleja, el comportamiento observable es idéntico al de cualquier otra lista.

**`f) Proponga una prueba de estres que detecte errores de tamaño logico o perdida de elementos.`**

  La prueba consiste en realizar inserciones y eliminaciones masivas en posiciones críticas (inicio, centro y final) para forzar los métodos de balanceo (spread y gather). En paralelo, se replican exactamente las mismas operaciones en una estructura de referencia confiable (como std::vector).

  Tras cada operación, se automatizan dos verificaciones: que el size() de ambas estructuras coincida (detecta errores de conteo) y que un recorrido completo usando get(i) devuelva los mismos elementos en el mismo orden (detecta pérdida, duplicación o desplazamiento incorrecto de elementos entre bloques).
 
#### Pregunta 6

**`a) Proponga pruebas concretas que probablemente fallen si no se maneja correctamente el wrap-around.`**
  
  Prueba 1: Se construye un ArrayDeque con capacidad 4, j = 3, n = 3, con elementos [10, 20, 30] en posiciones físicas 3, 0, 1 respectivamente. Se llama remove(1). El desplazamiento de elementos para cerrar el hueco debe cruzar el borde del arreglo usando aritmética modular. Si la implementación calcula a[j+k] en lugar de **a[(j+k) % a.length]**, accede a la posición física 4, que está fuera del arreglo.

 Prueba 2: Se construye un **ArrayDeque** con capacidad 4, **j = 2**, n = 4, con elementos [10, 20, 30, 40] en posiciones físicas 2, 3, 0, 1 respectivamente. Se llama remove(0). Al eliminar el primer elemento la implementación debe actualizar j = (j + 1) % a.length. Si se hace sin módulo, j queda con el valor a.length, que es un índice fuera de rango y corrompe el estado interno.

**`b) Proponga 2 pruebas para la eliminacion en estructura de tamaño 1 y tamaño 2.`**

  Tamaño 1: Se inserta un único elemento y se llama **remove(0)**. Se verifica que el valor retornado es el elemento insertado, que **size()** retorna 0 después del remove, y que un **add** posterior funciona correctamente. Esto confirma que la rama del **for** no itera con **n=1** y que **resize()** se invoca dejando el estado interno consistente.

  Tamaño 2, eliminar primero: Se insertan dos elementos con **j = capacidad - 1**, se llama **remove(0)*** y se verifica que el elemento restante es el correcto y que **n = 1**. Este caso fuerza que j se actualice con módulo: si j = capacity - 1 y la implementación hace **j = j + 1** sin módulo, **j** queda igual a **capacidad**, que es inválido.

**`c) Explique por que pasar pruebas publicas no prueba correctitud total.`**
   
  Porque las pruebas públicas construyen el deque desde cero con j = 0, por lo que nunca hay wrap-around. La implementación puede ser correcta para ese caso y fallar cuando j ≠ 0, ya que los cálculos de índice circular difieren. Al no haber pruebas que fuercen j a estar cerca del borde del arreglo, los errores en la aritmética modular pasan desapercibidos. El valor de j es un estado interno que las pruebas públicas no controlan directamente, por lo que solo cubren el comportamiento observable en condiciones normales, no todos los estados internos posibles.

**`d) Indique que invariante deberia revisarse despues de cada eliminacion.`**

 Después de cada eliminación deben cumplirse tres condiciones: primero, n disminuyó exactamente en 1; segundo, todos los elementos en posiciones lógicas [0, n-1] son accesibles con get(i) y retornan los valores correctos respetando la aritmética circular, es decir, el elemento en posición física (j+i) % a.length es el esperado para cada índice lógico i; tercero, el elemento eliminado ya no aparece en ninguna posición lógica de la secuencia, descartando duplicaciones accidentales por un for que copiara en dirección incorrecta.

**`e) Explique que tipo de error podria detectar ASan en una implementacion incorrecta y que tipo de error logico no detectaria.`**

 ASan detecta accesos fuera de los límites del arreglo físico y uso de memoria ya liberada. Por ejemplo, si la implementación calcula **a [j+k]** sin módulo y **j+k >= a.length**, ASan reporta el acceso ilegal.
 Lo que ASan no detecta son errores lógicos donde se accede a una posición dentro del arreglo pero que corresponde al índice lógico equivocado. Por ejemplo, si el módulo se calcula incorrectamente pero produce un valor que sigue estando entre 0 y **a.length-1**, el acceso es físicamente válido y ASan no lo reporta, aunque el resultado sea incorrecto. Ese tipo de bug produce valores erróneos silenciosamente y solo puede detectarse con **assert** que comparen el resultado obtenido con el esperado.

#### Pregunta 7

**`a) Defina ADT con precondiciones y comportamiento observable.`**

  | Operacion | Precondicion | Comportamiento observable | 
  | :--- | :--- | :--- | 
  | apply(x) | ninguna | Agrega el estado x al final. El estado actual pasa a ser x. size() aumenta en 1. |
  | undo() | size() >= 2 | Elimina el estado más reciente. El estado actual pasa a ser el anterior. size() disminuye en 1. |
  | current() | size() >= 1 | Retorna el estado actual (el último no deshecho). No modifica el historial. | 
  | size() | ninguna | Retorna la cantidad de estados almacenados. Siempre ≥ 0. |
  | clear() | ninguna | Elimina todos los estados. size() pasa a 0. Después current() queda indefinido. |

**`b) Proponga dos representaciones: una basada en arreglo dinamico y otra basada en lista enlazada. Indique sus invariantes.`**

 Representación 1 
 Arreglo dinámico (**ArrayStack**)
 
  Se usa un **ArrayStack<T>** donde los estados se apilan cronológicamente. El índice **n-1** es siempre el estado actual. **apply** empuja al final, **undo** elimina el último.

     Índices:  [  0  |  1  |  2  |  3  ]
     Estados:  [ E0  | E1  | E2  | E3  ]
                                    
                           current = a[n-1]

 Invariantes de la representación:
  - **a[0..n-1]** contiene los estados en orden cronológico estricto.
  - **n >= 0** siempre.
  - Si **n > 0**, el estado actual es exactamente **a[n-1]**.
  - La capacidad satisface **n <= a.length <= 3*n** (condición del **resize** de **ArrayStack)**.
  - Los slots **a[n..a.length-1]** son basura y nunca se leen.
 
 Representacion 2
 Lista enlazada (**SLList**)
 
 Se usa una **SLList<T>** donde **head** apunta al estado más antiguo y **tail** apunta al estado actual. **apply** agrega al final en O(1) gracias al puntero **tail**. **undo** requiere llegar al penúltimo nodo para actualizar **tail**.

     head -> [E0] -> [E1] -> [E2] -> [E3] -> nullptr
                              
                                  tail = current

 Invariantes de la representación:

  - Los nodos están en orden cronológico desde **head** hasta **tail**.
  - **tail** apunta siempre al estado actual cuando **n > 0**.
  - Si **n == 0**, tanto **head** como **tail** son **nullptr**.
  - No hay ciclos: seguir **next** desde **head** llega a **nullptr** en exactamente **n** pasos.
  - No existe puntero **prev**: retroceder requiere recorrer desde **head**.

**`c) Compare costos de apply, undo, current y clear.`**

 **apply(x)**:

 Con **ArrayStack**: se traduce en **add(n, x)**  inserta al final sin desplazar ningún elemento. Si el arreglo está lleno se llama **resize()** que copia todos los elementos, pero esto ocurre con frecuencia decreciente. Costo: O(1) amortizado.
 
 Con **SLList**: se crea un nuevo nodo y se enlaza a **tail->next**, luego **tail = nuevo nodo**. Nunca hay copia ni redimensionamiento. Costo: O(1) estricto.

 **undo():**

 Con **ArrayStack**: se traduce en **remove(n-1)** elimina el último elemento, decrementa **n**, y puede llamar **resize()** si **a.length >= 3*n**. No hay desplazamiento de elementos. Costo: O(1) amortizado.
 
 Con **SLList**: **tail** apunta al último nodo pero no hay puntero **prev**. Para actualizar **tail** al penúltimo hay que recorrer toda la lista desde **head** hasta encontrar el nodo cuyo **next == tail**. Costo: O(n).
 
 **current():**

 Con **ArrayStack**: retorna **a[n-1]**  acceso directo por índice. Costo: O(1).

 Con **SLList**: retorna **tail->x**  acceso directo al puntero de cola. Costo: O(1).

 **clear():**

 Con **ArrayStack**: resetea **n = 0** y reemplaza el arreglo por uno de tamaño 1. La memoria del arreglo antiguo se libera automáticamente. Costo: O(1) (o O(n) si T tiene destructores no triviales).

 Con **SLList**: hay que recorrer todos los nodos y liberar cada uno con **delete**. Costo: O(n).

 Tabla resumida:
  | Operacion | ArrayStack | SLList | 
  | :--- | :--- | :--- | 
  | apply(x) | O(1) amort. | O(1) estricto |
  | undo() | O(1) amort. | O(n) |
  | current() | O(1) | O(1) |
  | clear() | O(1) | O(n) |

**`d) Explique como manejaria el caso de deshacer hasta quedar sin estado previo.`**

 Este es el caso en que size() == 1 y se intenta llamar undo(). La precondición exige size() >= 2, por lo que hay dos estrategias posibles:

 Estrategia 1 
 Lanzar error o hacer nada (defensivo):
 Si **size() < 2**, **undo()** simplemente no hace nada y retorna sin modificar el historial. Se puede acompañar de un valor booleano de retorno que indique si el **undo** fue exitoso o no. Así el estado inicial queda siempre protegido.
   
     Historial: [ E0 ] -> undo() no hace nada, current() sigue retornando E0

 Estrategia 2
 Estado vacío permitido:
 Se relaja la precondición a **size() >= 1**. Al deshacer el único estado, el historial queda vacío (**size() == 0**) y **current()** queda indefinido hasta que se llame **apply()** de nuevo. Esta estrategia requiere que el código cliente verifique **size() > 0** antes de llamar **current()**.

 Ahora aca la Estrategia 1 es la mas segura porque mantiene siempre un estado valido en el historial. 

  La implementación con ArrayStack verifica simplemente:
  
     si n >= 2 entonces remove(n-1)
     sino no hacer nada (o señalizar)
  
**`e) Proponga pruebas para secuencias largas, estados repetidos y operaciones invalidas.`**

 Para secuencias largas: Se aplican N estados consecutivos (por ejemplo N = 10.000), luego se deshacen todos hasta llegar al primero. Se verifica que **size()** disminuya correctamente en cada **undo()** y que **current()** retorne en cada paso el estado esperado. Esto estresa el **resize()** en **ArrayStack** y el recorrido en **SLList**.

 Para estados repetidos: Se aplican varios estados con el mismo valor, por ejemplo **apply(5)**, **apply(5)**, **apply(5)**. Se verifica que el historial mantenga tres entradas distinta, que **size() == 3**, y que **undo()** elimine una a una correctamente. Esto confirma que la estructura almacena estados y no valores únicos.

 Para operaciones invalidas: Se intenta llamar **undo()** sobre un historial con un solo estado y luego con uno vacío. Se verifica que la operación no corrompa el estado interno, **size()** debe permanecer igual, **current()** debe seguir retornando el mismo valor, y no debe ocurrir ningún acceso a memoria inválida. Esto nos probara que la precondición se maneja correctamente.

**`f) Suponga que ahora se pide consultar cualquier estado por indice. Reevalue su eleccion de estructura y justifique.`**

 El nuevo requisito es **getAt(i)** — acceder al estado i-ésimo del historial en tiempo eficiente.

 Con **ArrayStack**: **getAt(i)** se implementa directamente como **a[i]** ,acceso O(1) por índice directo. No cambia nada en la implementación existente. **ArrayStack** sigue siendo la mejor opción.

 Con **SLList**: **getAt(i)** requiere recorrer **i** nodos desde **head**, costo O(n). Esto hace que **SLList** sea inadecuada para este nuevo requisito.
 
 Con el nuevo requisito de acceso por índice, la representación recomendada es ArrayStack por su simplicidad y O(1) estricto para getAt(i)















