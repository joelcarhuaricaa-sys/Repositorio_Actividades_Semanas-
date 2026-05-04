### Actividad4_Semana4
#### Bloque 1 - Núcleo conceptual de la semana

Revisa:

    1. Semana4/README.md
    Semana4/include/Stack.h
    Semana4/include/Queue.h
    Semana4/include/BaseConversion.h
    Semana4/include/Parentheses.h
    Semana4/include/ExpressionEvaluator.h
    Semana4/include/NQueens.h
    Semana4/include/Maze.h
    Semana4/include/BankSimulation.h
    Capítulo 4 de Deng.

Responde:

    Explica con tus palabras la diferencia entre acceso LIFO y acceso FIFO.
    Explica por qué Stack resuelve naturalmente problemas donde importa "lo último pendiente".
    Explica por qué Queue modela naturalmente procesos de espera y atención.
    Explica qué significa reemplazar recursión implícita por una estructura explícita.
    Explica qué información mínima debe guardarse para que una pila permita reconstruir una solución parcial.
    Compara la conversión de base recursiva e iterativa: ¿qué comparten y qué cambia en el control del proceso?
    Explica por qué la verificación iterativa de paréntesis necesita almacenar aperturas pendientes.
    Explica por qué el evaluador de expresiones necesita dos pilas y no una sola.
    Explica por qué N-Reinas y laberinto son ejemplos naturales de backtracking.
    Explica por qué la simulación bancaria no se modela bien con pila, pero sí con colas.
    Explica qué relación hay entre estructura auxiliar, estado parcial y correctitud.
    Explica qué diferencia conceptual hay entre "resolver un problema" y "simular un proceso".
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