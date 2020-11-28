using namespace std;
#include <iostream>

//--------------------------------------------
// CS311 HW2P1 Binary Search
// Name: Nick Luckey
// Compiler: g++
// --------------------------------------------

// x is what we are looking for in L; first and last are slot numbers 
int binarySearch(int L[], int x, int first, int last) 
{
  int middle;

  
  if(first>last) return -1; //if first passes last then the number was not found so end the search

  middle= int((first+last)/2); //find middle number in list
  
  cout << "comparing against an element in slot " << middle << endl;

  if(L[middle]==x) return middle; //if x is found at middle, return the index of that number

  else if(L[middle]>x) return binarySearch(L, x, first, middle-1); // if the middle is greater than x, then recursively call function on first half of the list

  else if(L[middle]<x) return binarySearch(L, x, middle+1, last); // if the middle is less than x, then recursively call function on second half of the list
		 

}


int main()
{ int A[10];
  int e;  // to look for this

  // fixed elements for A
  A[0] = 1; A[1]= 3; A[2]=5; A[3]= 7; A[4]=9; A[5]=11; A[6]=13;
  A[7] =15; A[8]= 17; A[9]= 19;

  cout << "What do you want to look for? ";
  cin >> e;

  // Call binarySearch here to look for e in A
  int respos = binarySearch(A,e, 0,9);

  if (respos == -1) cout << "Element not found" << endl; 
  else cout << "Found it in position " << respos+1 << endl;

}
