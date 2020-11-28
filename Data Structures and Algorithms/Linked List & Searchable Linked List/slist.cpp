// ====================================================
//HW#: HW3P2 slist
//Your name: Nick Luckey
//Complier:  g++
//File type: slist.cpp implementation file
//=====================================================

using namespace std;
#include<iostream>
#include "slist.h"



slist::slist()   // constructor 
{
    cout << "in slist constructor" << endl;
}

//     search through the list to see if any node contains Key.
//   If so, return its position (>=1). Otherwise, return 0.
int slist::search(el_t Key)
{
  Node *P;
  P=this->Front;
  // Traverse linked list, compare each element with key, if key is found return position of node
  for(int i=1;i<=Count;i++)
    {
      if(Key==P->Elem)
	return i;
      P=P->Next;
    }
  // If loop does not find a match return 0
  return 0;
}

//       go to the Ith node (I is between 1 and Count) and replace the element there with Elem. 
//       If I was an illegal value, throw an exception (OutOfRange).
void slist::replace(el_t Elem, int I)
{
  if(I>Count || I<1) throw OutOfRange();

  Node *temp;
  temp=this->Front;

  //Traverse linked list to the Ith node
  for(int j=1;j<I;j++)
    temp=temp->Next;

  temp->Elem=Elem; // Ith node's Elem gets Elem
}

//       compare two slist object to see if they look the same.
bool slist::operator==(const slist& OtherOne)
{
  if(this->Count!=OtherOne.Count) return false;

  else
    {
      // If neither object is empty, compare elements in lists
      Node *P=this->Front;
      Node *Q=OtherOne.Front;
      
      // Compare all elem's from receiver object to other object, if an element does not match return false
      for(int i=1;i<=this->Count;i++)
	{
	  if(P->Elem!=Q->Elem)
	    return false;
	  
	  P=P->Next;
	  Q=Q->Next;
	}
           
      // if all elements match return true
      return true;
    }
}
