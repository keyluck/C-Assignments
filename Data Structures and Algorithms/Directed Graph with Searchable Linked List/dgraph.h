// CS311 Yoshii dgraph.h that uses slist.h
// INSTRUCTION:
//  You need to comment this file completely
//  using the How to Comment file.
//  You have seen many examples so far.
//  We will check to see how well you have commented it.
//-----------------------------------------------------

// =======================================================
// HW#: HW6 dgraph
// Name: Nick Luckey
// File Type: Header file for dgraph class  
// ==================================================

#include <iostream>
#include "slist.h"
using namespace std;

//-----  globally setting up an alias ---------------------
const int SIZE = 20;   // for the size of the graph table

// this will be in each GTable slot
struct Gvertex
{
  char vertexName;      //the vertex Name
  int outDegree;	//the Out degree
  slist adjacentOnes;   //the adjecent vertices in an slist
  int visit;            // This will hold the visit number in HW7 
};

class dgraph
{

private:
  Gvertex Gtable[SIZE];  // a table representing a dgraph
  int  countUsed; // how many slots of the Gtable are actually used

public:

  
  class BadVertex {};  // thrown when the vertex is not in the graph

  //  virtual void testOne(){};

  dgraph();    // initialize vertexName (blank) and visit numbers (0)
               // initialize countUsed to be 0
  ~dgraph();   // do we have to delete all nodes of slists in table??
	       // Question: If we do not do this, will the llist destructor
               // be called automatically??? Try it.


  // PURPOSE: This will input data from file to fill Gtable
  // TO CALL: No parameter 
  void fillTable();  

  // PURPOSE: This will display the contents of Gtable  
  // TO CALL: No parameter
  void displayGraph(); 

  // PURPOSE: This will return the number of adjacent vertices from a given vertex.
  // If vertex has no adjacent vertices, throw BadVertex. Returns integer value.
  // TO CALL: Provide character of vertex.
  int findOutDegree(char);  
	
  // PURPOSE: This will return an slist containing adjacent vertices of a given vertex. 
  // If vertex has no adjacent vertices, throw BadVertex. Returns slist object.
  // TO CALL: Provide character of vertex.
  slist findAdjacency(char);  

};


