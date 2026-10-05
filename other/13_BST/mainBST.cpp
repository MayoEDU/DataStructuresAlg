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
    words.insert("cat");
    words.insert("dog");
    words.insert("car");

    words.print();

    return 0;
}
