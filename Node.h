#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
private:
    double coef;      // coefficient
    int exp;          // exponent
    Node* next;       // pointer to next node

public:
    // constructor
    Node();
    // Overloaded constructor
    
    Node(double coefficient, int exponent);   
   

    // Accessors
    double getCoef() const;
    int getExp() const;
    Node* getNext() const;

    // Mutators
    void setCoef(double coefficient);

    void setExp(int exponent);

    void setNext(Node* nextNode);

    friend std::ostream& operator<<(std::ostream& os, Node* node);
};
#endif
