#include "Solution.h"

void Solution::processQuery1(long long x) {
    tree.add(x);
}

long long Solution::processQuery2(long long x, int k) {
    //buscamos el nodo de partida(el mas grande que sea <=x)
    auto* curr = tree.findMaxLessOrEqual(x);
    if (!curr) return -1;
    
    //Avanzamos hacia atras a traves de los nodos de los predecesores
    while (curr) {
        if (k <= curr->frequency) {
            return curr->key; // El K-ésimo elemento está contenido en este nodo
        }
        k -= curr->frequency;
        curr = tree.getPredecessor(curr);
    }
    return -1; // No se encontraron suficientes elementos
}

long long Solution::processQuery3(long long x, int k) {
    //buscamos el nodo de partida(el mas pequeño que sea >=x)
    auto* curr = tree.findMinGreaterOrEqual(x);
    if (!curr) return -1; 
    
    // Avanzamos hacia adelante a través de los sucesores
    while (curr) {
        if (k <= curr->frequency) {
            return curr->key; // El K-ésimo elemento está contenido en este nodo
        }
        k -= curr->frequency;
        curr = tree.getSuccessor(curr);
    }
    return -1; // No se encontraron suficientes elementos
}