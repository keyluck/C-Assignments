//INSTRUCTION:
//Look for ** using control-S
//Fill in the function body
//When done, compile queue.cpp to make sure it has no syntax errors

//=========================================================
//HW#: HW1P2 queue
//Your name: Nick Luckey
//Complier:  g++
//File type: Queue Implementation file  queue.cpp
//===========================================================

using namespace std;
#include <iostream>
#include "queue.h"  

// constructor 
queue::queue()
{
  front=0; //set front to 0
  count=0; //set count to 0
  rear=0; //set rear to 0
}

//destructor 
queue::~queue()
{
}

// PURPOSE: returns true if queue is empty, otherwise false
bool queue::isEmpty()
{
  if(count==0) return true;  //if count is 0 then the queue is a empty
  else return false; // otherwise queue is not empty
}

// PURPOSE: returns true if queue is full, otherwise false
bool queue::isFull()
{
  if(count==MAX_SIZE) return true; //if the count is equal to the max size, then queue is full
  else return false; //otherwise queue is not full
}

// PURPOSE: if full, throws an exception Overflow
// if not full, enters an element at the rear 
// PAREMETER: provide the element (newElem) to be added
void queue::add(el_t newElem)
{
  if(isFull()) throw Overflow(); //if queue is full throw Overflow exception

  else
    {
      el[rear]=newElem; //add element to the queue
      count++; //increase count of queue
      rear=(rear+1)%MAX_SIZE; //move the rear of the queue
    }
}

// PURPOSE: if empty, throw Underflow
// if not empty, removes the front element to give it back 
// PARAMETER: provide a holder (removedElem) for the element removed (pass by ref)
void queue::remove(el_t& removedElem)
{
  if(isEmpty()) throw Underflow(); // if queue is empty throw Underflow exception

  else
    {
      removedElem=el[front]; //remove element from front of queue
      count--; //decrease count of queue
      front=(front+1)%MAX_SIZE; //move the front of the queue 
    }
}

// PURPOSE: if empty, throws an exception Underflow
// if not empty, give back the front element (but does not remove it)
//PARAMETER: provide a holder (theElem) for the element (pass by ref)
void queue::frontElem(el_t& theElem)
{
  if(isEmpty()) throw Underflow(); //if empty throw Underflow
  
  else
    theElem=el[front]; //get front element without removing from queue
}

// PURPOSE: returns the current size to make it 
// accessible to the client caller
int queue::getSize()
{
  return count; //return the count
}

// PURPOSE: display everything in the queue horizontally
// from front to rear enclosed in [   ]
// if empty, displays [ empty ]
void queue::displayAll()
{  
  int j = front;
  cout << "[";

  //display elements in queue starting at the front until i equals the number of items in queue
  for (int i = 1; i <= count; i++)
    { 
      cout << " " << el[(j+i-1)%MAX_SIZE] << " ";
    }
   cout << "]" << endl;   

}

// PURPOSE: if empty, throws an exception Underflow
//if queue has just 1 element, does nothing
//if queue has more than 1 element, moves the front one to the rear by
//calling remove followed by add.
void queue::goToBack()
{   
  string temp;//declare temp variable
  
  if(isEmpty()) throw Underflow(); // if queue is empty, throw exception underflow

  if(count==1) return;// if count is 1, do nothing
  else// otherwise, send the front element to the back of the queue
    {
      remove(temp);//remove front and store in temp
      add(temp);//add temp to back into queue so it goes to end of queue
    }
      
}

