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