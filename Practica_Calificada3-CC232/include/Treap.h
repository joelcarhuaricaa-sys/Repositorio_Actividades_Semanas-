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

    int countLess(const T& x) const {
        int count = 0;
        Node* curr = root_;
        while (curr) {
            if (x < curr->key) {
                curr = curr->left;
            } else if (curr->key < x) {
                count += getSubtreeSize(curr->left) + curr->frequency;
                curr = curr->right;
            } else {
                count += getSubtreeSize(curr->left);
                break;
            }
        }
        return count;
    }

    int countLessOrEqual(const T& x) const {
        int count = 0;
        Node* curr = root_;
        while (curr) {
            if (x < curr->key) {
                curr = curr->left;
            } else if (curr->key < x) {
                count += getSubtreeSize(curr->left) + curr->frequency;
                curr = curr->right;
            } else {
                count += getSubtreeSize(curr->left) + curr->frequency;
                break;
            }
        }
        return count;
    }

    T findKth(int index) const {
        Node* curr = root_;
        while (curr) {
            int left_size = getSubtreeSize(curr->left);
            if (index < left_size) {
                curr = curr->left;
            } else if (index < left_size + curr->frequency) {
                return curr->key;
            } else {
                index -= (left_size + curr->frequency);
                curr = curr->right;
            }
        }
        return -1;
    }
};

} // namespace ods