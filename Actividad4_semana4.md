### Actividad4_Semana4
#### Bloque 1 - Núcleo conceptual de la semana
1. Explica con tus palabras la diferencia entre acceso `LIFO` y acceso `FIFO`.

  - LIFO (Pila): El último elemento en ingresar (push) es el primero en ser retirado (pop). Imagina una pila de platos: solo puedes interactuar de forma segura con el que está arriba del todo.

  - FIFO (Cola): El primer elemento en ingresar (enqueue) es el primero en salir (dequeue). Es la dinámica de una fila de banco real: el que llegó primero merece ser atendido primero, y los nuevos se forman al final.

2. Explica por qué `Stack` resuelve naturalmente problemas donde importa "lo último pendiente".

 El control de flujo en la ejecución de un programa requiere recordar "dónde estaba antes de desviarme". Una pila resuelve esto de forma natural porque preserva el contexto inverso. Cuando el algoritmo avanza en un subproblema (como analizar un paréntesis interno o explorar un camino en Maze.h), el estado anterior queda pausado justo debajo. Al terminar la subtarea actual, el elemento superior de la pila (top) te devuelve de inmediato al contexto inmediato anterior.

3. Explica por qué `Queue` modela naturalmente procesos de espera y atención.

 Porque la cola garantiza la equidad cronológica y simula el paso del tiempo de forma secuencial. En BankSimulation.h, los clientes se procesan exactamente en el orden en que llegan. Si usáramos una pila, el último cliente en llegar sería atendido primero, dejando al primer cliente esperando indefinidamente (un fenómeno algorítmico conocido como inanición o starvation). La cola asegura que los recursos se distribuyan respetando el orden de arribo.

4. Explica qué significa reemplazar recursión implícita por una estructura 
explícita.

  Cuando usas una función recursiva (como en convertRecursive), la computadora utiliza una pila oculta llamada pila de llamadas del sistema (Call Stack) para recordar las variables locales de cada paso.

  Reemplazar la recursión por una estructura explícita (como se hace en NQueens.h o Maze.h) significa que tú, como programador, asumes el control de esa memoria creando un objeto Stack<T> en el heap o en el stack local.

   - Ventaja: Evitas el riesgo de un Stack Overflow (el límite de la pila del sistema suele ser muy estricto).

   - Control: Puedes inspeccionar, depurar o modificar el historial del algoritmo en cualquier momento porque la pila es una variable más de tu código.
5. Explica qué información mínima debe guardarse para que una pila permita reconstruir una solución parcial.

   Para poder reconstruir el camino o deshacer pasos (backtracking), cada elemento guardado en la pila debe contener, como mínimo:

     1. El estado o posición actual: (Por ejemplo, las coordenadas (x, y) en Maze.h o la fila/columna de la reina en Queen.h).

     2. El historial de decisiones locales / Siguiente opción a probar: Necesitas saber qué alternativas ya exploraste y cuál sigue. En Maze.h, esto se logra mediante el enumerador ESWN outgoing, que guarda qué dirección se intentó tomar antes de pausar o retroceder. Sin esto, el algoritmo entraría en un bucle infinito al regresar a un estado previo.

6. Compara la conversión de base recursiva e iterativa: ¿qué comparten y qué cambia en el control del proceso?

 - **Qué comparten:** Ambas usan la misma lógica matemática (divisiones sucesivas por la base y almacenamiento de residuos mediante el arreglo digit[]). El orden en que se calculan los dígitos es inverso al orden en que deben imprimirse.

 - **Qué cambia en el control:** * La versión recursiva delega el almacenamiento en la pila de llamadas del sistema operativo durante la fase de ida, y el objeto Stack<char> se va llenando a medida que la recursión "despierta" en el retorno.

   - La versión **iterativa** controla el proceso mediante un bucle while explícito y va guardando activamente los residuos en tu estructura Stack<char> de inmediato. Al final, ambas usan popAll para invertir el resultado final.

7. Explica por qué la verificación iterativa de paréntesis necesita almacenar aperturas pendientes.

   Porque los símbolos de agrupación operan bajo una regla de anidación simétrica (el último que se abre debe ser el primero que se cierre). Cuando el código en Parentheses.h encuentra un cierre (como ]), el algoritmo no tiene ojos en la espalda para saber si es válido; necesita comprobar si el último paréntesis abierto sin emparejar coincide exactamente con ese tipo. Al guardar las aperturas en una pila, el carácter correcto para validar el cierre siempre estará en el top().

