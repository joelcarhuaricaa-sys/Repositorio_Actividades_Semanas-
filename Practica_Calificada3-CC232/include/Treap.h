//explicacion de las funciona  de vecindad por punteros.
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

} // namespace ods