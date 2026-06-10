#include <iostream>
#include <chrono>
#include <random>
#include "Solution.h"

int main() {
    Solution sol;
    int operaciones = 100000;
    std::mt19937 rng(1337);
    std::uniform_int_distribution<long long> dist(1, 1000000);

    std::cout << "   BENCHMARK DE RENDIMIENTO: TREAP PC3     " << std::endl;

    // 1. Tiempo de Inserción Masiva con Duplicados Aleatorios
    auto start_ins = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operaciones; ++i) {
        sol.processQuery1(dist(rng));
    }
    auto end_ins = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_ins = end_ins - start_ins;

    // 2. Tiempo de Consultas Cruzadas de Orden Estadístico K-th
    auto start_query = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operaciones; ++i) {
        sol.processQuery2(dist(rng), 5);
        sol.processQuery3(dist(rng), 5);
    }
    auto end_query = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_query = end_query - start_query;

    std::cout << "Métricas registradas para " << operaciones << " operaciones:" << std::endl;
    std::cout << " -> Tiempo total de Inserción: " << time_ins.count() << " ms" << std::endl;
    std::cout << " -> Tiempo total de Consultas K-th: " << time_query.count() << " ms" << std::endl;

    return 0;
}