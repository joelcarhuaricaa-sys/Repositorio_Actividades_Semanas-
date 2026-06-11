# Bitácora de Desarrollo - PC3

## Día 1
- **Problema trabajado:** Andamiaje inicial del proyecto y resolución del bloque conceptual básico.
- **Estructura:** Configuración del script modular de construcción automatizada.
- **Errores:** Ninguno en esta etapa inicial.

## Dia 2
- **Problema trabajado:** Modelado estructural de punteros del Treap.
- **Estructura:** Implementación matemática de balanceo a través de rotaciones directas (`rotateLeft`/`rotateRight`).
- **Errores:** Se corrigió un reordenamiento de punteros de asignación de padres que causaba ciclos infinitos.

## Día 3
- **Problema trabajado:** Desarrollo del motor algorítmico posicional del Treap.
- **Estructura:** Inyección de consultas acumulativas binarias e indexación estadística K-th.
- **Errores:** Se ajustó la indexación base $0$ en la resta de frecuencias para prevenir desbordamientos posicionales

## Día 4
- **Problema trabajado:** Interfaz funcional para AtCoder y optimización de flujos rápidos de I/O.
- **Estructura:** Construcción del despachador condicional en `main.cpp`.
- **Errores:** Ninguno, integración limpia entre la lógica del Treap y el solucionador.

## Día 5
- **Problema trabajado:** Cierre de la documentación técnica final, incorporación de reportes reproducibles y validación total del cuestionario.
- **Estructura:** Pipeline completado al 100% libre de binarios.

## Dia 6
- **Problema trabajado:** Cambiamos el countLess , countLessOrEqual y findKth por findMaxLessOrEqual, findMinGreaterOrEqual, getPredecessor y getSuccessor . (del Treap.h)
Para el Solution.cpp pasamos de una estrategia basada en "calcular un índice numérico global y buscar a ciegas" (findKth) a una estrategia basada en "buscar el nodo frontera y caminar hacia los lados usando punteros" (getPredecessor / getSuccessor).
En test_main.cpp lo que hice fue agregar una nueva función llamada test_caso_duplicados_complejo()
-  **Estructura y Cambios importantes:**Para el Treap.h 
 ```C++
 // Encuentra el nodo con la clave más grande que sea <= x
 Node* findMaxLessOrEqual(const T& x) const {
    Node* curr = root_;
    Node* res = nullptr;
    while (curr) {
        if (curr->key <= x) {
            res = curr; // Candidato viable, intentamos buscar uno más grande a la derecha
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return res;
 }

 // Encuentra el nodo con la clave más pequeña que sea >= x
 Node* findMinGreaterOrEqual(const T& x) const {
    Node* curr = root_;
    Node* res = nullptr;
    while (curr) {
        if (curr->key >= x) {
            res = curr; // Candidato viable, intentamos buscar uno más chico a la izquierda
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return res;
 }

 // Devuelve el nodo predecesor en orden simétrico (inorder)
 Node* getPredecessor(Node* u) const {
    if (!u) return nullptr;
    if (u->left) {
        Node* curr = u->left;
        while (curr->right) curr = curr->right;
        return curr;
    }
    Node* p = u->parent;
    while (p && u == p->left) {
        u = p;
        p = p->parent;
    }
    return p;
 }

 // Devuelve el nodo sucesor en orden simétrico (inorder)
 Node* getSuccessor(Node* u) const {
    if (!u) return nullptr;
    if (u->right) {
        Node* curr = u->right;
        while (curr->left) curr = curr->left;
        return curr;
    }
    Node* p = u->parent;
    while (p && u == p->right) {
        u = p;
        p = p->parent;
    }
    return p;
 }
```
Para el Solution.cpp:
 En la Query 2
 ```C++
 auto* curr = tree.findMaxLessOrEqual(x);
 if (!curr) return -1;

 while (curr) {
    if (k <= curr->frequency) return curr->key;
    k -= curr->frequency;
    curr = tree.getPredecessor(curr);
 }
 return -1;
 ```
 En la Query 3
 ```C++
 auto* curr = tree.findMinGreaterOrEqual(x);
 if (!curr) return -1;

 while (curr) {
    if (k <= curr->frequency) return curr->key;
    k -= curr->frequency;
    curr = tree.getSuccessor(curr);
 }
 return -1;
 ```
 Y para el test_main.cpp :
 ```C++
 void test_caso_duplicados_complejo() {
    Solution sol;
    sol.processQuery1(10);
    sol.processQuery1(20);
    sol.processQuery1(20); 
    sol.processQuery1(20); 
    sol.processQuery1(30);

    // Query 2: Menores o iguales a 25, ordenados de mayor a menor: [20, 20, 20, 10]
    assert(sol.processQuery2(25, 1) == 20);
    assert(sol.processQuery2(25, 2) == 20);
    assert(sol.processQuery2(25, 3) == 20);
    assert(sol.processQuery2(25, 4) == 10);
    assert(sol.processQuery2(25, 5) == -1);

    // Query 3: Mayores o iguales a 15, ordenados de menor a mayor: [20, 20, 20, 30]
    assert(sol.processQuery3(15, 1) == 20);
    assert(sol.processQuery3(15, 2) == 20);
    assert(sol.processQuery3(15, 3) == 20);
    assert(sol.processQuery3(15, 4) == 30);
    assert(sol.processQuery3(15, 5) == -1);
    
    std::cout << "[PASÓ] Prueba Avanzada de Duplicados y Saltos de Nodos." << std::endl;
 }
 ```
 - **Errores:** Ninguno, integración limpia entre la lógica del Treap, el Solution.cpp y el test_main.cpp .
