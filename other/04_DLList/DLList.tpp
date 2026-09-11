#ifndef DLLIST_TPP
#define DLLIST_TPP

#include <stdexcept>

template <typename T>
DLList<T>::DLList()
    : head(nullptr), tail(nullptr), list_size(0) {}

template <typename T>
DLList<T>::~DLList() {
    clear();
}

template <typename T>
DLList<T>::DLList(const DLList& other)
    : head(nullptr), tail(nullptr), list_size(0) {
    DDLNode<T>* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList& other) {
    if (this == &other) {
        return *this;
    }
    
    clear();
    DDLNode<T>* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
    return *this;
}

template <typename T>
void DLList<T>::push_front(const T& value) {
    DDLNode<T>* node = new DDLNode<T>(value);
    
    if (empty()) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    
    ++list_size;
}

template <typename T>
void DLList<T>::push_back(const T& value) {
    DDLNode<T>* node = new DDLNode<T>(value);
    
    if (empty()) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    
    ++list_size;
}

template <typename T>
void DLList<T>::pop_front() {
    if (empty()) {
        return;
    }
    
    DDLNode<T>* old_head = head;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    
    delete old_head;
    --list_size;
}

template <typename T>
void DLList<T>::pop_back() {
    if (empty()) {
        return;
    }
    
    DDLNode<T>* old_tail = tail;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    
    delete old_tail;
    --list_size;
}

template <typename T>
const T& DLList<T>::front_element() const {
    if (empty()) {
        throw std::out_of_range("front_element: Empty list");
    }
    return head->data;
}

template <typename T>
const T& DLList<T>::back_element() const {
    if (empty()) {
        throw std::out_of_range("back_element: Empty list");
    }
    return tail->data;
}

template <typename T>
int DLList<T>::size() const {
    return list_size;
}

template <typename T>
bool DLList<T>::empty() const {
    return list_size == 0;
}

template <typename T>
void DLList<T>::print() const {
    std::cout << "[ ";
    DDLNode<T>* current = head;
    while (current) {
        std::cout << current->data;
        if (current->next) {
            std::cout << " <-> ";
        }
        current = current->next;
    }
    std::cout << " ]" << std::endl;
}

template <typename T>
void DLList<T>::print_reverse() const {
    std::cout << "[ ";
    DDLNode<T>* current = tail;
    while (current) {
        std::cout << current->data;
        if (current->prev) {
            std::cout << " <-> ";
        }
        current = current->prev;
    }
    std::cout << " ]" << std::endl;
}

template <typename T>
void DLList<T>::clear() {
    while (head) {
        DDLNode<T>* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
    list_size = 0;
}

#endif
