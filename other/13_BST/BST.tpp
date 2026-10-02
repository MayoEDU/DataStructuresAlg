#ifndef BST_TPP
#define BST_TPP

template <typename T>
BST<T>::BST()
    : root(nullptr), tree_size(0) {}

template <typename T>
BST<T>::BST(const BST& other)
    : root(copy_tree(other.root)), tree_size(other.tree_size) {}

template <typename T>
BST<T>& BST<T>::operator=(const BST& other) {
    if (this == &other) {
        return *this;
    }

    Node* copied_root = copy_tree(other.root);
    delete_tree(root);
    root = copied_root;
    tree_size = other.tree_size;
    return *this;
}

template <typename T>
BST<T>::~BST() {
    clear();
}

template <typename T>
bool BST<T>::insert(const T& value) {
    Node** current = &root;

    while (*current != nullptr) {
        if (value == (*current)->data) {
            return false;
        }
        current = value < (*current)->data ? &(*current)->left : &(*current)->right;
    }

    *current = new Node(value);
    ++tree_size;
    return true;
}

template <typename T>
bool BST<T>::contains(const T& value) const {
    const Node* current = root;

    while (current != nullptr) {
        if (value == current->data) {
            return true;
        }
        current = value < current->data ? current->left : current->right;
    }

    return false;
}

template <typename T>
bool BST<T>::has(const T& value) const {
    return contains(value);
}

template <typename T>
bool BST<T>::remove(const T& value) {
    bool removed = false;
    root = remove_node(root, value, removed);
    if (removed) {
        --tree_size;
    }
    return removed;
}

template <typename T>
bool BST<T>::empty() const {
    return root == nullptr;
}

template <typename T>
std::size_t BST<T>::size() const {
    return tree_size;
}

template <typename T>
void BST<T>::clear() {
    delete_tree(root);
    root = nullptr;
    tree_size = 0;
}

template <typename T>
void BST<T>::inorder() const {
    print_inorder(root);
    std::cout << '\n';
}

template <typename T>
void BST<T>::inordr() const {
    inorder();
}

template <typename T>
typename BST<T>::Node* BST<T>::copy_tree(const Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* copy = new Node(node->data);
    try {
        copy->left = copy_tree(node->left);
        copy->right = copy_tree(node->right);
    } catch (...) {
        delete_tree(copy);
        throw;
    }
    return copy;
}

template <typename T>
void BST<T>::delete_tree(Node* node) {
    if (node == nullptr) {
        return;
    }

    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

template <typename T>
void BST<T>::print_inorder(const Node* node) {
    if (node == nullptr) {
        return;
    }

    print_inorder(node->left);
    std::cout << node->data << ' ';
    print_inorder(node->right);
}

template <typename T>
typename BST<T>::Node* BST<T>::remove_node(Node* node, const T& value, bool& removed) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = remove_node(node->left, value, removed);
        return node;
    }
    if (node->data < value) {
        node->right = remove_node(node->right, value, removed);
        return node;
    }

    removed = true;
    if (node->left == nullptr) {
        Node* replacement = node->right;
        delete node;
        return replacement;
    }
    if (node->right == nullptr) {
        Node* replacement = node->left;
        delete node;
        return replacement;
    }

    Node* successor = node->right;
    while (successor->left != nullptr) {
        successor = successor->left;
    }
    node->data = successor->data;

    bool successor_removed = false;
    node->right = remove_node(node->right, successor->data, successor_removed);
    return node;
}

#endif