8. Explica por qué el evaluador de expresiones necesita dos pilas y no una sola.

 El algoritmo de evaluación de expresiones (basado en el algoritmo de Shunting-yard de Dijkstra en ExpressionEvaluator.h) procesa dos tipos de entidades con reglas de negocio completamente distintas:

   1. Pila de Operandos (Stack<double>): Guarda los números (valores listos para ser operados).

   2. Pila de Operadores (Stack<char>): Guarda los operadores pendientes (+, *, ^, ( ) debido a que su ejecución está condicionada por la jerarquía y precedencia matemática.

 No pueden mezclarse en una sola pila lineal de manera simple porque un operador de alta prioridad (como *) puede aparecer después de uno de baja prioridad (como **+**), obligando al algoritmo a posponer la ejecución del **+** y mantenerlo en espera mientras extrae operandos para calcular primero la multiplicación. Separar los datos (operandos) del control (operadores) permite aplicar la matriz de prioridades de **OperatorPriority.h** de forma limpia y precisa.

9. Explica por qué N-Reinas y laberinto son ejemplos naturales de backtracking.

 El **backtracking** (o búsqueda con retroceso) es una estrategia algorítmica que se usa para resolver problemas donde se debe encontrar una solución válida dentro de un conjunto enorme de opciones combinatorias, construyendo la respuesta **paso a paso** y descartando caminos apenas se detecta que no tienen salida.
   - **En N-Reinas** (NQueens.h): El problema consiste en colocar $N$ reinas sin que se ataquen. El algoritmo coloca la primera reina en la fila 0, columna 0, y avanza a la fila 1. Si en la fila actual una posición entra en conflicto con las reinas anteriores (verificado por conflictsWithAny), la descarta de inmediato. Si llega a una fila donde ninguna columna es válida, se da cuenta de que las decisiones anteriores fueron erróneas. El backtrack ocurre al sacar la reina de la fila anterior (solution.pop()) y moverla a la siguiente columna disponible para reintentar desde ahí
   - **En el Laberinto** (Maze.h): Para ir desde un inicio hasta un destino, el algoritmo elige una dirección (por ejemplo, EAST). Avanza celda por celda marcando el camino como ROUTE. Si topa con una pared o con un callejón sin salida donde todas las direcciones apuntan a NO_WAY, el algoritmo retrocede. Al hacer path.pop(), desanda el camino y marca la celda como BACKTRACKED para no volver a cometer el mismo error, regresando a la bifurcación anterior para probar una ruta alternativa.

10. Explica por qué la simulación bancaria no se modela bien con pila, pero sí con colas.

 La elección de la estructura de datos cambia drásticamente las reglas del negocio y el comportamiento del sistema que se intenta representar:

   - **Por qué NO con una Pila**: Si modeláramos las ventanillas del banco con pilas (Stack), el comportamiento sería sumamente injusto y destructivo para el negocio. El último cliente en llegar a la fila sería el primero en ser atendido (LIFO). Aquellos clientes que llegaron temprano quedarían atrapados al fondo de la pila, y mientras sigan llegando personas, su tiempo de espera tendería al infinito (inanición o starvation). Ningún sistema de atención real sobrevive bajo esta premisa.

   - **Por qué SÍ con Colas**: El servicio bancario se rige bajo el principio de equidad cronológica. Una cola (Queue) garantiza que el orden de atención respete estrictamente el orden de llegada (FIFO). En BankSimulation.h, esto permite medir con precisión métricas reales de rendimiento: el tiempo promedio de espera, cuántos clientes se acumulan en las horas pico y la eficiencia de las ventanillas al despachar a los clientes en el orden en que sacrificaron su tiempo al formarse.

11. Explica qué relación hay entre estructura auxiliar, estado parcial y correctitud.

   - **Estado Parcial:** Representa la instantánea o "fotografía" de la solución en un momento dado (por ejemplo, el vector con la posición de las primeras 3 reinas colocadas, o la ruta de celdas recorridas hasta la mitad del laberinto).

   - **Estructura Auxiliar:** Es el contenedor físico (la pila Stack o la cola Queue) que almacena y organiza de forma secuencial esos estados parciales o las decisiones pendientes del algoritmo.

   - **Correctitud:** Es la garantía matemática de que el algoritmo llegará a la solución correcta (si existe) o informará con certeza que no hay solución, sin quedarse atrapado en bucles infinitos.

 **La relación entre ellos:** La estructura auxiliar es la encargada de salvaguardar el estado parcial de manera inviolable. En problemas de búsqueda, si el algoritmo mete la pata y toma un camino inválido, la correctitud depende enteramente de que la estructura auxiliar (Stack) sea capaz de devolver el estado parcial previo exactamente como estaba antes del error. Si la estructura pierde información o altera el orden del estado parcial, el algoritmo pierde el hilo de dónde se encontraba, rompiendo la correctitud y fallando en resolver el problema.

12. Explica qué diferencia conceptual hay entre "resolver un problema" y "simular un proceso".

| Criterio | Resolver un problema | Simular un proceso |
| :--- | :--- | :--- | 
| Objetivo Principal | Encontrar una respuesta óptima o exacta que cumpla con restricciones lógicas o matemáticas rigurosas. | Replicar el comportamiento de un sistema real a lo largo del tiempo para estudiar su rendimiento y variabilidad. |
| El rol del Tiempo | El tiempo no forma parte de la solución. Solo importa la velocidad de cómputo del algoritmo (complejidad temporal). | El tiempo es una variable fundamental del modelo. El algoritmo avanza paso a paso (now++) emulando segundos, minutos o ciclos de reloj. |
| Naturaleza | Determinista o Combinatoria: La expresión 2 + 3 * 4 siempre debe dar 14. Las soluciones de N-Reinas son finitas y exactas. | Estocástica (Aleatoria): Depende de distribuciones de probabilidad (como en tu código, donde la llegada de clientes y sus tiempos de atención se definen mediante un generador std::mt19937). |
| Resultado final | Un valor único, un camino específico o un "Sí/No" rotundo. | Una colección de datos estadísticos o un historial de eventos (timeline) para analizar promedios, mínimos y máximos. |

#### Bloque 2 -Demostración y trazado guiado
1.  En demo_stack_queue.cpp, ¿qué parte de la salida deja más clara la diferencia entre tope y frente?

 - en pila(stack):stack .top() devuelve 9
 _ en cola(queue): queue .front() devuelve 10 

2. En demo_base_conversion.cpp, ¿qué observable permite afirmar que las versiones recursiva e iterativa producen la misma representación?

 Lo que permite afirmar que ambas versiones producen la misma representación es el valor de retorno (la cadena de caracteres) que se muestra en la consola para un mismo número de entrada y una misma base.
 En este caso, el observable directo es la salida estándar (std::cout). Si al ejecutar el programa ambos métodos imprimen exactamente el mismo número octal, se confirma la equivalencia funcional.

3. En demo_paren_rpn.cpp, ¿qué relación observas entre paréntesis balanceados, RPN y valor final?

  La relación entre estos tres elementos es de jerarquía y dependencia estructural. Para que una computadora pueda calcular el valor de una expresión compleja, debe seguir un proceso lógico donde cada paso garantiza la validez del siguiente.
  
4. En demo_nqueens.cpp, ¿qué significan solutions y checks, y por qué no miden lo mismo?
  - solutions (Soluciones): Es el número total de configuraciones válidas encontradas donde las N reinas están en el tablero sin atacarse entre sí. Para N=4, el valor de solutions será 2.

 - checks (Verificaciones): Es la cantidad de veces que el algoritmo tuvo que preguntar: "¿Es seguro poner una reina en esta posición específica?". Representa el esfuerzo computacional realizado.

 No miden lo mismo porque representan el éxito frente al intento. La relación entre ellos es una medida de la eficiencia del algoritmo.

5. En demo_maze.cpp, ¿qué muestra la secuencia de coordenadas sobre el camino encontrado?

 La secuencia de coordenadas es la representación vectorial del movimiento a través del laberinto. Al observar los pares (x,y) impresos, puedes extraer tres conclusiones fundamentales sobre la naturaleza del camino encontrado:
 1. Continuidad y Adyacencia
 2. Evitación de Obstáculos
 3. La Estrategia del Algoritmo (Orden de Exploración)

6. En demo_bank.cpp, ¿qué representa cada lista impresa en cada instante t?

 En la simulación, cada lista (representada entre corchetes []) representa el estado de una fila de espera (cola) en una ventanilla específica en un momento determinado del tiempo t.

7. En demo_capitulo4_panorama.cpp, ¿qué salida resume mejor la idea de que una misma semana reúne estructuras y aplicaciones?
 
 La salida que mejor resume la unión entre estructuras y aplicaciones es la combinación de los resultados de RPN/Valor y N-Reinas/Laberinto/Simulación.

  Expresion en RPN = 0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -
 Valor = 220
 Soluciones de N-Reinas(4) = 2

#### Bloque 3 - Pruebas públicas, pruebas internas y correctitud
1. ¿Qué operaciones mínimas valida la prueba pública para `Stack`?

  La prueba pública valida el ciclo de vida básico y el comportamiento LIFO del contenedor mediante:

   - **empty():** Verifica que inicialmente está vacía y que vuelve a estarlo al final.

   - **push(value):** Inserta elementos en la pila (**5** y luego **9**).

   - **top():** Inspecciona el elemento superior sin extraerlo (valida que sea **9**).

   - **pop():** Extrae elementos garantizando el orden inverso de inserción (primero sale **9**, luego **5**).

2. ¿Qué operaciones mínimas valida la prueba pública para `Queue`?

 Valida el comportamiento FIFO secuencial de la cola mediante:

   - **empty():** Revisa el estado de vacuidad inicial y final.

   - **enqueue(value):** Inserta tres elementos secuenciales (**1**, **2**, **3**).

   - **front():** Inspecciona el primer elemento en espera sin removerlo (valida que sea **1**).

   - **dequeue():** Extrae y retorna los elementos en el orden exacto en que llegaron (**1**, luego **2**, y finalmente **3**).

3. ¿Qué valida la prueba pública sobre conversión de base?

  Valida la equivalencia de resultados entre ambos enfoques de control: toma  el número decimal **12345**, lo convierte a base octal (base **8**) usando **toBaseRecursive** y **toBaseIterative**, y mediante un **assert** confirma que ambas estrategias producen exactamente la misma cadena de texto: **"30071"**.

4. ¿Qué valida la prueba pública sobre paréntesis balanceados?

 - Casos correctos: result1 (recursivo) valida paréntesis simples balanceados (a+(b*(c+d))). result2 (iterativo) valida el soporte combinado y anidamiento correcto de paréntesis, corchetes y llaves (a+(b*[c-{d/e}])).

 - Caso incorrecto: result3 (iterativo) valida que la función detecte el cruce inválido de símbolos (([)]), el cual tiene los caracteres correctos pero en un orden de cierre asimétrico.

5. ¿Qué valida la prueba pública sobre evaluación de expresiones y RPN?

 Somete al evaluador a una expresión aritmética compleja: "(0!+1)*2^(3!+4)-(5!-67-(8+9))". Valida:

   - **Conversión a Notación Posfija (RPN):** Que el orden de los tokens resultantes sea exactamente "0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -".

   - **Precisión Matemática:** Que la reducción de operadores unarios (factoriales !), potencias (^), agrupaciones y signos aritméticos de un valor flotante idéntico a 2012.0 (controlando la tolerancia de precisión con 1e-9).

6. ¿Qué valida la prueba pública sobre `NQueens`?

 Valida el cálculo combinatorio para el caso clásico de $N = 4$. Verifica que el algoritmo iterativo de backtracking encuentre exactamente el número de soluciones teóricas 
 **(queens.solutions == 2)** y que la longitud de la lista de tableros válidos devueltos 
 **(placements.size())** coincida con este número.

7. ¿Qué valida la prueba pública sobre `Maze`?

 Configura una cuadrícula de texto de 5 x 5 donde existe un camino despejado entre las coordenadas de inicio **(1, 1)** y destino **(3, 3)**. Valida que la función **findPath**:
   1. No devuelva una ruta vacía (**!path.empty()**).
   2. El punto de partida de la ruta coincida estrictamente con el origen solicitado (**path.front() == (1,1)**).
   3. El punto de llegada coincida estrictamente con el destino deseado (**path.back() == (3,3)**).

8. ¿Qué valida la prueba pública sobre `bestWindow` en la simulación bancaria?

  Prueba la lógica de la cola más corta. Modela un banco con 3 ventanillas: la ventanilla 0 tiene dos clientes en espera, la ventanilla 1 tiene un cliente, y la ventanilla 2 está completamente vacía (0 clientes). El **assert** valida que la función elija correctamente el índice 2 por ser la opción óptima con menor carga de trabajo.

9. ¿Qué casos adicionales cubre la prueba interna y no aparecen de forma explícita en la pública?

 El archivo **test_internal_week4.cpp** actúa como una batería de pruebas de robustez ("stress cases" y límites) que la pública no toca:

   - **Límites de Frontera:** Valida la conversión con el número **0** (**toBaseRecursive(0, 2) == "0"**).

   - **Manejo de Errores y Excepciones:**  Despara intencionalmente un fallo al intentar convertir a una base inválida (**base 1**), y verifica mediante un bloque **try-catch** que el sistema lance un error del tipo **std::invalid_argument**.

   - **Cadenas Vacías o sin Símbolos**: Valida que una cadena de texto plana sin paréntesis ("sin parentesis") sea procesada como balanceada (true).

   - **Paréntesis de Cierre Huérfanos**: Valida el caso donde hay cierres antes de aperturas (")()("), forzando un error de subdesbordamiento (underflow) en la pila que el algoritmo debe capturar devolviendo false.

   - **Laberinto sin Salida**: Modela una grilla donde el destino está completamente bloqueado por paredes (**#**), validando que **findPath** devuelva una ruta vacía de forma segura en lugar de ciclarse.

   - **Signos Unarios**: Verifica el procesamiento correcto del signo menos en números negativos al inicio de la expresión (**"-3+5"**).

10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad?

 Las pruebas unitarias (como los asserts) son comprobaciones puntuales de caja negra para un conjunto finito de datos de entrada. No reemplazan la fundamentación teórica por tres razones:
   1. **La Complejidad es Invisible para los Asserts:** Una prueba para $N=4$ reinas pasa en microsegundos tanto si el código tiene una complejidad de    O(2^N) como si tiene un error de diseño que lo degrada a O(N!). Las pruebas no miden cómo escala el algoritmo con datos masivos.
   2. **No Garantizan Invariantes de Estructura:** Un test puede pasar "de casualidad" debido a la suerte con una semilla aleatoria (**seed = 123U**), ocultando que bajo ciertas condiciones la estructura viola sus propiedades (por ejemplo, que la simulación bancaria corrompa la memoria si dos clientes llegan al mismo tiempo).
   3. **Falta de Demostración Formal:** Las pruebas confirman que el código funciona para los ejemplos dados, pero no explican por qué funciona ni demuestran que el estado interno se mantiene consistente en todas las transiciones lógicas del programa.

11. Da un ejemplo de un error conceptual que podría sobrevivir si solo se ejecutaran los casos mínimos.
 Imagina que en ExpressionEvaluator.h, al implementar la matriz de prioridades en OperatorPriority.h, cometes el error de asignar la misma prioridad y asociatividad al operador de suma (+) y al de potencia (^).

 Si ejecutas una prueba mínima o lineal como 3+4*2 (que solo evalúa suma contra multiplicación), la prueba pasará con éxito porque el error está oculto en otro operador. Incluso una expresión como 2^3+4 podría pasar si los operandos no fuerzan la ambigüedad. Sin embargo, en el momento en que el sistema real intente evaluar una expresión combinada como 2^3^2 o 5+2^3, el algoritmo romperá las reglas de la matemática e introducirá un error de cálculo masivo en producción. Las pruebas mínimas validan el "camino feliz", pero solo la comprensión profunda de las invariantes y los casos límite protegen contra fallos conceptuales.

#### Bloque 4 - Comparación recursivo vs iterativo

1. En conversión de base, ¿qué papel juegan el cociente, el residuo y la pila?

 - **El residuo (n % base):** Representa el valor del dígito de la nueva base que se acaba de extraer. El detalle clave es que las divisiones nos entregan estos residuos en orden de menor a mayor significancia (primero las unidades, luego las decenas de la nueva base, etc.).

 - **El cociente (n / base):** Actúa como el estado de control. Es la parte entera que queda tras la división y sirve para alimentar la siguiente iteración o llamada recursiva. Cuando el cociente llega a 0, significa que ya extrajimos hasta el último dígito posible.

 - **La pila (Stack<char>& stack):** Funciona como un mecanismo de inversión temporal. Dado que los residuos se calculan al revés de cómo se leen o escriben matemáticamente, la pila los retiene momentáneamente para poder revertir su orden al final.

2. ¿Por qué los residuos se apilan antes de formar la cadena final?

  Si convirtiéramos el número decimal $11$ a binario (base 2) y simplemente fuéramos concatenando los residuos en un string conforme van saliendo de las operaciones:
    1. 11/ 2 = 5 residuo 1 (Bit menos significativo/Unidades)
    2. 5/2 =2, residuo 1
    3. 2/2 =1, residuo 0
    4. 1/2 =0, residuo 1(Bit mas significativo)
  
     Si los unimos tal como salen. Obtendriamos "1101", lo cual equivale al decimal 13 en binario(¡incorrecto!).El resultado matematico real debe ser 1011(sub2).
     Al meterlos a la pila (stack.push), el bit de las unidades (1) se va al fondo, y el bit más significativo (1) queda hasta arriba en el top(). Al ejecutar popAll(), la naturaleza LIFO de la pila revierte por completo la secuencia, entregándonos los caracteres en el orden de lectura correcto (de izquierda a derecha, de mayor a menor significancia).

3. ¿Qué cambia entre dejar que el call stack haga el trabajo y manejar una pila explícita?

   - **En convertRecursive (Call Stack implícito):** Tú le delegas el flujo de control al sistema operativo. Cada vez que la función se llama a sí misma, la computadora detiene la ejecución actual y guarda un "registro de activación" con las variables locales en la memoria del sistema. La pila explícita de caracteres que pasas por referencia (stack) solo se va llenando a medida que la recursión va "regresando" de las llamadas.

   - **En convertIterative (Pila explícita):** El control del proceso es plano y directo mediante un bucle while. Toda la lógica corre dentro del mismo entorno de ejecución. No hay llamadas extras a funciones ni sobrecarga en la memoria del sistema (cero riesgo de Stack Overflow). Tú controlas activamente el llenado de la pila local en cada paso del ciclo.

4. En `parenRecursive`, ¿qué idea intenta capturar `divideParentheses`?

 **divideParentheses** intenta modelar la propiedad de anidación profunda mediante la estrategia de Divide y Vencerás. Su objetivo principal es encontrar el paréntesis de cierre que se encuentra al mismo nivel sintáctico que el paréntesis de apertura de la izquierda (lo).

 Para lograrlo, usa una variable de control llamada crc (un contador de balanceo):

   - Incrementa **crc** cuando ve un **(** y lo decrementa con un **)**.

   - Cuando **crc** vuelve a ser **0**, el algoritmo sabe que ha localizado la frontera exacta (mi) donde termina el bloque actual.

  Esto le permite dividir el problema en dos subproblemas independientes: validar lo que está estrictamente dentro de ese bloque (**lo + 1** hasta **mi - 1**) y validar lo que viene después de él (**mi + 1** hasta **hi**).

5. ¿Qué limitación conceptual tiene la versión recursiva mostrada frente a la iterativa cuando aparecen `[]` y `{}`?

 La versión recursiva **parenRecursive** mostrada en el archivo está diseñada exclusivamente para un solo tipo de carácter (( y )).

 Si intentáramos extenderla directamente para soportar llaves y corchetes, colapsaría conceptualmente. ¿Por qué? Porque **divideParentheses** solo rastrea la profundidad contando aperturas y cierres genéricos, pero no tiene memoria histórica para validar si el carácter de cierre coincide en tipo con el de apertura.

 Para que la recursión pudiera validar expresiones híbridas como **{[()]}**, tendría que validar en cada subdivisión qué tipo de símbolo abrió la frontera, lo que volvería al código sumamente complejo, ineficiente y propenso a errores al intentar segmentar los límites de la cadena.

6. En `parenIterative`, ¿por qué un cierre incorrecto puede detectarse apenas aparece?

 La versión iterativa tiene una ventaja fundamental: posee memoria de emparejamiento inmediato gracias a la pila.

   case ']':
       if (stack.empty() || stack.pop() != '[') {
           return false;
       }
       break;

  Cuando el bucle recorre la cadena de izquierda a derecha y se topa con un carácter de cierre (por ejemplo, ]), no necesita analizar el resto de la cadena ni calcular subdivisiones. Debido a la regla de simetría, el carácter que está en el top() de la pila tiene que ser forzosamente su apertura correspondiente ([). Si la pila está vacía (cierre huérfano) o si al hacer pop() sale un carácter diferente (como { o (), el invariante de balanceo se rompe en ese mismísimo instante y la función aborta devolviendo **false**.

7. Compara ambas parejas de funciones: ¿en cuál caso la versión iterativa te parece más natural y en cuál la recursiva resulta más expresiva?

 - **Conversión de Base:** La versión iterativa (**convertIterative**) resulta mucho más natural y eficiente. El problema de dividir un número sucesivamente hasta llegar a cero es intrínsecamente un bucle. Forzar una recursión aquí añade una sobrecarga innecesaria a la pila de llamadas del sistema para resolver algo que un simple while resuelve de forma limpia.

 - **Verificación de Paréntesis:** La versión iterativa con pila (**parenIterative**) es inmensamente superior tanto en claridad como en expresividad. Captura de forma elegante la esencia del problema: "guardo lo que abro, lo borro cuando lo cierro". Por el contrario, la versión recursiva (**parenRecursive**), con sus funciones auxiliares para recortar (**trimParentheses**) y dividir (**divideParentheses**), resulta artificial, difícil de leer y muy costosa en tiempo debido a las múltiples pasadas que hace sobre los índices de la cadena de texto.

#### Bloque 5 - Evaluación de expresiones y prioridad de operadores

1. Explica qué información guarda `EvaluationResult`.

 EvaluationResult: guarda el value (valor numérico final, tipo double) y la rpn (representación en notación polaca inversa, std::string). Permite devolver simultáneamente resultado y trazado legible de la evaluación.

2. Explica por qué primero se eliminan espacios.

 Eliminación de espacios: removeSpaces simplifica el análisis carácter a carácter: evita ramas por espacios, facilita indexado y lookahead, y asegura que el lexer/parseador vea solo tokens relevantes.
3. Explica cómo se detecta el signo menos unario.
 
 Detección de menos unario: isUnaryMinus comprueba que el carácter es '-', que el siguiente carácter existe y es dígito o '.', y que el anterior es inicio de cadena o un operador/**(**; así distingue -3 (unario) de a-3 (binario).

4. Explica por qué el factorial se trata como operador unario y qué restricción impone el código.

 Factorial como operador unario y su restricción: el factorial ('!') es operador postfix que toma un único operando; el código trata ! como unario y, antes de calcular, exige que el operando sea (prácticamente) entero: redondea y comprueba diferencia < 1e-9; además factorialInt lanza error si el entero es negativo.

5. Explica cómo la RPN se va construyendo durante la evaluación y no al final.

 RPN construida durante la evaluación: la cadena RPN se va ampliando a medida que se leen operandos (appendRpn al leer números) y cada vez que se desapila un operador (appendRpn cuando se aplica un operador). No se reconstruye al final: se registra el orden real de reducción mientras se evalúa.

6. Explica qué significa la relación entre operador del tope y símbolo actual.

 Significado de la relación entre operador tope y símbolo actual: orderBetween usa la tabla de precedencias (pri) para devolver <, > o =. < significa "empujar" el símbolo actual sobre la pila de operadores; > significa "desapilar y evaluar" el operador del tope; = indica emparejamiento (p. ej. ( con )) o fin de expresión.


7. Explica por qué una expresión mal formada debe terminar en error y no en un valor arbitrario.

 Por qué una expresión mal formada debe lanzar error: aceptar silenciosamente un resultado arbitrario oculta fallos semánticos/sintácticos. El código detecta y lanza **runtime_error** en casos como tokens inesperados, operadores sin operandos suficientes, división por cero o al final no reducir a un único operando; esto garantiza corrección y evita resultados engañosos.

 8. ¿Qué ventaja conceptual tiene obtener a la vez el valor y la RPN?

 Ventaja de obtener valor y RPN a la vez: eficiencia (un solo pase para ambos), trazabilidad (la RPN sirve para depuración y verificación), y reutilización (la RPN puede re-evaluarse o mostrarse al usuario). Facilita comprobar y explicar por qué se obtuvo ese valor.

#### Bloque 6 - Backtracking explícito: N-Reinas y laberinto

1. En `Queen`, ¿qué significa que dos reinas entren en conflicto?

 En Queen: que dos reinas entren en conflicto significa que ocupan la misma fila (x), la misma columna (y) o la misma diagonal (mismo x+y o mismo x-y). El operador == implementa esa comprobación.

2. En `NQueens`, ¿qué representa exactamente la pila `solution`?
 
 En NQueens: la pila solution contiene la colocación parcial actual —una Queen por fila— desde la fila 0 hasta la fila última colocada; la cima es la última reina añadida (estado parcial del backtracking).

3. ¿Qué significa avanzar en columna dentro de una fila y cuándo toca retroceder?

 "Avanzar en columna dentro de una fila" significa incrementar y para intentar otra columna en la misma fila x. Se retrocede cuando no quedan columnas válidas en la fila actual (o se alcanza y>=n): se hace pop() de la pila para volver a la fila anterior y probar la siguiente columna allí.

4. ¿Por qué `checks` es una métrica útil para analizar la búsqueda?

  checks cuenta cuántas comparaciones de conflicto se hacen (cada vez que se comprueba candidate == q). Es útil porque mide el trabajo de búsqueda/prueba (coste de exploración y poda) independientemente del número de soluciones encontradas.

5. ¿Qué cambia cuando `collectPlacements` vale `false`?

  Si collectPlacements == false se omite la construcción/almacenamiento de los vectores placement, por lo que se ahorra memoria y tiempo; el algoritmo sigue contando solutions y checks pero no devuelve las colocaciones concretas.

6. En `Maze`, ¿qué representa el estado `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL`?

  En **Maze**:

 - **AVAILABLE:** celda libre y no explorada.
 - **ROUTE:** celda marcada como parte del camino actual (ruta en construcción).
 - **BACKTRACKED:** celda explorada que se descartó porque no conduce al objetivo.
 - **WALL:** celda impracticable (obstáculo).

7. ¿Qué información codifican `incoming` y `outgoing`?

 incoming codifica la dirección desde la que se entró en la celda (para poder saber la procedencia); outgoing codifica la siguiente dirección a probar/desplazarse desde esa celda (o la dirección por la que se salió).

8. ¿Por qué el algoritmo del laberinto marca y desmarca estado en lugar de solo "moverse"?

 El algoritmo marca/desmarca estados para evitar ciclos, recordar qué celdas ya fueron probadas y distinguir rutas válidas de callejones sin salida. Esa marcación permite la lógica iterativa con pila: saber cuándo retroceder y qué celdas ya fueron descartadas, algo que no se logra solo "moviendo" la posición actual.

9. Compara N-Reinas y laberinto: ¿qué comparten como problemas de búsqueda y qué cambia en la representación del estado?
 
 Comparación N-Queens vs Maze:

 - Similitudes: ambos son problemas de búsqueda/backtracking que exploran un espacio de estados, usan una pila o camino parcial, y retroceden al hallar calles sin salida; ambos aplican poda para evitar explorar estados inútiles.
 - Diferencias en representación de estado: N-Queens representa combinaciones (una reina por fila; estado = lista de colocaciones, conflicto por pares) y la vecindad es "poner una reina en otra columna de la siguiente fila". Maze representa posiciones espaciales con estados por celda (**AVAILABLE/ROUTE/BACKTRACKED/WALL**) y direcciones (**incoming/outgoing**); la vecindad son los vecinos cardinales. Además la poda en **N-Queens** surge de comprobaciones de conflicto (filtrado lógico), mientras que en **Maze** surge de marcar celdas visitadas y evitar volver sobre ellas (poda por recorrido).

#### Bloque 7 - Simulación bancaria y experimentación con colas

1. ¿Qué representa cada `Queue<Customer>` dentro del vector `windows`?

  Cada **Queue<Customer>** en el vector **windows** representa la fila de espera de una ventanilla del banco. Es decir, cada ventanilla tiene su propia cola de clientes esperando ser atendidos.

2. ¿Qué criterio usa `bestWindow` y qué decisión toma cuando hay empate?

  **bestWindow** elige la ventanilla con la cola más corta comparando **windows[i].size()**. Si hay empate se queda con la primera ventanilla que aparece con el tamaño mínimo, porque **opt** solo cambia cuando encuentra una cola estrictamente más pequeña.


3. ¿Qué significa que la simulación use una semilla (`seed`)?

 La semilla (seed) fija el generador pseudoaleatorio std::mt19937, por lo que la secuencia de llegadas y tiempos de servicio es reproducible. Con la misma semilla y mismos   parámetros, la simulación produce exactamente el mismo resultado.

4. ¿Qué relación debe cumplirse entre `totalArrivals` y `totalServed`, y por qué?

 Debe cumplirse totalArrivals >= totalServed. Cada cliente atendido primero debe haber llegado, y la simulación no puede servir más clientes que los que entraron al sistema.

5. ¿Qué representa la línea de tiempo (`timeline`) en el resultado?

 La timeline es el historial de estados de la simulación en cada instante de tiempo now. Cada BankSimulationStep guarda el instante y las colas actuales de cada ventanilla, representadas como tiempos de servicio restantes de los clientes en la cola.

6. ¿Por qué esta aplicación necesita colas y no pilas?

 Necesita colas porque el orden de servicio es FIFO: el primer cliente que llega a una ventanilla es el primero en ser atendido. Una pila sería LIFO, lo que significaría atender al último cliente llegado antes que los anteriores, y eso no refleja el comportamiento de una fila de banco.

7. ¿Qué simplificación del mundo real introduce este simulador?

 El simulador simplifica la realidad al usar:

 - llegadas aleatorias independientes con probabilidad fija arrival(rng) != 0,
 - tiempos de servicio aleatorios sencillos,
 - una sola unidad de servicio por paso de tiempo,
 - y no considera clientes que cambian de fila, prioridades, llegadas simultáneas complejas ni tiempos de llegada exactos.

8. ¿Qué cambiaría si la política ya no fuera "cola más corta" sino otra?
 Si la política fuera otra, cambiaría cómo se elige la ventanilla para cada nuevo cliente. Por ejemplo:

   - “menos clientes atendidos” podría buscar la cola con menos tiempo total restante,
   - “round robin” podría asignar en orden cíclico,
   - “aleatoria” elegiría una ventanilla al azar.
    Eso modificaría la distribución de carga entre ventanillas y el comportamiento de congestión final.



