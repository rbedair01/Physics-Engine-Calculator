// Reema Bedair --- ryb200001
//   Node.h                    -- HEADER FILE (NODE) --

#include <string>

// include header guards
#ifndef NODE_H
#define NODE_H


// create class with attributes to be used in program
class Node
{
private:   // attributes
    double Operand = 0.0;
    char Operator = '0';
    Node *Next = nullptr;
    
public:    // functions to interact w/ varibles (attributes)
    // Default constructor: fills variables to ensure they are set to 0
    Node() {};
    
    // Overloaded constructor: to give variables specific values
    Node (double, char);
    
    // Accessor: see value of class attributes
    double getOperand() const {return Operand;} /* inline function */
    char getOperator() const {return Operator;} /* inline function */
    Node* getNext() const {return Next;} /* inline function */
    
    
    // Mutator: changes value of a class attribute
    void setOperand(double num) {Operand = num;}  /* inline function */
    void setOperator(char sign) {Operator = sign;} /* inline function */
    void setNext(Node* ptr) {Next = ptr;} /* inline function */
    
    
    
};

#endif /* NODE_H */



