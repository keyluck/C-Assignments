//CS311 Yoshii dgraph.cpp 
// INSTRUCTION:
//  Complete all the functions you listed in dgraph.h
//  Comment the file completely using How to Comment file.
//  Use HW6-help.docx to finish the functions.
//-------------------------------------------------------

//======================================================
// HW#: HW6 dgraph
// Name: Nick Luckey
// File Type: Implementation file for dgraph class
//========================================================

using namespace std;
#include <iostream>
#include "dgraph.h"
#include <fstream>

//Constructor
dgraph::dgraph() 
{
  // initialize countUsed to be 0, vertexName to be blank, and visit number to 0
  countUsed=0; 
  Gtable[0].vertexName = ' ';
  Gtable[0].visit = 0;
}
//Destructor
dgraph::~dgraph() {}   


// PURPOSE: This will input data from file to fill Gtable
// TO CALL: No parameter
void dgraph::fillTable()  // be sure to read from a file
{
  ifstream fin; // variable to stream input from file
  fin.open("table.txt"); //open file
  char x; //variable to receive input from file

  while (fin >> Gtable[countUsed].vertexName)  // IF I CAN READ THE NAME
    { 
      fin >> Gtable[countUsed].outDegree; // input outDegree into Gtable
      Gtable[countUsed].visit = 0;      
      // loop to get each adjacent vertices based on out degree
      for(int i=0;i<Gtable[countUsed].outDegree;i++)
	{
	  fin >> x;
	  (Gtable[countUsed].adjacentOnes).addRear(x);   // this is a slist function from HW3
	  
	}
      countUsed++; //update index to next vertex

    }

  fin.close(); //close file when done
}



// PURPOSE: This will display the contents of Gtable
// TO CALL: No parameter
void dgraph::displayGraph()
{
  //for loop to display contents of each Gtable struct
  for(int i=0;i<countUsed;i++)
    {
      cout << Gtable[i].vertexName << " " << Gtable[i].outDegree << " " << Gtable[i].visit << " " << " " ;
     (Gtable[i].adjacentOnes).displayAll();
      cout << endl;
    }

}


// PURPOSE: This will return the number of adjacent vertices from a given vertex.
// If vertex has no adjacent vertices, throw BadVertex. Returns integer value.
// TO CALL: Provide character of vertex.
int dgraph::findOutDegree(char V)
{ // does not use a loop

  //throw exception for vertex with no adjacent vertices
  if((Gtable[(V-'A')].adjacentOnes).isEmpty()) throw BadVertex();
  
  //throw exception for bad inputs
  else if(V<'A' || V>'Z') throw BadVertex();

  //return number of adjacent vertices
  else
      return (Gtable[(V-'A')].adjacentOnes).Count;
    

}

// PURPOSE: This will return an slist containing adjacent vertices of a given vertex.
// If vertex has no adjacent vertices, throw BadVertex. Returns slist object.
// TO CALL: Provide character of vertex.
slist dgraph::findAdjacency(char V)
{ // does not use a loop

  // throw exception to catch bad vertex
  if((Gtable[(V-'A')].adjacentOnes).isEmpty()) throw BadVertex();
  
  //throw exception for bad inputs
  else if(V<'A' || V>'Z') throw BadVertex();

  //return slist containing adjacent vertices
  else
    return Gtable[(V-'A')].adjacentOnes;
  
}
