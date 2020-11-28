//CS311 Yoshii
//INSTRUCTION:
//Llist class - header file template 
//You must complete the ** parts and then complete llist.cpp
//Don't forget PURPOSE and PARAMETERS 

// =======================================================
// HW#: HW3P1 llist
// Your name: Nick Luckey
// Compiler:  g++ 
// File type: headher file  llist.h
//=======================================================

// include elem class for definition of el_t object
#include "elem.h"

//Class Node for linked list
class Node
{
 private:
  el_t Elem;   // elem is the element stored
  Node *Next; // pointer for next node
  friend class llist;// Allow access to llist class
  friend class slist; //Allow access to slist class

};
//---------------------------------------------------------

class llist
{
 
  
 protected:
  Node *Front;       // pointer to the front node
  Node *Rear;        // pointer to the rear node
  int  Count;        // counter for the number of nodes
  

 
 public:
  //virtual functions for test cases
  //virtual void testOne() = 0;


  // Exception handling classes 
  class Underflow{};   //thrown when trying to delete node when there are none left
  class OutOfRange{};  // thrown when the specified Node is out of range

  llist ();     // constructor to create a list object
  ~llist();     // destructor to destroy all nodes
  
 
  // PURPOSE: if llist is empty, returns true
  // if llist is not empty, returns false 
  // PARAMETER: None
  bool isEmpty();
    
  // PURPOSE: Displays everything in llist
  // if llist is empty displays [ empty ]
  // PARAMETER: None
  void displayAll();

  // PURPOSE: Add new node to the front of llist
  // PARAMETER: Provide element to be added to llist passed by value
  void addFront(el_t);
    
  // PURPOSE: Add new node to the rear of llist
  // PARAMETER: Provide element to be added to llist passed by value
  void addRear(el_t);

  // PURPOSE: If list is empty, throw exception
  // if llist is not empty, delete the front node
  // PARAMETER: Provide a holder for the element (pass by ref)
  void deleteFront(el_t&);
    
  // PURPOSE: if llist is empty, throw exception
  // if llist is not empty, delete the rear node
  // PARAMETER: Provide a holder for the element (pass by ref)
  void deleteRear(el_t&);
    
  // PURPOSE: if llist is empty, throw exception
  // if llist is not empty, delete the Ith node
  // PARAMETER: Provide the integer value of I and a holder for the element (pass by ref)
  void deleteIth(int, el_t&);

  // PURPOSE: if llist contains 1 or less elements, throw exception
  // if llist is contains more than 1 element, place a node before the Ith node
  // PARAMETER: Provide integer value of I and element to be added in Ith node both passed by value
  void insertIth(int, el_t);

  //Copy Constructor to allow pass by value and return by value
  llist(const llist&);
  
  //Overloading of = 
  llist& operator=(const llist&); 

};
