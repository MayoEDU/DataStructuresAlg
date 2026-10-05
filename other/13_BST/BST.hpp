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
    void print() const;
    Node* search(const T& value) const;
    Node* getMinNode(Node* node) const;
    void deleteLeaf(Node* node, Node* parent);
    void deleteNodeWithOneChild(Node* node, Node* parent);
    void deleteNodeWithTwoChildren(Node* node);

    Node* root;
};

#include "BST.tpp"

#endif
