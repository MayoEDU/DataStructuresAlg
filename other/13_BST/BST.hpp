#ifndef BST_HPP
#define BST_HPP

#include <cstddef>
#include <iostream>

template <typename T>
class BST {
public:
    BST();
    BST(const BST& other);
    BST& operator=(const BST& other);
    ~BST();

    bool insert(const T& value);
    bool contains(const T& value) const;
    bool has(const T& value) const;
    bool remove(const T& value);

    bool empty() const;
    std::size_t size() const;
    void clear();

    void inorder() const;
    void inordr() const;

private:
    struct Node {
        explicit Node(const T& value) : data(value), left(nullptr), right(nullptr) {}

        T data;
        Node* left;
        Node* right;
    };

    Node* root;
    std::size_t tree_size;

    static Node* copy_tree(const Node* node);
    static void delete_tree(Node* node);
    static void print_inorder(const Node* node);
    static Node* remove_node(Node* node, const T& value, bool& removed);
};

#include "BST.tpp"

#endif
