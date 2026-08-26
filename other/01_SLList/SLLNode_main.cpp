#include <iostream>
#include "SLLNode.hpp"

int main(void) {
    // Creation of SLLNodes
    SLLNode* n1 = new SLLNode(1);
    SLLNode* n2 = new SLLNode(2);
    SLLNode* n3 = new SLLNode(3);
    SLLNode* n4 = new SLLNode(4);

    // Linking of nodes
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;

    // Print the value of the first node
    std::cout << n1->data << std::endl;
    std::cout << n2->data << std::endl;
    std::cout << n3->data << std::endl;
    std::cout << n4->data << std::endl;

    // Printing through n1
    std::cout << n1->data << std::endl;
    std::cout << n1->next->data << std::endl;
    std::cout << n1->next->next->data << std::endl;
    std::cout << n1->next->next->next->data << std::endl;

    // Iteration through the nodes
    SLLNode* cur = n1;

    while (cur != nullptr) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }

    return 0;
};