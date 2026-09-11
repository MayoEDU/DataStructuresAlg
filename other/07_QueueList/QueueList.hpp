#ifndef QUEUE_LIST_HPP
#define QUEUE_LIST_HPP

#include "../04_DLList/DDLNode.hpp"
#include <iostream>
#include <stdexcept>

template <typename T>
class QueueList {

public:
    QueueList();
    ~QueueList();

    void enqueue(const T& value);
    T dequeue();
    const T& front_element() const;
    int size() const;
    bool empty() const;
    void print() const;
    void clear();

private:
    DDLNode<T>* front;
    DDLNode<T>* back;
    int queue_size;
};

#include "QueueList.tpp"

#endif
