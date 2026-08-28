#ifndef SLLNODE_HPP
#define SLLNODE_HPP

class SLLNode {
   public:
   int data;
   SLLNode* next;

   SLLNode(int d = 0, SLLNode* n = nullptr) {
    data = d;
    next = n;
   }
};

#endif