// CS311 Yoshii - complete ** for HW8 client
// Note that the client knows about elem.h functions.
// It can create el_t objects.
//-----------------------------------------------

//============================================
// HW#: HW8 hashing client
// Name: Nick Luckey
// File type: client hw8client.cpp
//===========================================

using namespace std;
#include "htable.h"


// note that the second constructor of el_t can be used to
// create key+name to add to the table.
int main()
{ /**
 Loop:  
   Interactively add about 20 keys and names to the table,
     making sure some of them  collide. (function add)
     You can create el_t containing a key and name using a constructor.
 
  **/
  htable HT; //htable object
  el_t item; // el_t object to add or search for
  int slot; //integer value for slot number
  string name; //string variable for element's name
  int key; // integer value for element's key 
  slist found; // slist object for returning slist object during search2
  el_t blank; // blank slist object to check if element was found
  
  //for loop to add items to htable
  for(int i=0; i<=5; i++)
    {
      cout << "Enter key: " ;
      cin >> key;
      cout << "\nEnter name: " ;
      cin  >> name;
      
      item=el_t(key, name);

      slot = HT.add(item);
      cout << "Item entered into table at slot " << slot << endl;
    }

  /**
DisplayTable.
  **/

  //display htable 
  HT.displayTable();

  /**
 Loop:
  Interactively look up names using keys. (function find)
  Display the key + name if found else error message. 
  **/

  //loop to search for items in htable using key
  while(true)
    {
      cout << "Enter a key to search the table or press Ctrl-c to exit: " ;
      cin >> key;
      
      
      item=HT.find(key);

      if(item==blank)
	cout << "Item not found" << endl;

      else
	cout << "Found " << key << ": " << item << endl;

    }
 }
