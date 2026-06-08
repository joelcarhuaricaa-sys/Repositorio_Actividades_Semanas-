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

private:
    Node* root_{nullptr};
    std::mt19937_64 rng_;

    int getSubtreeSize(Node* u) const {
        return u ? u->subtree_size : 0;
    }
    
    void updateSize(Node* u) {
        if (u) {
            u->subtree_size = u->frequency + getSubtreeSize(u->left) + getSubtreeSize(u->right);
        }
    }

    void rotateLeft(Node* u) {
        if (!u || !u->right) return;
        Node* w = u->right;
        w->parent = u->parent;
        if (!u->parent) root_ = w;
        else if (u->parent->left == u) u->parent->left = w;
        else u->parent->right = w;

        u->right = w->left;
        if (u->right) u->right->parent = u;
        w->left = u;
        u->parent = w;

        updateSize(u);
        updateSize(w);
    }

    void rotateRight(Node* u) {
        if (!u || !u->left) return;
        Node* w = u->left;
        w->parent = u->parent;
        if (!u->parent) root_ = w;
        else if (u->parent->left == u) u->parent->left = w;
        else u->parent->right = w;

        u->left = w->right;
        if (u->left) u->left->parent = w;
        w->right = u;
        u->parent = w;

        updateSize(u);
        updateSize(w);
    }

public:
    Treap() : rng_(232) {}
    ~Treap() { clear(); }

    void clear() {
        root_ = nullptr;
    }

    Node* root() const { return root_; }
};

} // namespace ods