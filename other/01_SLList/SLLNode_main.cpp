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

    return 0;
};