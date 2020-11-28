// =================================================
// HW5 Priority Printer Queue 
// Name: Nick Luckey
// File Type: implementation pqueue.cpp
// =================================================

#include "pqueue.h"

// constructor
pqueue::pqueue()
{  count = 0;  // no jobs yet
}

// destructor does nothing
pqueue::~pqueue() {}

// Purpose: to add a job to a right place in the Pqueue
// Argument: j is the job priority number
void pqueue::insertjob(int j)
{
  // ** add the job j at the rear
  cout << "Adding: " << j << endl;
  Q[count]=j;
  count++;
  
  trickleup(); // moves the job to the right place
}

// Purpose: to print a job and reheapify the Pqueue
void pqueue::printjob()
{
  cout << "printing: " << Q[0] <<endl;

  reheapify(); 
}

// Purpose: to display all jobs
void pqueue::displayAll()
{ cout << "Jobs: " ;
  // ** loop to display jobs from slot 0 to slot count-1 horizontally
  
  for(int i=0;i<count;i++)
    { 
      cout << Q[i] << " " ;
    }
  cout << endl;
} 

// Utility functions follow: ------------------


// Purpose: to make the very last job trickle up to the right location 
void pqueue::trickleup()
{ 
  int x = count-1;  // the very last job location
  // ** while x is > 0
  // compare Q[x] with the parent and if the parent is bigger swap & update x. Otherwise stop.
  //  You can call getParent to get the location of the parent
  int temp;

  while(x>0 && (Q[getParent(x)]>Q[x]))
    {
      //if child index is even then swap and x gets parent location
      if(even(x))
	{
	  temp=Q[getParent(x)];
	  Q[getParent(x)]=Q[x];
	  Q[x]=temp;
	  x=(x-2)/2;
	}
      //if child index is odd then swap and x gets parent location
      else
	{
	  temp=Q[getParent(x)];
          Q[getParent(x)]=Q[x];
          Q[x]=temp;
          x=(x-1)/2;
	}
      
    }
}

  
// Purpose: find the location of the parent 
// The child location is given.  Need to call even.
int pqueue::getParent(int child)
{  

  // ** return the parent location 
  // if child is even it is right child

  if(even(child))
    return ((child-2)/2);

  //otherwise it is left child
  return ((child-1)/2);

}

// Purpose: is location i even? Important in finding its parent location
bool pqueue::even(int i)
{
  if ((i % 2) ==  0) return true; else return false; 
}


// Purpose: to reheapify the Pqueue after printing
void pqueue::reheapify()
{ 
  Q[0] = Q[count-1];  // move the last job to the front
  count--;
  // ** start at the root and repeat the following:
  // find the location of the smaller child if you have not fallen off the tree yet
  //  if the smaller child is smaller than the parent, swap
  //  else stop

  int x=0;//variable for parent node

  //while parent node is still in tree
  while(x<count-1)
    {
      //if parent node is larger than smaller child swap
      if(Q[x]>Q[getSmallerchild(x)])
	{
	  Q[count+1]=Q[getSmallerchild(x)];//store value of smaller child in unused array slot

	  Q[getSmallerchild(x)]=Q[x]; // parent goes to index of smaller child
	  Q[x]=Q[count+1]; // parent index becomes smaller child
	  
	  //if child index is even, then parent node is at left child 
	  if(even(x))
	    x=(x*2)+1;
	  //otherwise parent node is at right child
	  else
	    x=(x*2)+2;
	}
      //if parent is < smaller child then break loop
	else
	  break;

    }
      


}

// Purpose: to find the location of the smaller child
// where children at locations 2*i+1 and 2*i+2
int pqueue::getSmallerchild(int i)
{
// ** return the location of the smaller child 
  if(Q[2*i+1]>Q[2*i+2])
    return (2*i+2);//return right child
  
  return (2*i+1);//return left child
}


