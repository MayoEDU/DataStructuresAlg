#include "BST.hpp"
#include <iostream>
#include <string>

int main() {
    BST<std::string> words;
    words.insert("mango");
    words.insert("apple");
    words.insert("zoo");
    words.insert("banana");
    words.insert("pear");

    std::cout << "Has apple " << words.has("apple") << '\n';
    std::cout << "Has cat " << words.has("cat") << '\n';
    std::cout << "Inorder: ";
    words.inordr();

    words.remove("mango");
    std::cout << "After removing mango: ";
    words.inorder();

    return 0;
}
