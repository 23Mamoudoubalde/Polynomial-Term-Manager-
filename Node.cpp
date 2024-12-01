#include "Node.h"
#include <iostream>

// Default constructor

Node::Node() 
{
    coef = 0.0;
    exp = 0;
    next = nullptr;
}

// Overloaded constructor
Node::Node(double coefficient, int exponent){
    coef = coefficient;
    exp = exponent;
    next = nullptr;
}

/*Node::Node(double coefficient){
    coef = coefficient
    exp = 0; 
}

Node::Node(int exponent)
{
    exp = exponent;
    coef= 0.0;
}
*/
// Accessor 
double Node::getCoef() const { return coef;}

int Node::getExp() const {return exp;}

Node* Node::getNext() const {return next;}

// Mutator
void Node::setCoef(double coefficient)
{
    coef = coefficient;
}

void Node::setExp(int exponent)
{
    exp = exponent; 
}

void Node::setNext(Node* nextNode) 
{
    next = nextNode; 
}

std::ostream& operator<<(std::ostream& os, Node* node) {
    // the coefficient part
    //std::cout<< "\n\n"<<node.exp<<"\n\n";

    os << (node->coef < 0 ? -1 * node->coef : node->coef);
    
    //  the exponent part
    if (node->exp == 1) {
        os << "x";  // For x^1, print "x"
    } else if (node->exp != 0) {
        os << "x^" << node->exp;  // For any other print "x^exp"
    }
    return os;
}