//CS311
//INSTRUCTION:
//Must use the provided HW3P1_help.doc to create llist.cpp
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes
//EMACS HINT:
//  You can copy from a Word document to emacs (contrl-right click)
//  control-K cuts and control-Y pastes
//  Esc x replace-str does string replacements
//  Esc > goes to the end of the file; Esc < to the beginning
//  Tab on each line will indent perfectly for C++

// ====================================================
//HW#: HW3P1 llist
//Your name: Nick Luckey
//Complier:  g++
//File type: llist.cpp implementation file
//=====================================================

using namespace std;
#include<iostream>
#include"llist.h" 

//constructor for llist object
llist::llist()
{
  //initialize Front, Rear, and Count
  Front=NULL;
  Rear=NULL;
  Count=0;

  cout << "calling the llist constructor" << endl;
}

//destructor for llist object
llist::~llist() 
{
  cout << "calling the destructor" << endl;


  el_t temp;//temp variable for deleteFront function
  
  //delete front while list is not empty 
  while(!isEmpty())
    deleteFront(temp);
}

// PURPOSE: if llist is empty, returns true
// if llist is not empty, returns false
// PARAMETER: None
bool llist::isEmpty() 
{
  if(Front == NULL && Rear==NULL && Count==0)
    return true;
  else 
    return false;
}

// PURPOSE: Displays everything in llist
// if llist is empty displays [ empty ]
// PARAMETER: None
void llist::displayAll() 
{


  //special case if llist is empty
  if(isEmpty())
    cout << "[ Empty ]" << endl;
  // regular case
  else
    {
      
      Node *temp=new Node; //temp pointer to traverse list to display each element in list
      temp=Front; //start at Front of list
      cout << "[" ;
      //Displays each element from Front to Rear, when temp is at Rear, then temp->Next=NULL 
      // so next loop will fail temp!=NULL condition
      while(temp!=NULL)
	{
	  cout << " " << temp->Elem; 
	  temp=temp->Next;
	}
      cout << " ]" << endl;
      cout << "Count is: " << Count << endl;
    }
}
  
// PURPOSE: Add new node to the rear of llist
// PARAMETER: Provide element to be added to llist
void llist::addRear(el_t NewNum) 
{
  //special case if this node is this first node
  if(isEmpty())
    {
      Node *newNode= new Node;
      Front=newNode;
      Rear=Front;
      Count++;
      Front->Elem=NewNum;
      Front->Next=NULL;
    }

  //regular case: create new node after rear, move rear to new node, insert elem into rear, set rear next to NULL
  else
    {
      Rear->Next= new Node;
      Rear=Rear->Next;
      Rear->Elem=NewNum;
      Rear->Next=NULL;
      Count++;
    }
}

// PURPOSE: Add new node to the front of llist
// PARAMETER: Provide element to be added to llist
void llist::addFront(el_t NewNum) 
{
  //special case if this node is the first node
  if(isEmpty())
    {
      Node *newNode= new Node;
      Front=newNode;
      Rear=Front;;
      Count++;
      Front->Elem=NewNum;
      Front->Next=NULL;
    }
  //regular case: create new first node(temp), link temp to front, move front to temp, insert elem into front elem
  else
    {
      Node *temp=new Node;
      temp->Next=Front;
      Front=temp;
      Front->Elem=NewNum;
      Count++;
    }
}

// PURPOSE: If list is empty, throw exception
// if llist is not empty, delete the front node
// PARAMETER: Provide a holder for the element (pass by ref)
void llist::deleteFront(el_t& OldNum) 
{
  //error case if linked list is empty
  if(isEmpty())
    {
      throw Underflow();
    }
  //special case if deleting 1 Node will make list empty
  else if(Count==1)
    {
      OldNum=Front->Elem; // get Elem from Front node
      delete Front; //Delete Node
      Front=NULL; //Set Front to NULL 
      Rear=NULL; //Set Rear to NULL
      Count=0; //Reset Count to zero
    }
  
  else
    {
      OldNum=Front->Elem; //Get Elem from Front node
      Node *Second; //Pointer for 2nd Node
      Second = Front->Next; //Second points to second Node in linked list
      delete Front; //Delete old first Node
      Front = Second; //Front points to the new first Node
      Count--;// Reduce count
    }
}


