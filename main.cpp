//   main.cpp
/*
        PROJECT 4 - Physics Engine Calculator
    This Program is creating a calculator to receive mathematical expressions through a file and relay the
    result to the user.
    In order for the program to evaluate the expressions read from a line on the file, it must take the expression line
    and convert it's format to a different notation, so the program can correctly adhere to the order of operations
    displayed in the expression.
    The line read in the file shows an expression using infix notation allowing the program to convert it to
    postfix notation.
    Once the expression is converted, the program will then use that conversion to evaluate the final answer
    of the expression. Displaying both the converted expression (postfix) and the resulting answer to the user
 */


// include header files that were created (Node.h, Stack.h)
#include "Node.h"
#include "Stack.h"

// libraries
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
using namespace std;


// function prototypes
string conversion(string);
double evaluation(string);


// main
int main()
{
    // define variable for filename to be read from user
    string infixFile;
    
    // Prompt user to enter a filename
    cout << "Enter filename: ";
    cin >> infixFile;
    cout << endl;
    
    // define a file data type for input (reading file only)
    ifstream infix;
    
    // open file
    infix.open(infixFile);
    
    
    // define variable to hold a line from the file
    string line;
    
    /*
        Create loop to read through each line in the file.
        Each line will be sent to a function to be converted from infix notation to postfix notation.
        After conversion, the newly converted expression line is then sent to another function to be evaluated for a result
        The converted line (postfix) and it's answer is then displayed to the console
     */
    while (getline(infix, line))
    {
        // if line is empty, go to next iteration in the loop (read next line)
        if (line.length() == 0)
        {
            continue;
        }
        
        /*
            - create string variable calling the infix to postfix conversion function
                (will store postfix notation)
            - create double variable calling the postfix evaluation function
                (will store final answer)
            - Display to console
         */

        // defining string varaible to hold returned converted expression of postfix notation
        // from function call. infix line is sent in as argument in the function call
        string postfix = conversion(line);

        // defining double to hold returned evaluated answer of postfix notation. postfix line was sent in as an
        // argument in the function call
        double evalAnswer = evaluation(postfix);
        
        // once both functions are complete, display returned items from functions (postfix 'string' & result 'double')
        // result is formatted to the 3 decimal place when displayed
        cout << postfix << "   " << fixed << setprecision(3) << evalAnswer << endl;
    }
    
    // close file
    infix.close();
    
    // end of main function
    return 0;
}


