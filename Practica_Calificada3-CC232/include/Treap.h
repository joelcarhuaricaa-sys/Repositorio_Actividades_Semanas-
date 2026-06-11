Treap.h

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

    void destroy(Node* u) {
        if (!u) return;
        destroy(u->left);
        destroy(u->right);
        delete u;
    }

public:
    Treap() : rng_(232) {}
    ~Treap() { clear(); }

    void clear() {
        destroy(root_);
        root_ = nullptr;
    }

    Node* root() const { return root_; }

    void add(const T& x) {
        std::uint64_t p = rng_();
        if (!root_) {
            root_ = new Node(x, p);
            return;
        }

        Node* curr = root_;
        Node* prev = nullptr;
        while (curr) {
            prev = curr;
            if (x < curr->key) {
                curr = curr->left;
            } else if (curr->key < x) {
                curr = curr->right;
            } else {
                curr->frequency++;
                Node* tmp = curr;
                while (tmp) {
                    updateSize(tmp);
                    tmp = tmp->parent;
                }
                return;
            }
        }

        Node* u = new Node(x, p, prev);
        if (x < prev->key) prev->left = u;
        else prev->right = u;

        Node* tmp = u;
        while (tmp) {
            updateSize(tmp);
            tmp = tmp->parent;
        }

        while (u->parent && u->parent->priority > u->priority) {
            if (u->parent->right == u) rotateLeft(u->parent);
            else rotateRight(u->parent);
        }
        if (!u->parent) root_ = u;
    }

    Node* findMaxLessOrEqual(const T& x) const {
        Node* curr = root_;
        Node* res = nullptr;
        while (curr) {
            if (curr->key <= x) {
                res = curr; 
                curr = curr->right; // Buscamos si hay uno más grande que también cumpla
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
                res = curr;
                curr = curr->left; // Buscamos si hay uno más pequeño que también cumpla
            } else {
                curr = curr->right;
            }
        }
        return res;
    }

    // Devuelve el nodo predecesor en orden simétrico (Inorder)
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

    // Devuelve el nodo sucesor en orden simétrico (Inorder)
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
};

}// namespace ods