// Reema Bedair --- ryb200001
//   Stack.h

#include "Node.h"

#ifndef STACK_H
#define STACK_H


class Stack
{
private:
    Node* Head = nullptr;
    
public:
    // Mutator
    void setHead(Node* ptr) {Head = ptr;}
    
    // Accessor
    Node* getHead() const {return Head;}
    
    // default constructor
    Stack() {Head = nullptr;}
    
    // overloaded constructor
    Stack (Node* ptr) {Head = ptr;}
    
    // copy constructor
    Stack(const Stack&);
    
    // destructor
     ~Stack();
    
    
    // overloaded operators
    void operator=(const Stack&); // assignment operator (copy)
    friend std::ostream& operator<< (std::ostream&, const Stack&); // print
    void operator<< (Node*&); // push
    void operator>> (const Node*&); // pop
    
    
    
};

#endif /* STACK_H */
