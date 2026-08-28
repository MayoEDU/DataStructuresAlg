#ifndef SLLIST_HPP
#define SLLIST_HPP

#include "SLLNode.hpp"

class SLList {
public:
    // No-Arg constructor
    SLList();
    ~SLList();

    unsigned    size() const;       // Return the size of the list
    bool        empty() const;      // Return true if the list is empty
    void        push_front(int);    // Inserts a node at the beginning
    void        push_back(int);     // Insert a node at the end
    void        print();            //Print

private:
    SLLNode* head;          // Initial node
    unsigned list_size;     // Amount of nodes
};

#endif