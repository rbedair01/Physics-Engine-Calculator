// Reema Bedair --- ryb200001
//   Stack.cpp

#include "Stack.h"
#include "Node.h"
#include <iostream>


// destructor
Stack::~Stack()
{
    if (Head == nullptr)
    {
        return;
    }

    delete this->getHead()->getNext();
}


// copy constructor
/*void*/ Stack::Stack(const Stack &right)
{
    Head = right.Head;
}

// overloaded assignment operator -- copy ("good programming practice")
void Stack::operator= (const Stack& right)
{
    Head = right.Head;
}


std::ostream& operator<< (std::ostream& print, const Stack& right)
{
    Stack temp = right;

    if (temp.Head->getOperand() == 0.0)
    {
        print << temp.Head->getOperator();
        
        temp.Head = temp.Head->getNext();
        
        while (temp.Head != nullptr)
        {
            print << ", " << temp.Head->getOperator();
            
            temp.Head = temp.Head->getNext();
        }
    }
    else
    {
        print << temp.Head->getOperand();
        
        temp.Head = temp.Head->getNext();
        
        while (temp.Head != nullptr)
        {
            print << ", " << temp.Head->getOperand();
            
            temp.Head = temp.Head->getNext();
        }
    }
    
    return print;
}


void Stack::operator<< (Node*& push)
{
   if (Head == nullptr)
    {
        Head = push;
    }
    else
    {
        push->setNext(Head);
        
        Head = push;
    }
}


void Stack::operator>> (const Node*& pop)
{
    if (Head->getNext() == nullptr)
    {
        pop = Head;
        
        Head = nullptr;
    }
    else
    {
        Node* hold;
        hold = Head;
    
        pop = hold;
    
        Head = Head->getNext();
    
        hold->setNext(nullptr);
    }
}



