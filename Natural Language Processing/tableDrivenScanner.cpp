#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: Nick Luckey
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.


// info on each DFA
struct info
{
  string name;  // token name
  int startstate;
  int finalstate;
};

info DFAs[4];     // store up to 4 dfas' start and final

int  TRS[10][4];  // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here 

// ----- utility functions -----------------------

int readTables()
{  
  int i=0; //counter for number of DFAs
  int t;// variable for fin stream

  string w;// variable for fin2 stream
  int st,ft;// variables for fin2 stream

   ifstream fin ("trs.txt", ios::in);
   ifstream fin2 ("dfas.txt", ios::in);
   // ** Read in the files into TRS and DFAs
  
   for(int i=0;i<10;i++)
     {
       for(int j=0;j<4;j++)
	 {
	  
	  fin >> t;
	  TRS[i][j]=t;
	  }
     }
	  


   while(fin2 >> w)
     {
       DFAs[i].name = w;
       fin2 >> st;
       DFAs[i].startstate = st;
       fin2 >> ft;
       DFAs[i++].finalstate = ft;
     }
  



   // ** Return how many DFAs were read
   return i;
}

void displayTables(int numDFAs)
{
  // ** display DFAs nicely labeled
  cout  << setw(19) << "A" << setw(10) << "B" << setw(10) << "C" << setw(10) << "D" << endl;

  for(int i=0;i<10;i++)
    {
      cout  << "State " << i << " :" ;
      for(int j=0;j<4;j++)
	{
	  cout << setw(10) << TRS[i][j];
	}
      cout << endl;
    }

  // ** display TRS nicely labeled
  for(int i=0;i<numDFAs;i++)
    {
      cout << "Token type: " << DFAs[i].name << " Start state is " << DFAs[i].startstate <<
	" and the Final state is " << DFAs[i].finalstate << endl;
    }  
}

bool accept(info dfa, string word)
{
  // ** Does the dfa accept the word?
  // Start with the start state of the DFA and
  // look up the next state in TRS for each char in word.
  // At the end of the word, make sure you are in the 
  // final state of the DFA.
  // Use a formula to convert chars to TRS col numbers.

  int i=0;//variable to iterate over character string
  int k; //variable for next state



  k = TRS[dfa.startstate][word[i++]-97];
  while(word[i] != '\0')
    {

      cout <<  "State: " << k << " Char: " << word[i-1] << endl;
      cout << "Next state: " << TRS[k][word[i-1]] << endl;

      if(k>=0)
	{
	  k=TRS[k][word[i++]-97];
	}
      else
	{
	  return false;
	}
    }

  if(k==dfa.finalstate)
    return true;
  else 
    return false;

}


int main()
{
  cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
  cout << "States are 0 to 9 and chars are a to d" << endl;

  int numDFA = readTables(); // how many DFAs were read
  displayTables(numDFA);     // DISPLAY TABLES
  cout << ".....done reading tables...." << endl;

  bool found = false;

  string word;
  while(true)
    { cout << "@@Enter a string: " ;
      cin >> word;
      // ** try the DFAs one by one and see 
      //      if the word is accepted
      //      if so, display the word and the token name
      for(int i=0;i<numDFA;i++)
	{
	  cout << "Checking DFA number " << i << endl;
	  if(accept(DFAs[i],word))
	    {
	      found = true;
	      cout << "Token found!" << endl;
	      cout << " Word is: " << word << " Token type: " << DFAs[i].name << endl;
	      break;
	    }
	}

      // ** if no DFA does, generate a lexical error message.
      if(!found)
	{
	  cout << " LEXICAL ERROR:  " << endl;
	}
      found = false;

      cout << "do control-C to quit" << endl;
    }

}//the end
