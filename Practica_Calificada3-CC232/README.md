# Práctica Calificada 3 - CC232

## Declaración de Autoría

- **Estudiante:** Joel Gustavo Carhuarica Aguilar
- **Código:** 20222270I
- **Problema asignado**: AtCoder ABC241 D - Sequence Query
- **Enlace Oficial:** https://atcoder.jp/contests/abc241/tasks/abc241_d 
 
## Referencia oficial

CSV oficial: https://github.com/joelcarhuaricaa-sys/Repositorio_Actividades_Semanas-/tree/main/Practica_Calificada3-CC232 

## Relación con Semanas 4-6

- **Semana principal:** Semana 6 (Estructuras de datos probabilísticas y aumentadas: Treaps y aplicaciones de orden estadístico dinámico).
- **Estructura usada:** Treap Aumentado con soporte explícito para multi-conjuntos (conteo de duplicados mediante frecuencias locales) y campos acumulativos de pesos en subárboles.
- **Estructura de la librería `cc232` relacionada:** Variante indexada y balanceada de un Árbol Binario de Búsqueda (BST) aumentado con prioridades de Heap probabilístico para garantizar el balanceo autorregulado.

## Resumen de la solución

La idea central consiste en resolver el problema de mantener una secuencia dinámica de números de manera ordenada y eficiente bajo tres tipos de consultas. Para evitar el uso ineficiente de un arreglo ordenado o de estructuras estándar que no permitan indexación posicional logarítmica, se implementa un **Treap Aumentado**. 

Cada nodo en este Treap almacena de manera explícita la clave (`key`), una prioridad aleatoria única (`priority`), la frecuencia de la clave para el manejo nativo de duplicados (`frequency`) y el tamaño total acumulado de su subárbol (`subtree_size`). La estrategia de solución ante las tres consultas distribuye el trabajo de la siguiente manera:
1. **Consulta Tipo 1:** Se inserta el elemento bajando por las ramas del BST. Si la clave ya existe, únicamente se incrementa su `frequency`. El balanceo se preserva mediante rotaciones hacia arriba (`rotateLeft` y `rotateRight`) de acuerdo con la prioridad.
2. **Consulta Tipo 2:** Se determina el número de elementos menores o iguales a $x$ usando un método de conteo binario acumulativo (`countLessOrEqual`). Si la cantidad de elementos disponibles es menor que $k$, se retorna `-1`. En caso contrario, se busca el elemento correspondiente usando su posición relativa en base cero calculada como `total_le - k` a través del selector estadístico `findKth`.
3. **Consulta Tipo 3:** Se cuenta la cantidad de elementos estrictamente menores que $x$ usando `countLess`. A partir de este valor se proyecta el índice objetivo hacia adelante como `total_less + k - 1`. Si el índice calculado excede el tamaño total actual del árbol, se retorna `-1`. En caso contrario, se extrae el valor exacto de la clave empleando `findKth`.

Esta estructura es idónea porque permite localizar cotas, calcular distribuciones de rangos y realizar búsquedas por orden estadístico dinámico de manera descendente en tiempo logarítmico, satisfaciendo las estrictas restricciones de tiempo del juez sin caer en sobrecostos lineales.

## Invariante principal

Después de cada operación que modifique la estructura (inserción o rotaciones), se asegura y preserva de forma estricta la siguiente propiedad geométrica y de pesos en cada nodo $u$:
- **Propiedad BST:** Para todo nodo $u$, las llaves del subárbol izquierdo son menores que la de $u$, y las llaves del subárbol derecho son mayores que la de $u$.
- **Propiedad Heap:** Para todo nodo $u$ con padre válido, se cumple de manera probabilística que `u->parent->priority <= u->priority` (Min-Heap).
- **Ecuación Estructural de Aumento:** El tamaño del subárbol está determinado por la suma exacta de sus frecuencias internas más los tamaños reportados por sus hijos directos

## 📊 Estructura del Proyecto
El proyecto utiliza una arquitectura limpia e incremental dividida de la siguiente manera:
- `include/`: Contiene la plantilla del Treap aumentado (`Treap.h`) y la definición de la clase de negocio (`Solution.h`).
- `src/`: Implementación de queries de despachado lógico (`Solution.cpp`).
- `demos/`: Código fuente de la consola principal interactiva (`main.cpp`).
- `tests/`: Suite unitaria automatizada (`test_main.cpp`).
- `benchmark/`: Pruebas empíricas de estrés temporal con chrono (`main_benchmark.cpp`).
- `resultados/`: Almacén de reportes reproducibles de control de calidad.

## Complejidad

- Tiempo por operación:

     - Inserción: O de logaritmo de N promedio.
     - Conteo de rangos: O de logaritmo de N promedio.
     - Orden estadístico: O de logaritmo de N promedio.

- Tiempo total: O de Q veces logaritmo de N para procesar las Q consultas de la entrada.

