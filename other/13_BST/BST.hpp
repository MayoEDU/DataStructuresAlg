#ifndef BST_HPP
#define BST_HPP

#include <iostream>

template <typename T>
class BST {
public:
    BST();
    ~BST();

    bool insert(const T& value);
    void remove(const T& value);
    void print() const;

    // Rotate the subtree rooted at value; return false if the rotation is impossible.
    bool rotateRight(const T& value);
    bool rotateLeft(const T& value);
    bool rotateLeftRight(const T& value);
    bool rotateRightLeft(const T& value);

private:
    struct Node {
        explicit Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
        ~Node() {
            delete left;
            delete right;
        }

        T data;
        Node* left;
        Node* right;
    };

    void inorder(Node* node) const;
    Node* search(const T& value) const;
    Node* getMinNode(Node* node) const;
    Node*& findLink(const T& value);
    static void rotateRight(Node*& node);
    static void rotateLeft(Node*& node);
    void deleteLeaf(Node* node, Node* parent);
    void deleteNodeWithOneChild(Node* node, Node* parent);
    void deleteNodeWithTwoChildren(Node* node);

    Node* root;
};

#include "BST.tpp"

#endif
