#include "LinkedList.h"
#include "Node.h"
#include <iostream>

//default constructor
LinkedList::LinkedList()
{
    head = nullptr;
    size =0;
}

LinkedList::~LinkedList()
{
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->getNext();
        delete current;
        current = next;
    }
}


//member functions
void LinkedList::append(double coefficient, int exponent) {
    Node* newNode = new Node(coefficient, exponent);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
    }
    size++;
}

void LinkedList::sortList() {
    if (!head) return;

    bool swapped = true;

    // Repeat until no swaps are needed
    while (swapped) {
        swapped = false;
        Node* prior = nullptr;
        Node* ptr1 = head;

        // Traverse and perform swaps as necessary
        while (ptr1->getNext() != nullptr) {
            Node* nextNode = ptr1->getNext();
            bool swapNeeded = (ptr1->getExp() < nextNode->getExp());

            if (swapNeeded) {
                // Perform the swap
                if (prior != nullptr) {
                    prior->setNext(nextNode);
                } else {
                    head = nextNode; // Update head if the first element is swapped
                }
                ptr1->setNext(nextNode->getNext());
                nextNode->setNext(ptr1);

                // Update pointers for next iteration
                prior = nextNode;
                swapped = true; // Mark that a swap occurred
            } else {
                // Move pointers forward if no swap needed
                prior = ptr1;
                ptr1 = nextNode;
            }
        }
    }
}

//Accessors
Node* LinkedList::getHead() const {return head;}
int LinkedList::getSize() const {return size;}

//mutator
void LinkedList::setHead(Node* newHead){ head = newHead; }

std::ostream& operator<<(std::ostream& os, LinkedList& list) {
        Node* current = list.head;
        while (current) {
            if (current) {
                if (current->getCoef() < 0)
                    os << " - ";
                else
                    os << " + ";
            }
            os << current;

            current = current->getNext();
        }
        return os;
    }


LinkedList& LinkedList::operator+=(Node* node) {
    if (!head)
    {
        head = node;
    } 
    else
    {
        Node* temp = head;
        Node* prev = nullptr;
        while (temp) {
            //check if current node exp = temp exponent if it is the case add then return
             if (temp->getExp() == node->getExp()) {
                // std::cout << "Match found! Adding coefficients.\n";
                // Add coefficients and delete the node for safety.
                double coef_value= temp->getCoef() + node->getCoef();
                temp->setCoef(coef_value);
                delete node;
                return *this;
            }
            prev = temp;
            temp = temp->getNext();
            
        }

        prev->setNext(node);
    }
    return *this;
}


const Node* LinkedList::operator[](int index) const 
{
    // Code to locate the node at 'index' and return a pointer to it
    Node* current = head;
    int count = 0;
    while(current != nullptr)
    {
        if(count == index){ return current;}
        current = current->getNext();
        count++; 
    }
    return nullptr;
}