/*
    FUNCTION: POSTFIX EVALUATION
    Return type: double
    Parameters: function will recieve string containing the already converted expression
            (string in parameter holds the postfix notation)
    
    Function will receive postfix expression and will evaluate each operand and operator in the line to reach final answer
    the function will start by reading each number or sign in the line one by one to determine how to go about the evaluation
        - if an operand is read, it will be placed into a node into the top of the Stack (Head) until it is popped off the stack
            later for evaluation of a specific part in the operation of the expression
        - if an operator is read, it will tell the function to pop off the first 2 nodes (holding the operands) from the top of the stack,
            depending on the type of operator read, the function will either add, subtract, multiply, divide, or find the power of
            the second popped operand against the first popped operand
                EX:( 2nd pop + 1st pop )  EX: ( 2nd pop ^ 1st pop )
            once an operation from the expression is evaluated the answer for it will be placed back on the top of the stack (head)
    Function will loop though above method (if operand or if operator) until end of the line is all read, the final value of the
    entire expression will be the only number at head of stack
    The final value is then removed from stack and returned to main
*/
double evaluation(string postfix)
{
    // define variable to hold final answer of entire expression
    // this variable will be returned to main at end of function
    double finalAnswer = 0.0;
    
    // define varaible to hold the lenth of the postfix expression, so line is read properly to
    // determine if an item in the line is an operand or operator
    long int lineSize = 0;
    lineSize = postfix.length(); // places length of postfix into variable
    
    // create back up line that holds a replica of the postfix expression
    // postfix expression will be manipulated throughout function, this variable will ensure that the
    // postfix expression is being read properly
    string newLine = postfix;
    
    // define variable to hold the answers of the operations between 2 operands
    double tempAns = 0;
    
    
    // define a stack variable that will hold all the operands when pushed into a stack before being popped off
    // for evaluation
    Stack eval;
    
    
    
    // loop will allow each digit, space, or punctuation to be read one at a time
    for (int x = 0; x < lineSize; x++)
    {
        // if item read in line is a space, the postfix line parse everything before the space
        // and store it in a string, while the rest of the line will hold the entire string minus the parsed operator/operand
        if (isspace(newLine.at(x)))
        {
            // a Node is created and dynamically allocated so when item is determined to be an operand,
            // it will be placed in this node until later it is linked to the list (Stack)
            Node* newNode = new Node;
            
            // define variable to hold item that is parsed
            string digit;
            
            // define and give variable initialization to find the number given to the space's position in the
            // length of the line
            long int index = postfix.find(' ');
            
            // parse the item off postfix line from beginning to where the space is found in line
            // then parse the remainder of the line from the space until the end
            digit = postfix.substr(0, index);
            postfix = postfix.substr(index + 1);
            
            
            // if item parsed is a number, the number is converted from a string to a double
            // and entered into a new node, where the node is then pushed onto the tope of the stack at 'head'
            // else if item parsed is a punctuation, 2 operands are popped off stack to be evaluated with the
            // method established by the operator parsed from line
            if ((isdigit(digit.at(0))) || (digit.at(0) == '.'))
            {
                // convert string to double so the string digit can be placed into the node as an operand
                double number = stof(digit);
                
                // number is entered into the new node as an operand
                newNode->setOperand(number);
                
                
                // if Stack is empty, place new node into empty stack
                // else place new node into a stack where the stack isn't empty
                if (eval.getHead() == nullptr)
                {
                    // push new node into stack
                    eval.operator<<(newNode);
                    
                    // ensure that new node is at head of stack
                    eval.setHead(newNode);
                    
                    // set new node, next to nullptr
                    newNode->setNext(nullptr);
                }
                else
                {
                    // push new node into stack
                    eval.operator<<(newNode);
                    
                    // ensure that new node is at head of stack
                    eval.setHead(newNode);
                }
            }
            else if ((ispunct(digit.at(0))) && (digit.at(0) != '.'))
            {
                // initialize temporary operation holding answers is set to 0, before operation
                tempAns = 0;
                
                
                // create node to hold the head of the stack, so that a node is sent to pop function
                const Node* first = eval.getHead();
                // pop first node in stack and place into node created
                eval.operator>>(first);
                // define and initilaize variable to hold operand of the first number popped
                double firstPop = first->getOperand();
                
                // create node to hold the head of the stack, so that a node is sent to pop function
                const Node* second = eval.getHead();
                // pop second node in stack and place into node created
                eval.operator>>(second);
                // define and initilaize variable to hold operand of the second number popped
                double secPop = second->getOperand();
                
                // if operator is '+'; add the two numbers popped
                // if operator is '-'; subtract the two numbers popped
                // if operator is '/'; divide the two numbers popped
                // if operator is '*'; multiply the two numbers popped
                // if operator is '^'; find the power of the second popped number to the first popped number
                if (digit == "+")
                {
                    tempAns = secPop + firstPop;
                }
                else if (digit == "-")
                {
                    tempAns = secPop - firstPop;
                }
                else if (digit == "/")
                {
                    tempAns = secPop / firstPop;
                }
                else if (digit == "*")
                {
                    tempAns = secPop * firstPop;
                }
                else if (digit == "^")
                {
                    tempAns = pow (secPop, firstPop);
                }
                
                // New Node to add temporary final answer
                newNode->setOperand(tempAns);
                
                
                // push newNode holding answer onto top of stack
                if (eval.getHead() == nullptr) // if stack is empty
                {
                    eval.operator<<(newNode);
                                
                    eval.setHead(newNode);
                                   
                    newNode->setNext(nullptr);
                }
                else // if stack is not empty
                {
                    eval.operator<<(newNode);
                                
                    eval.setHead(newNode);
                }
                
                // ensure that both dynamically allocated constant nodes created are reset
                delete first;
                delete second;
            }
            
        }
        
    }
    
    
    // When parsing postfix line in beginning of loop above, the last item in line is not be parsed
    // since there is no space after the ending of the postfix expression
    // the if statement will ensure that if there is still something in the line (by seeing if the length is greater than 0)
    // it will find out if it is an operator or operand and will continue to create the last operation in
    // the evaluation of the postfix expression
    if (postfix.length() > 0)
    {
        // define and create dynamically allocated node, to hold the item in the line
        Node* newNode = new Node;
        
        // if item is a digit, convert string to double and add to node
        // then add node to stack
        // else if item parsed is a punctuation, 2 operands are popped off stack to be evaluated with the
        // method established by the operator parsed from line
        if (isdigit(postfix.at(0)) || (postfix.at(0) == '.'))
        {
            // convert string to double
            double num = stof(postfix);
            
            // add double variable of number to operand in the new node
            newNode->setOperand(num);
            
            // add the new node to top of stack 'head', by using push function
            if (eval.getHead() == nullptr) // if stack is empty
            {
                eval.operator<<(newNode);
                
                eval.setHead(newNode);
                
                newNode->setNext(nullptr);
            }
            else // if stack is not empty
            {
                eval.operator<<(newNode);
                
                eval.setHead(newNode);
            }

        }
        else if ((ispunct(postfix.at(0))) && (postfix.at(0) != '.'))
        {
            // initialize temporary operation holding answers is set to 0, before operation
            tempAns = 0;
            
            // create node to hold the head of the stack, so that a node is sent to pop function
            const Node* first = eval.getHead();
            // pop first node in stack and place into node created
            eval.operator>>(first);
            // define and initialize variable to hold operand from the node popped off
            double firstPop = first->getOperand();
            
            
            // create node to hold the head of the stack, so that a node is sent to pop function
            const Node* second = eval.getHead();
            // pop secon node in stack and place into node created
            eval.operator>>(second);
            // define and initialize variable to hold operand from the node popped off
            double secPop = second->getOperand();
            
            // if operator is '+'; add the two numbers popped
            // if operator is '-'; subtract the two numbers popped
            // if operator is '/'; divide the two numbers popped
            // if operator is '*'; multiply the two numbers popped
            // if operator is '^'; find the power of the second popped number to the first popped number
            if (postfix == "+")
            {
                tempAns = secPop + firstPop;
            }
            else if (postfix == "-")
            {
                tempAns = secPop - firstPop;
            }
            else if (postfix == "/")
            {
                tempAns = secPop / firstPop;
            }
            else if (postfix == "*")
            {
                tempAns = secPop * firstPop;
            }
            else if (postfix == "^")
            {
                tempAns = pow (secPop, firstPop);
            }
            
            //New Node to add temporary final answer
            newNode->setOperand(tempAns);
            
            // push newNode holding answer onto top of stack
            if (eval.getHead() == nullptr) // if stack is empty
            {
                eval.operator<<(newNode);
                            
                eval.setHead(newNode);
                               
                newNode->setNext(nullptr);
            }
            else // if stack is not empty
            {
                eval.operator<<(newNode);
                            
                eval.setHead(newNode);
            }
            // ensure that both dynamically allocated constant nodes created are reset
            delete first;
            delete second;
        }
    }
    
    // create node to hold the head (final number) of the stack, so that a node is sent to pop function
    const Node* Final = eval.getHead();
    // POP OFF FINAL NUMBER IN STACK
    eval.operator>>(Final);
    // get operand from node popped off and place into variable that will be returned to main
    finalAnswer = Final->getOperand();
    
    // ensure that dynamically allocated constant node created is reset
    delete Final;
    
    // return final result from evaluation of postfix expression to main
    return finalAnswer;
}




