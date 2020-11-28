using namespace std;
#include <iostream>
#include <vector>

//--------------------------------------------
//CS311 HW2P2 Combine 
//Name: Nick Luckey
//Compiler: g++
//--------------------------------------------

// combine two sorted lists A and B into R
// displays comparison every time it is done
void combine( vector<int> A, vector<int> B, vector<int> &R )
{
  //Initialize indexes for A and B vectors
  int ia, ib;
  ia=0;
  ib=0;
 
  //while loop until one vector has no more elements to check
  while(ia<A.size() && ib<B.size())
    {
      //if element from A is less than B's element then A's element is put into R vector
      if(A.at(ia)<B.at(ib)) 
	R.push_back(A.at(ia++));
      //otherwise B's element is less than A's element so B's element is put into R vector
      else
	R.push_back(B.at(ib++));

      cout << "comparison" << endl;
    }
  //Once 1 vector has no more elements to compare, put the rest of the elements from the other vector
  // into R vector
  if(ia==A.size())
    while(ib<B.size())
      R.push_back(B.at(ib++));
  else
    while(ia<A.size())
      R.push_back(A.at(ia++));

  
}


int main()
{  
  vector<int> L1;
  vector<int> L2;
  vector<int> L3;
  int N;  // how many elements in each of L1 and L2
  int e;  // for each element

  cout << "How many elements in each list?" << endl;
  cin >> N;

  cout << "List1"  << endl;
  for (int i = 1; i <=N; i++)
    { cout << "element :"; cin >> e; L1.push_back(e);} 

  cout << "List2"  << endl; 
  for (int i = 1; i <=N; i++)
    { cout << "element :"; cin >> e; L2.push_back(e);} 
  

  // call combine here to combine L1 and L2 into L3
  combine(L1,L2,L3);
  
  cout << "The result is: ";
  for (int i = 0; i < N*2; i++)
    { cout << L3[i]; } cout << endl;

}// end of main
