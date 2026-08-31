#include "SLList.hpp"
#include <iostream>

int main(void) {
    SLList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    list.print();
    std::cout << list.size() << std::endl;

    return 0;
}