#include "SLList.hpp"
#include <iostream>

SLList::SLList() : head(nullptr), tail(nullptr), list_size(0) {

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
    //SLLNode* new_node = new SLLNode(val);
    //new_node->next = head;
    //head = new_node;

    head = new SLLNode(val, head);

    ++list_size;

    if (size() == 1) {
        tail = head;
    }
}

void SLList::push_back(int val) {
    //SLLNode* new_node = new SLLNode(val);
    //if (!head) {
    //   head = new_node;
    //} else {
    //    SLLNode* cur = head;
    //    while (cur->next) {
    //        cur = cur->next;
    //    }
    //    cur->next = new_node;
    //}

    if (empty()) {
        push_front(val);
        return;
    }

    tail->next = new SLLNode(val);  // Adds the new node at end
    tail = tail->next;              // Updates the tail

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

void SLList::pop_front(void){
    if (!empty()) {
    SLLNode* old_head = head;
    head = head->next;
    
    delete old_head;

    list_size--;
    }
}

void SLList::clear(void){
    while (head) {
        SLLNode* next = head->next;
        delete head;
        head = next;
    }

    tail = nullptr;
    list_size = 0;
}