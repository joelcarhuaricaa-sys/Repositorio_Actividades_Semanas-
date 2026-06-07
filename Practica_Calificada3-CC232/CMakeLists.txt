cmake_minimum_required(VERSION 3.10)
project(Practica_Calificada3_CC232)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
include_directories(include)

set(COMMON_SOURCES src/Solution.cpp)

add_executable(demo_pc3 demos/main.cpp ${COMMON_SOURCES})
add_executable(benchmark_pc3 benchmark/main_benchmark.cpp ${COMMON_SOURCES})
add_executable(tests_pc3 tests/test_main.cpp ${COMMON_SOURCES})

add_test(NAME OperacionesTreap COMMAND tests_pc3)