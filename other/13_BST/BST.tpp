#ifndef BST_TPP
#define BST_TPP

template <typename T>
BST<T>::BST()
    : root(nullptr) {}

template <typename T>
BST<T>::~BST() {
    delete root;
}

template <typename T>
bool BST<T>::insert(const T& value) {
    Node** node = &root;

    while (*node != nullptr) {
        if (value == (*node)->data) {
            return false;
        }

        if (value < (*node)->data) {
            node = &(*node)->left;
        } else {
            node = &(*node)->right;
        }
    }

    *node = new Node(value);
    return true;
}

template <typename T>
void BST<T>::remove(const T& val) {
    Node* parent = nullptr;
    Node* node = root;

    while (node != nullptr && node->data != val) {
        parent = node;

        if (val < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (node == nullptr) {
        std::cout << "remove: No Node to delee\n";
        return;
    }

    if (node->left == nullptr && node->right == nullptr) {
        deleteLeaf(node, parent);
    } else if (node->left == nullptr || node->right == nullptr) {
        deleteNodeWithOneChild(node, parent);
    } else {
        deleteNodeWithTwoChildren(node);
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::search(const T& value) const {
    Node* node = root;

    while (node != nullptr && node->data != value) {
        if (value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::getMinNode(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

template <typename T>
void BST<T>::inorder(Node* node) const {
    if (node == nullptr) {
        return;
    }

    inorder(node->left);
    std::cout << node->data << ' ';
    inorder(node->right);
}

template <typename T>
void BST<T>::print() const {
    inorder(root);
    std::cout << '\n';
}

template <typename T>
void BST<T>::deleteLeaf(Node* node, Node* parent) {
    if (parent == nullptr) {
        root = nullptr;
    } else if (parent->left == node) {
        parent->left = nullptr;
    } else {
        parent->right = nullptr;
    }

    delete node;
}

template <typename T>
void BST<T>::deleteNodeWithOneChild(Node* node, Node* parent) {
    Node* child = node->left != nullptr ? node->left : node->right;

    if (parent == nullptr) {
        root = child;
    } else if (parent->left == node) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    node->left = nullptr;
    node->right = nullptr;
    delete node;
}

template <typename T>
void BST<T>::deleteNodeWithTwoChildren(Node* node) {
    Node* min_right = node->right;
    Node* min_parent = node;

	// find min_right
    while (min_right->left != nullptr) {
        min_parent = min_right;
        min_right = min_right->left;
    }
	// change value at the node
    node->data = min_right->data;

	//delete min right
    if (min_right->right == nullptr) {
        deleteLeaf(min_right, min_parent);
    } else {
        deleteNodeWithOneChild(min_right, min_parent);
    }
}

template <typename T>
typename BST<T>::Node*& BST<T>::findLink(const T& value) {
    Node** link = &root;
    while (*link != nullptr && (*link)->data != value) {
        link = value < (*link)->data ? &(*link)->left : &(*link)->right;
    }
    return *link;
}

template <typename T>
void BST<T>::rotateRight(Node*& node) {
    Node* pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;
    node = pivot;
}

template <typename T>
void BST<T>::rotateLeft(Node*& node) {
    Node* pivot = node->right;
    node->right = pivot->left;
    pivot->left = node;
    node = pivot;
}

template <typename T>
bool BST<T>::rotateRight(const T& value) {
    Node*& node = findLink(value);
    if (node == nullptr || node->left == nullptr) return false;
    rotateRight(node);
    return true;
}

template <typename T>
bool BST<T>::rotateLeft(const T& value) {
    Node*& node = findLink(value);
    if (node == nullptr || node->right == nullptr) return false;
    rotateLeft(node);
    return true;
}

template <typename T>
bool BST<T>::rotateLeftRight(const T& value) {
    Node*& node = findLink(value);
    if (node == nullptr || node->left == nullptr || node->left->right == nullptr)
        return false;
    rotateLeft(node->left);
    rotateRight(node);
    return true;
}

template <typename T>
bool BST<T>::rotateRightLeft(const T& value) {
    Node*& node = findLink(value);
    if (node == nullptr || node->right == nullptr || node->right->left == nullptr)
        return false;
    rotateRight(node->right);
    rotateLeft(node);
    return true;
}

#endif
