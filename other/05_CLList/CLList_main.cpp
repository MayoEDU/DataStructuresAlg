#include "CLList.hpp"
#include <iostream>

int main() {
    CLList<double> list;

    list.push_front(1.1);
    list.push_front(1.2);
    list.push_front(1.3);

    list.print();
    std::cout << "size: " << list.size() << std::endl;

    list.pop_front();
    list.print();

    list.pop_front();
    list.pop_front();
    list.pop_front();
    list.print();

    return 0;
}
