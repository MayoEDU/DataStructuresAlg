#ifndef CLLIST_HPP
#define CLLIST_HPP

#include "SLLNode.hpp"

template <typename T>
class CLList {
public:
    CLList();
    ~CLList();

    CLList(const CLList& other);
    CLList& operator=(const CLList& other);

    unsigned size() const;
    bool empty() const;
    void push_front(const T& value);
    void pop_front();
    void print() const;

private:
    SLLNode<T>* tail;
    unsigned list_size;
};

#include "CLList.tpp"

#endif
