#include <iostream>
#include <cassert>
#include "Solution.h"

void test_caso_vacio_y_ausencia() {
    Solution sol;
    // Estructura vacía debe responder -1 de manera segura
    assert(sol.processQuery2(10, 1) == -1);
    assert(sol.processQuery3(10, 1) == -1);
    std::cout << "[PASÓ] Prueba de Estructura Vacía e Inexistencia." << std::endl;
}

void test_caso_duplicados_y_ranking() {
    Solution sol;
    sol.processQuery1(20);
    sol.processQuery1(20);
    sol.processQuery1(20);
    sol.processQuery1(30);

    // Menores o iguales a 20 hay tres elementos '20'. El 1ero, 2do y 3er más grande deben ser 20.
    assert(sol.processQuery2(20, 1) == 20);
    assert(sol.processQuery2(20, 2) == 20);
    assert(sol.processQuery2(20, 3) == 20);
    assert(sol.processQuery2(20, 4) == -1); // No hay 4 elementos

    // Mayores o iguales a 20: el 4to más pequeño debe ser 30
    assert(sol.processQuery3(20, 4) == 30);
    std::cout << "[PASÓ] Prueba de Elementos Duplicados y Concurrencia." << std::endl;
}

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

    std::cout << "[PASÓ] Prueba Avanzada de Duplicados y Saltos de Nodos" << std::endl;

} 

int main() {
    std::cout << "Ejecutando Suite de Verificación Obligatoria" << std::endl;
    test_caso_vacio_y_ausencia();
    test_caso_duplicados_y_ranking();
    test_caso_duplicados_complejo();
    std::cout << "Todas las pruebas unitarias pasaron con éxito." << std::endl;
    return 0;
}