// PURPOSE: if llist is empty, throw exception
// if llist is not empty, delete the rear node
// PARAMETER: Provide a holder for the element (pass by ref)
void llist::deleteRear(el_t& OldNum) 
{
  //error case if list is empty
  if(isEmpty())
    throw Underflow();

  //special case if deleting 1 Node will make list empty
  else if(Count==1)
    {
      OldNum=Rear->Elem; //get Elem from Rear
      delete Rear; // delete Node that Rear points to
      Front=NULL; //Set Front to NULL
      Rear=NULL; //Set Rear to NULL
      Count=0;
    }
  // regular case
  else
    {
      OldNum=Rear->Elem; //get elem from Rear
      Node *temp; // temp pointer to traverse list
      temp=Front; // start at front of list

      //Traverse list with temp until temp is the node before Rear
      while(temp->Next->Next!=NULL)
        temp=temp->Next;

      Rear=temp; // Rear goes back one node to temp

      temp=temp->Next; //Move temp to node that needs to be deleted
      delete temp; //Delete last node
      Rear->Next=NULL; // set Rear->Next to NULL because it is the end of list
      Count--;
    }

}

// PURPOSE: if llist is empty, throw exception
// if llist is not empty, delete the Ith node
// PARAMETER: Provide the integer value of I and a holder for the element (pass by ref)
void llist::deleteIth(int I, el_t& OldNum) 
{
  //error case if Ith Node goes beyond the length of the list 
  if(I>Count || I<1)
    throw OutOfRange();
  
    
  //special case if there is only one Node
  else if(I==1)
    deleteFront(OldNum);

  //special case if Ith Node is the last Node
  else if(I==Count)
    deleteRear(OldNum);

  //regular case
  else
    {
      //temp pointer for traversing list to Ith node
      Node *temp=new Node;
      Node *P= new Node;
      temp=Front;
      //go to  Ith-1 node
      for(int j=1;j<I-1;j++)
	temp=temp->Next;
      
      OldNum=temp->Next->Elem; //Get elem from Ith Node
      P=temp->Next->Next; //P points to I+1th Node
      delete temp->Next; //Delete Ith Node(I-1th Node is not pointing to anything)
      temp->Next=P;//link the Ith-1 Node to I+1th Node
      Count--; //Reduce count
    }
  
  


}

// PURPOSE: if llist contains 1 or less elements, throw exception
// if llist is contains more than 1 element, place a node before the Ith node
// PARAMETER: Provide integer value of I and element to be added to new Ith node
void llist::insertIth(int I, el_t newNum) 
{
  

  //error case if I goes beyond the length of the list or there is no list to insert into
  if(I>Count+1 || I<1)
    throw OutOfRange();

    
  //special case if there is only one Node
  else if(I==1)
    addFront(newNum);

  //special case if Ith Node will become the last Node
  else if(I==Count+1)
    addRear(newNum);

  //regular case
  else
    {
      Node *temp=Front; //temp pointer to traverse list
      Node *P=new Node; //pointer for new node to be inserted into list
      P->Elem=newNum; // Elem in new Node gets newNum
      
      //traverse list to Ith-1 Node
      for(int j=1;j<I-1;j++)
        temp=temp->Next;
      
      P->Next=temp->Next;// Link P to Ith Node
      temp->Next=P; //Link Temp to P
      Count++;
    }
}

//PURPOSE: Allow pass by value and return by value with llist object
//PARAMETER: Provide place holder for llist object (pass by ref)
llist::llist(const llist& Original) 
{
    //  this->'s data members need to be initialized here first
    Front = NULL; Rear = NULL; Count = 0;
    //  this-> object has to be built up by allocating new cells
    //  and copying the values from Original into each cell as we did with
    //  operator= above. To do this,
    //  copy here the (**) lines in Operator Overloading of = but note that it is Original and not OtherOne.
    Node* P;  // local pointer for OtherOne
    P = Original.Front;
    while (P != NULL)  // a loop which repeats until you reach the end of OtherOne.
      {
	this->addRear(P->Elem);    //P’s element is added to this->
	P = P->Next;                         // Go to the next node in OtherOne
      }

      //  Nothing to return because this is a constructor.
      

 }

//PURPOSE: Allow the client to use = operator on llist object
//PARAMETER: Provide place holder for llist object (pass by ref)
llist& llist::operator=(const llist& OtherOne) 
{
  // First make sure this-> and OtherOne are not the same object.
  // To do this, compare the pointers to the objects .
  if (&OtherOne != this)  // if not the same
    {
      el_t temp;
      // this-> object has to be emptied first.
      while (! this->isEmpty() )
	this->deleteRear(temp);  
      // this-> object has to be built up by allocating new cells with OtherOne elements (**)
      Node* P;  // local pointer for OtherOne
      P = OtherOne.Front;
      while (P != NULL)  // a loop which repeats until you reach the end of OtherOne. 
        {
	  this->addRear(P->Elem);    //P’s element is added to this->
	  P = P->Next;                         // Go to the next node in OtherOne   
	} 
    }// end of if              
  return *this;    // return the result unconditionally.  Note that the result is returned by reference.
} 



