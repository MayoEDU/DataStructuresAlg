#include "SLLList.hpp"
#include <iostream>

SLList::SLList() : head(nullptr), list_size(0) {

}

SLList::~SLList() {
    while (head) {
        SLLNode* next = head->next;
        delete head;
        head = next;
    }
}

unsigned SLList::size() const {
    return list_size;
}

bool SLList::empty() const {
    return (size() == 0);
}

void SLList::push_front(int val) {
    SLLNode* new_node = new SLLNode(val);
    new_node->next = head;
    head = new_node;
    ++list_size;
}

void SLList::push_back(int val) {
    SLLNode* new_node = new SLLNode(val);
    if (!head) {
        head = new_node;
    } else {
        SLLNode* cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = new_node;
    }
    ++list_size;
}

void SLList::print(){
    std::cout << "{ ";

    SLLNode* cur = head;
    while (cur) {
        std::cout << cur->data;
        if (cur->next) {
            std::cout << " -> ";
        }
        cur = cur->next;
    }
    std::cout << " }" << std::endl;
}