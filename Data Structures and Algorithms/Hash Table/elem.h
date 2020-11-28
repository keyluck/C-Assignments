// CS311 Yoshii - el_t for HW8 Hash Table
// Element type of a list node is defined here
// el_t can be changed by the client to fit its needs
//-----------------------------------------------------

#include <iostream>
#include <string>
using namespace std;

class el_t
{
 private:
  int key;      // key
  string name;  // customer name
  
  friend class slist;

 public:

  el_t();  // to create a blank el_t object
  el_t(int, string); // to create an initialized el_t object

  bool operator==(el_t);  // overload == for search
  // In search == is used to compare node elements
  // but what does it mean for this client to compare
  // node elements?  

  // this overloads cout for the el_t object
  // This is a friend function since the receiver object is not el_t
  friend ostream& operator<<(ostream&, const el_t&);  
  
  friend class htable;  // client of this class is htable which needs access to the key part of el_t 

};

