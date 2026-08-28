#include "SLLList.hpp"
#include <iostream>
int main (void) {
    SLList list;

    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.push_front(40);

    list.print();
    std::cout << list.size() << std::endl;
}