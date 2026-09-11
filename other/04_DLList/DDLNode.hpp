#ifndef DDLNODE_HPP
#define DDLNODE_HPP

template <typename T>
class DDLNode {
public:
    T data;
    DDLNode* next;
    DDLNode* prev;

    DDLNode(const T& value = T(), DDLNode* next_node = nullptr, DDLNode* prev_node = nullptr)
        : data(value), next(next_node), prev(prev_node) {}
};

#endif
