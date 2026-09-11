#ifndef DLLIST_HPP
#define DLLIST_HPP

#include "DDLNode.hpp"
#include <iostream>

template <typename T>
class DLList {

public:
    DLList();
    ~DLList();

    DLList(const DLList& other);
    DLList& operator=(const DLList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    const T& front_element() const;
    const T& back_element() const;
    int size() const;
    bool empty() const;
    void print() const;
    void print_reverse() const;
    void clear();

private:
    DDLNode<T>* head;
    DDLNode<T>* tail;
    int list_size;
};

#include "DLList.tpp"

#endif
