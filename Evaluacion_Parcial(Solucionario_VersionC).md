### CC232 - Evaluacion Parcial 1 (Version C)
Nombre: Joel Gustavo Carhuarica Aguilar 

#### Pregunta 2 

a)Trace sumRec([2,4,6,8],4) mostrando llamadas y retornos.

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

b) Pruebe correctitud por induccion sobre n.

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

c) Analice tiempo y espacio adicional. Distinga memoria del arreglo y pila de llamadas.
  
  Cada llamada aca hace O(1) trabajo(una suma,una comparacion). La funcion se llama **n+1** veces(desde **n** hasta **0**).

         T(n) = T(n-1) + O(1)  →  T(n) = O(n)
  Espacio ,hay que distinguir dos cosas:
  | Tipo de memoria | Tamaño | Explicacion | 
  | :--- | :--- | :--- |
  | Memoria del arreglo **A[]** | O(n) | El arreglo ya existía antes, la función no lo crea, solo lo recibe como puntero. No es espacio adicional de la función. |
  | Pila de llamadas (call stack) | O(n) | Cada llamada recursiva apila un frame con **{A, n, dirección de retorno}**. Se apilan **n+1** frames simultáneamente antes de empezar a retornar. Este sí es espacio adicional. |

 Observacion: La distinción es importante: la función usa O(1) espacio propio por frame, pero O(n) espacio adicional total por la profundidad de la recursión.

d) Escriba una version iterativa equivalente y proponga una invariante del ciclo.

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

e) ¿Por qué const int A[] comunica una intención útil para correctitud?

  Porque el calificador const le dice al compilador y al lector que la función se compromete a no modificar el arreglo. Esto es útil por tres razones:

  1. Garantía formal: el compilador rechazará cualquier línea dentro de la función que intente escribir en A[i]. Así se detectan bugs accidentales en tiempo de compilación, no en ejecución.
  2. Razonamiento más simple: al probar correctitud (como en el inciso b), podemos asumir que A no cambia entre llamadas recursivas. Sin const, tendríamos que verificar además que ninguna llamada altera el arreglo.
  3. Composabilidad: permite pasar arreglos declarados como const sin errores de tipo, haciendo la función más reutilizable.

f) Indique dos casos borde y como deberian probarse.

  Caso borde 1 —> arreglo vacío (n = 0):
  
  int A[] = {};
  
  assert(sumRec(A, 0) == 0);

  Por qué es borde: es el caso base de la recursión. Si falla aquí, toda la inducción colapsa. Se espera retorno 0.

  Caso borde 2 —> arreglo con un solo elemento (n = 1):

  int A[] = {42};

  assert(sumRec(A, 1) == 42);

  Por qué es borde: es el primer paso inductivo real. La llamada hace sumRec(A,0) + A[0] = 0 + 42 = 42. Verifica que el caso base y el paso recursivo interactúan correctamente.