- Espacio: O de N en memoria dinámica, donde N es la cantidad de elementos únicos almacenados en el árbol.

##  Archivos relevantes

Indica qué contiene cada carpeta o archivo importante:

- include/Treap.h: Archivo de cabecera que contiene la definición de la clase plantilla Treap, sus estructuras de nodos aumentados, operaciones de rotación, inserción multiconjunto y métodos de orden estadístico.

- include/Solution.h: Declaración de la clase de negocio Solution que gestiona e interconecta las interfaces de consulta expuestas al juez.

- src/Solution.cpp: Implementación de la lógica de negocio para la resolución matemática de las tres variantes de consultas.

- tests/test_main.cpp: Suite de pruebas unitarias automatizadas con aserciones estáticas obligatorias para el control de regresión lógica.

- demos/main.cpp: Código del programa principal interactivo optimizado para flujos rápidos de entrada y salida estándar.

- benchmark/main_benchmark.cpp: Módulo de pruebas empíricas de esfuerzo temporal para medir la eficiencia del Treap ante operaciones masivas.

- docs/respuestas_obligatorias.md: Documento con las respuestas detalladas del cuestionario conceptual y de diseño de la práctica.

- docs/bitacora.md: Historial y registro cronológico del desarrollo del proyecto.

- resultados/: Directorio físico que almacena los archivos de texto con las evidencias recolectadas y aprobadas de las ejecuciones del programa.

##  Limpieza del repositorio

El repositorio no debe versionar builds, ejecutables ni archivos generados. Para ello se ha configurado el archivo gitignore encargado de filtrar y omitir archivos temporales del sistema, carpetas de compilación y binarios.

## Comando sugerido para verificar archivos generados versionados:

 ```C++
 git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"
 ```
 
### Compilación

 ```bash
 cmake -S . -B build
 cmake --build build
 ```
 
### Ejecución

 ```bash
 ./build/nombre_del_programa
 ```

### Pruebas

1. Caso mínimo

    - entrada usada:
          1
          1 5

    - salida esperada: No genera salida por consola, inicializa de forma interna el árbol.

    - salida obtenida: Estructura interna inicializada correctamente con raíz única.

    - qué aspecto valida: Valida la correcta construcción del nodo raíz, asignación de prioridades iniciales y establecimiento base del invariante del tamaño de subárbol en uno en un entorno elemental.

2. Caso con estructura vacía, frontera o ausencia de respuesta

    - entrada usada:
          2
          2 10 1
          3 10 1

    - salida esperada:
         -1
         -1

    - salida obtenida:
         -1
         -1

    - qué aspecto valida: Valida la tolerancia a fallos en el software y el control seguro contra punteros nulos cuando se invoca un orden estadístico posicional sobre un árbol que no contiene datos, interceptando los rangos de manera limpia sin provocar caídas de memoria.   

3. Caso con duplicados o empates

    - entrada usada:
          5
          1 20
          1 20
          1 20
          1 30
          2 20 2

    - salida esperada:
          20

    - salida obtenida:
          20

    - qué aspecto valida: Valida la robustez y efectividad del campo de frecuencia en la inserción multiconjunto. Al ingresar tres llaves idénticas con valor 20, comprueba que no se bifurquen nodos duplicados de forma innecesaria en el árbol y que el recorrido devuelva de forma exacta la clave empatada.

4. Caso extremo pequeño verificable manualmente

   - entrada usada:
          5
          1 20
          1 20
          1 20
          1 30
          3 20 4

    - salida esperada:
          30

    - salida obtenida:
          30

    - qué aspecto valida: Valida la correcta aplicación aritmética del recorrido de saltos en subárboles mayores relativos a un valor dado. Comprueba manualmente que existiendo tres elementos de valor 20, el cuarto elemento más pequeño mayor o igual que 20 es correctamente identificado en el subárbol derecho como el valor 30.

5. Caso comparado contra una solución ingenua, si aplica

    - entrada usada: Inserción secuencial masiva aleatoria de 100,000 elementos seguida de una batería combinada de 100,000 consultas posicionales ejecutadas a través del ejecutable de rendimiento.

    - salida esperada: Tiempo total de ejecución inferior a la ventana crítica de un segundo de procesamiento dinámico, demostrando un comportamiento asintótico eficiente.

    - salida obtenida: Reporte exitoso por consola marcando un tiempo de inserción masiva de 48 milisegundos y un tiempo de procesamiento de consultas de 92 milisegundos.

    - qué aspecto valida: Valida el escalamiento logarítmico frente a una solución ingenua basada en vectores dinámicos ordenados secuencialmente. Mientras que la solución ingenua habría requerido tiempos de cómputo cuadráticos provocando parálisis por exceso de tiempo, la solución estructurada con el Treap Aumentado despacha el lote de estrés completo en pocos milisegundos.

