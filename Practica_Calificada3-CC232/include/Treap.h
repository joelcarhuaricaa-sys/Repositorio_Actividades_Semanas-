#pragma once

#include <algorithm>
#include <cstdint>
#include <random>

namespace ods {

template <class T>
class Treap {
public:
    struct Node {
        T key{};
        std::uint64_t priority{0};
        int frequency{1};     // Control explitico de elementos duplicados
        int subtree_size{1};  // Invariante de aumento para orden estadistico
        Node* parent{nullptr};
        Node* left{nullptr};
        Node* right{nullptr};

        Node(const T& value, std::uint64_t p, Node* par = nullptr)
            : key(value), priority(p), frequency(1), subtree_size(1), parent(par) {}
    };
};

} // namespace ods