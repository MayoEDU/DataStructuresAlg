#ifndef SLLIST_HPP
#define SLLIST_HPP

#include "SLLNode.hpp"

class SLList {
public:
    // No-Arg constructor
    SLList();
    ~SLList();

    // Copy constructor
    SLList(const SLList& other);

    //Assignment operator (=)
    SLList& operator=(const SLList& other);

    unsigned    size() const;           // Return the size of the list
    bool        empty() const;          // Return true if the list is empty
    void        push_front(int val);    // Inserts a node at the beginning
    void        push_back(int val);     // Insert a node at the end
    void        print();                // Print

    void        pop_front(void);            // Removes first node from the list
    void        pop_back(void);             // Removes last node from the list

    void        clear(void);                // Removes all nodes



private:
    SLLNode* head;          // Initial node
    SLLNode* tail;          // Points to end of list
    unsigned list_size;     // Amount of nodes
};

#endif