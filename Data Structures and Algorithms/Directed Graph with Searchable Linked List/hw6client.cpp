// CS311 Yoshii
// HW6 Client file 
//INSTRUCTION: Complete this file and comment using How to Comment file.
//---------------------------------------------

// ================================================
// HW#: HW6 dgraph client 
// Name: Nick Luckey
// File type: Client file for dgraph
// ================================================


#include <iostream>
#include "dgraph.h"




int main()
{ /**
  0.Declare table object
  1.fillTable()
  2.displayGraph()
  while (the user does not want to stop)
    a.the user will specify which vertex     
    b.findOutDegree of the vertex and display the result
    b.findAdjacency of the vertex and display the result (see Hint)
    c.catch exception to display error mesg but do not exit
  **/

  dgraph T; //Declare table object
  char input; //Input from user to select vertex
  slist l1; //slist object for adjacency list

  // Call fill table to read from file to Gtable
  T.fillTable(); 

  // Display Gtable
  T.displayGraph();

  //While loop for user input
  while(1>0)
    {
      
      try
      {
	cout << "Enter a vertex name or control-C to exit: ";
	cin >> input;
      
	cout << T.findOutDegree(input) << " edges comes out to " << endl;
	l1 = T.findAdjacency(input);
	(l1).displayAll();
      }
      //exception handling for vertex with no adjacent vertices
      catch (dgraph::BadVertex)
	{
	  cout << "Error: Bad vertex\nChoose a different vertex" << endl;
	}
    }
      
}

/*
Hint:
  slist l1;
  l1 = G.findAdjacency('a');
  // how do you display l1?  Hint: it is an slist from HW3.

*/
