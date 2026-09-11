#ifndef QUEUE_ARRAY_HPP
#define QUEUE_ARRAY_HPP

#include <iostream>
#include <stdexcept>

template <typename T, int CAPACITY = 100>
class QueueArray {

public:
    QueueArray();
    ~QueueArray();

    void enqueue(const T& value);
    T dequeue();
    const T& front_element() const;
    int size() const;
    bool empty() const;
    bool full() const;
    void print() const;
    void clear();

private:
    T data[CAPACITY];
    int front_idx;
    int back_idx;
    int queue_size;

    int next_index(int index) const;
};

#include "QueueArray.tpp"

#endif