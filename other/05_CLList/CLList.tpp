#ifndef CLLIST_TPP
#define CLLIST_TPP

#include <iostream>

template <typename T>
CLList<T>::CLList() : tail(nullptr), list_size(0) {}

template <typename T>
CLList<T>::~CLList() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
CLList<T>::CLList(const CLList& other) : tail(nullptr), list_size(0) {
    if (other.empty()) {
        return;
    }

    SLLNode<T>* current = other.tail->next;
    do {
        push_front(current->data);
        current = current->next;
    } while (current != other.tail->next);
}

template <typename T>
CLList<T>& CLList<T>::operator=(const CLList& other) {
    if (this == &other) {
        return *this;
    }

    CLList copy(other);
    std::swap(tail, copy.tail);
    std::swap(list_size, copy.list_size);
    return *this;
}

template <typename T>
unsigned CLList<T>::size() const {
    return list_size;
}

template <typename T>
bool CLList<T>::empty() const {
    return tail == nullptr;
}

template <typename T>
void CLList<T>::push_front(const T& value) {
    SLLNode<T>* node = new SLLNode<T>(value);

    if (empty()) {
        node->next = node;
        tail = node;
    } else {
        node->next = tail->next;
        tail->next = node;
    }

    ++list_size;
}

template <typename T>
void CLList<T>::pop_front() {
    if (empty()) {
        return;
    }

    SLLNode<T>* front = tail->next;
    if (front == tail) {
        tail = nullptr;
    } else {
        tail->next = front->next;
    }

    delete front;
    --list_size;
}

template <typename T>
void CLList<T>::print() const {
    std::cout << "{ ";

    if (!empty()) {
        SLLNode<T>* current = tail->next;
        do {
            std::cout << current->data;
            current = current->next;
            if (current != tail->next) {
                std::cout << " -> ";
            }
        } while (current != tail->next);
    }

    std::cout << " }" << std::endl;
}

#endif
