📌 **Overview**

  This project implements a Polynomial Evaluator in C++ that:
  
    Reads a polynomial expression from a file (poly.txt)
    
    Stores it in a linked list data structure
    
    Prints the polynomial in a human-readable format
    
    Evaluates the polynomial for a given value of x
**
🧠 Data Structure Used**
      
      
  The core data structure used to store polynomial terms is a **singly linked list**. Each node in the list represents a term with a coefficient and exponent. This allows dynamic, efficient storage and manipulation of polynomial expressions without knowing their size in advance.

**📦 Project Structure**
  
  Node: Represents a single term in the polynomial.

**LinkedList:** Manages the linked list of Node objects, supporting insertion, sorting, printing, and evaluation.

**Polynomial:** High-level class that handles file reading, delegates term management to LinkedList, and supports evaluation and display.
