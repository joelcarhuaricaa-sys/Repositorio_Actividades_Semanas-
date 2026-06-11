//explicacion de las funciona de acotacion
    // Encuentra el nodo con la clave más grande que sea <= x
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

     