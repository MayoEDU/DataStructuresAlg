#ifndef SLLNODE_HPP
#define SLLNODE_HPP

template <typename T>
class SLLNode {
public:
    T data;
    SLLNode* next;

    SLLNode(const T& value = T(), SLLNode* next_node = nullptr)
        : data(value), next(next_node) {}
};

#endif
