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

int main() {
    std::cout << "Ejecutando Suite de Verificación Obligatoria..." << std::endl;
    test_caso_vacio_y_ausencia();
    test_caso_duplicados_y_ranking();
    std::cout << "Todas las pruebas unitarias pasaron con éxito." << std::endl;
    return 0;
}