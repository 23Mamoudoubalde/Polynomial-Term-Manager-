#ifndef LinkedList_H
#define LinkedList_H
#include "Node.h"

class LinkedList
{
private:
    Node* head;
    int size;
public:

// constructor
    LinkedList();

//destructor
    ~LinkedList();

// Accessort
    Node* getHead() const;
    int getSize() const;
//mutator
void setHead(Node* newHead);

void append(double coefficient, int exponent);
void sortList();
//Overloaded operator
const Node* operator[](int index) const;
LinkedList& operator+=(Node* newNode);

    // Overloaded << operator to display
friend std::ostream& operator<<(std::ostream& os, LinkedList& list);
};

#endif

