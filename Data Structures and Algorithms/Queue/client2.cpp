//CS311 Yoshii
//INSTRUCTION:
//Look for ** to complete this program 
//The string output should match my hw1queueDemo.out 

//=========================================================
//HW#: HW1P2 queue
//Your name: Nick Luckey
//Complier:  g++
//File type: client program client2.cpp
//===========================================================

using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include "queue.h"

// Purpose of the program: Generate and display all possible combinations of strings 
// with the given characters using  a queue
// Algorithm: Remove element from queue then add the element+A, then element+B, 
// and then element+C to the queue

int main()
{ 
  string temp;//Variable to remove from queue to 
  queue Q;//Queue Object
  // "A", "B", "C" in the queue
  Q.add("A");
  Q.add("B");
  Q.add("C");
  
  // while loop -- indefinitely
  while(true)
    {
      try
	{ 
	  Q.remove(temp);
	  cout << temp << endl;
	  Q.add(temp+"A");
	  Q.add(temp+"B");
	  Q.add(temp+"C");
	}
      catch(queue::Overflow)
	{
	  cerr << "Error: the queue is full" ; exit(1);
	}
    }// end of loop

}

