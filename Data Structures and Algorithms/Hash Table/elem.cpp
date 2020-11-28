// CS311 Yoshii - el_t for HW8 Hash Table
// Element type of a list node is defined here
// el_t can be changed by the client to fit its needs
//----------------------------------------------------

#include "elem.h"

// blank element
el_t::el_t()
{
  key = 0;
  name = "";
}

// initializing constructor to create an el_t object 
el_t::el_t(int akey, string aname)
{
  key = akey;
  name = aname;
}
  
// overload == for search based on the key part only
bool el_t::operator==(el_t OtherOne)
{
  if (key == OtherOne.key) return true; else return false;
}

// overload cout 
ostream& operator<<(ostream& os, const el_t& E)  
{  
  os << E.key << "+" << E.name;
  return os;  
}  