/*
    FUNCTION: INFIX TO POSTFIX CONVERSION
    Return type: string
    Parameters: a string variable is sent into function
            (string holds infix expression line read from file)
 
    Function will receive a string holding an expression in infix notation and will be converted and returned back
    back to main in postfix notation
    Function will read line character by character and determine a path of method for if the character is a
    number or if the character is one of the following punctuations: +, -, /, *, ^
 */
string conversion(string infix)
{
    // define variable that will hold postfix expression converted from infix notation
    // this variable is going to be sent to main
    string postfix = "";
    
    // define and set variable to hold line's length (infix)
    long int lineSize = 0;
    lineSize = infix.length();
    
    // create stack variable to hold the operators read from line
    Stack temp;

    // create loop to read through each character of the line
    for (int x = 0; x < lineSize; x++)
    {
        // if character is a punctuation(+ - / * ^) other than a period (.) -- (period is used as decimal for the operands)
        // puncuation is pushed into stack, determining if any operator needs to be popped off of stack before
        // depending on the precedence of the operator at top of stack compared with with the precedence of operator being pushed into stack
        // if character is a number, the operand will be straight into the postfix string
        if (ispunct(infix.at(x)) && (infix.at(x) != '.'))
        {
            // create new node for operator to be held
            Node* newNode = new Node;
            
            // put operator into a new node
            newNode->setOperator(infix.at(x));
            
            
            // if head of stack is empty, add new node into the empty stack
            // otherwise, determine the operator precedence, as well as, the precedence of head to establish
            // when to push in the operator (this determination is looped until lower precedence is on top of stack)
            if (temp.getHead() == nullptr)
            {
                temp.operator<<(newNode);
            }
            else
            {
                // if head is not empty, meaning if stack is not empty...
                // Before adding operator to stack, check prority with new operator against head
                if (infix.at(x) == ('(')) // left parentheses is always pushed on top of stack
                {
                    // push operator '(' onto stack
                    temp.operator<<(newNode);
                }
                else if (infix.at(x) == ('+') || infix.at(x) == ('-')) // +,- have lowest precedence
                {
                    // because +,- have lowest precedence they will pop off any operator >= to it's precedence
                    // as long as it's not a left parentheses
                    // so if head of stack is + - * / ^, head is popped off
                    // and is looped until head is empty or if it any other operator
                    if ((temp.getHead()->getOperator() == '-') || (temp.getHead()->getOperator() == '+') || (temp.getHead()->getOperator() == '*')
                        || (temp.getHead()->getOperator() == '/') || (temp.getHead()->getOperator() == '^'))
                    {
                        while ((temp.getHead()->getOperator() == '-') || (temp.getHead()->getOperator() == '+') || (temp.getHead()->getOperator() == '*')
                        || (temp.getHead()->getOperator() == '/') || (temp.getHead()->getOperator() == '^'))
                        {
                            // create node to hold head, so it can be sent to pop function
                            // to be removed from stack
                            const Node* prevNode =  temp.getHead();

                            // below are statements to determine the operator that will be placed into the postfix string line
                            if (prevNode->getOperator() == '-')
                            {
                                postfix += ' ';
                                postfix += '-';
                            }
                            else if (prevNode->getOperator() == '+')
                            {
                                postfix += ' ';
                                postfix += '+';
                            }
                            else if (prevNode->getOperator() == '^')
                            {
                                postfix += ' ';
                                postfix += '^';
                            }
                            else if (prevNode->getOperator() == '/')
                            {
                                postfix += ' ';
                                postfix += '/';
                            }
                            else if (prevNode->getOperator() == '*')
                            {
                                postfix += ' ';
                                postfix += '*';
                            }
                            
                            
                            // pop operator off
                            temp.operator>>(prevNode);
                            
                            // ensure that node that was dynamically allocated is cleared
                            delete prevNode;
                            
                            // if stack is empty break from loop
                            if (temp.getHead() == nullptr)
                            {
                                break;
                            }
                            
                        }
                    }

                    // once pop offs are established, push the new operator node into the stack at head
                    temp.operator<<(newNode);
                } 
                else if (infix.at(x) == ('*') || infix.at(x) == ('/')) // if *, / they will have mid precedence
                {
                    if ((infix.at(x) == ('*')) || (infix.at(x) == ('/')))
                    {
                        // if head is / * ^ pop off the stack until it is any other operator, then push new operator
                        // node on to stack (determination is looped)
                        if (((temp.getHead()->getOperator() == '/') || (temp.getHead()->getOperator() == '*') ||
                        (temp.getHead()->getOperator() == '^')))
                        {

                            while ((temp.getHead()->getOperator() == '/' || temp.getHead()->getOperator() == '*' || temp.getHead()->getOperator() == '^'))
                            {
                                // create node to hold node to be popped off and sent to pop function
                                const Node* prevNode = temp.getHead();
                                
                                // these statements will determine which operator is added into postfix string expression
                                if (prevNode->getOperator() == '^')
                                {
                                    postfix += ' ';
                                    postfix += '^';
                                }
                                else if (prevNode->getOperator() == '/')
                                {
                                    postfix += ' ';
                                    postfix += '/';
                                }
                                else if (prevNode->getOperator() == '*')
                                {
                                    postfix += ' ';
                                    postfix += '*';
                                }

                            
                                // pop off the new node from stack
                                temp.operator>>(prevNode);
                                
                                // ensure that node is cleared
                                delete prevNode;
                                
                                // if head is empty, meaning if stack is empy
                                // break from loop
                                if (temp.getHead() == nullptr)
                                {
                                    break;
                                }
                            }
                        }

                        // push new operator node into top of stack 'head'
                        temp.operator<<(newNode);
                        
                    }
                }
                else if (infix.at(x) == ('^')) // if operator is ^, it will have the highest precedence
                {
                    // if head is ^, it will pop off stack (determination is looped)
                    if ((temp.getHead()->getOperator() == '^'))
                    {
                        while ((temp.getHead()->getOperator() == '^'))
                        {
                            // create node to hold operator to be popped off
                            const Node* high = temp.getHead();

                            // will place ^ into postfix string expression
                            if (high->getOperator() == '^')
                            {
                                postfix += ' ';
                                postfix += '^';
                            }

                            // pops off operator from stack
                            temp.operator>>(high);
                            
                            // ensures that node created is cleared
                            delete high;
                        }
                    }
                    // push new operatore node onto top of stack
                    temp.operator<<(newNode);
                }
                else if (infix.at(x) == (')')) // if node is right parentheses, it will pop each operator until '(' is found
                {
                    // create new node to hold popped off operators
                    const Node* until_LeftP = temp.getHead();
                    
                    // through a loop head is determined if it will be popped until '('
                    while (temp.getHead()->getOperator() != '(')
                    {
                        
                        // statements will determine which operator is placed in postfix string
                        if (temp.getHead()->getOperator() == '/')
                        {
                            postfix += ' ';
                            postfix += '/';
                        }
                        else if (temp.getHead()->getOperator() == '*')
                        {
                            postfix += ' ';
                            postfix += '*';
                        }
                        else if (temp.getHead()->getOperator() == '+')
                        {
                            postfix += ' ';
                            postfix += '+';
                        }
                        else if (temp.getHead()->getOperator() == '-')
                        {
                            postfix += ' ';
                            postfix += '-';
                        }
                        else if (temp.getHead()->getOperator() == '^')
                        {
                            postfix += ' ';
                            postfix += '^';
                        }
                        
                        // pop off head operator
                        temp.operator>>(until_LeftP);
                    }
                    
                    // if head still hold '(', pop off the left parentheses
                    if (temp.getHead()->getOperator() == '(')
                    {
                        // pop off head operator
                        temp.operator>>(until_LeftP);
                    }
                    
                    // ensure that node created is cleared
                    delete until_LeftP;

                }

            }
            
            // if character after operator is a digit place a space in the postfix string expressions
            if ((x + 1 < lineSize))
            {
                if (isdigit(infix.at(x + 1)))
                {
                    postfix += ' ';
                }
            }

        }
        else if (isdigit(infix.at(x)) || (infix.at(x) == '.')) // if character in expression is a number (or '.' -- decimal)
        {
            // append the operand/number to the postfix string expression
            postfix += infix.at(x);
        }
    }
    
    
    // if the postfix string created has an spaces in front of the string, it is now removed
    if (postfix.at(0) == ' ')
    {
        int y = 0;
        
        long int postSize = postfix.length();
        
        // determine parse amount by loop
        while (postfix.at(y) == ' ')
        {
            postfix = postfix.substr(y + 1, postSize);
        }
        
    }
    
    
    // if stack head is not empty yet, pop off all left over operators and append the
    // operator to the postfix string expression (determined by loop)
    while (temp.getHead() != nullptr)
    {
        // create node to hold popped off operators
        const Node* rest = temp.getHead();
        
        // statements will determine which operator to paste in postfix string expression
        if (temp.getHead()->getOperator() == '/')
        {
            postfix += ' ';
            postfix += '/';
        }
        else if (temp.getHead()->getOperator() == '*')
        {
            postfix += ' ';
            postfix += '*';
        }
        else if (temp.getHead()->getOperator() == '+')
        {
            postfix += ' ';
            postfix += '+';
        }
        else if (temp.getHead()->getOperator() == '-')
        {
            postfix += ' ';
            postfix += '-';
        }
        else if (temp.getHead()->getOperator() == '^')
        {
            postfix += ' ';
            postfix += '^';
        }
        
        // pop off head operator
        temp.operator>>(rest);
        
        // ensure that node created is cleared
        delete rest;
    }
    

    // return string varaible holding completed conversion of expression (infix to postfix)
    // (returns postfix notation)
    return postfix;
}

