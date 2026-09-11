#include "DLList.hpp"
#include <iostream>

int main() {
    DLList<int> list;

    // Test push_front and push_back
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    list.push_front(5);
    list.push_front(1);

    std::cout << "List after push operations:" << std::endl;
    list.print();
    std::cout << "Forward: ";
    list.print();
    std::cout << "Reverse: ";
    list.print_reverse();
    std::cout << "Size: " << list.size() << std::endl;
    std::cout << "Front: " << list.front_element() << ", Back: " << list.back_element() << std::endl;

    // Test pop_front
    std::cout << "\nPopping from front..." << std::endl;
    list.pop_front();
    list.print();

    // Test pop_back
    std::cout << "Popping from back..." << std::endl;
    list.pop_back();
    list.print();

    // Test copy constructor
    std::cout << "\nCopy constructor test:" << std::endl;
    DLList<int> list_copy = list;
    std::cout << "Original: ";
    list.print();
    std::cout << "Copy: ";
    list_copy.print();

    // Test clear
    std::cout << "\nClearing list..." << std::endl;
    list.clear();
    list.print();
    std::cout << "Empty? " << (list.empty() ? "true" : "false") << std::endl;

    return 0;
}
