/*
CS421 PROJECT 
Nick Luckey
STATE OF THE PROGRAM:

The program compiles and has the correct output for all 6 test cases.
The translation.cpp outputs are all in an output file after each test is run.
The program is complete, and there are no bugs.
 */

#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();
void getEword();
void gen(string line_type);

//******SCANNER.CPP BEGINS HERE******
//=====================================================
// File scanner.cpp 
//=====================================================
// --------- Two DFAs ---------------------------------
// WORD DFA 
// RE: (vowel | vowel n | constant vowel | constant vowel n | consonant-pair vowel | consonant-pair vowel n) ^+
bool word (string s)
{
  int state = 0;
  int charpos = 0;
  char c;  

  while (s[charpos] != '\0') 
    {
      c = s[charpos];

      if (c == 'a' || c == 'e' || c ==  'i' || c == 'o' || c == 'u' || c == 'I' || c == 'E')
	state = 1;
      else if (state == 0 || state == 1 || state == 2)
	{
	  if (c == 'd' || c ==  'w' ||  c == 'z' || c ==  'y' || c == 'j')
	    state = 3;
	  else if (c == 'b' || c == 'h' || c == 'k' || c == 'm' || c == 'r' || c == 'g' || c == 'p')
	    state = 4;
	  else if (c == 't')
	    state = 5;
	  else if (c == 's')
	    state = 6;
	  else if (c == 'c')
	    state = 7;
	  else if (c == 'n')// && state != 2)
	    state = 2;
	  else
	    return(false);
	}
      else if (state == 4 && c == 'y')
	state = 3;
      else if (state == 5 && c == 's')
        state = 3;
      else if (state == 6 && c == 'h')
        state = 3;
      else if (state == 7 && c == 'h')
        state = 3;
      else
	return(false);
      charpos++;
    }//end of while

  // check for final state
  if(state == 0 || state == 1 || state == 2) return(true);  
  else return(false);
}

// PERIOD DFA 
bool period (string s)
{  // complete this **
  int state = 0;
  int charpos = 0;

  while(s[charpos]!= '\0')
    {
      if(state == 0 && s[charpos] == '.')
	state = 1;
      charpos++;
    
    }

  if (state == 1) return(true);
  else return(false);
}

// ------ Three  Tables -------------------------------------

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR" , "EOFM"}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
struct reservedWord
{
  string word;
  tokentype token_type;
  
};

reservedWord rwList[] = { {"masu", VERB}, {"MASEN", VERBNEG}, {"mashita", VERBPAST}, {"masendeshita", VERBPASTNEG}, {"desu", IS}, {"deshita", WAS}, {"o", OBJECT} , {"wa", SUBJECT} , {"ni", DESTINATION} , {"watashi", PRONOUN}, {"anata", PRONOUN}, {"kare", PRONOUN}, {"kanojo", PRONOUN}, {"sore", PRONOUN}, {"mata", CONNECTOR}, {"soshite", CONNECTOR},{"shikashi", CONNECTOR}, {"dakara", CONNECTOR}  };

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
int scanner(tokentype& tt, string& w)
{
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */
  fin >> w;

  if(w == "eofm")
    {
      tt = EOFM;
      return 0;
    }

  if(word(w))
    {
      for(int i=0; i<18; i++)
	{
	  if(w == rwList[i].word)
	    {
	      tt = rwList[i].token_type;
	      return 0;
	    }
	}
      if(w[w.size()-1] == 'I' || w[w.size()-1] == 'E')
	tt = WORD2;
      else
	tt = WORD1;
      
    }
  else if(period(w))
    { tt = PERIOD;}
  else
    { tt = ERROR;}
}//the end of scanner

//******PARSER.CPP BEGINS HERE******
//=================================================
// File parser.cpp 
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

tokentype saved_Token;
string saved_Lexeme, saved_E_word, CONNECT, ACTOR, TENSE, DESCRIPTION, ACTION, TO, OBJ;
bool token_Available = false;

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: Syntax errors
void syntaxerror1(tokentype expected, string saved_Lexeme)
{
  cout << endl << "SYNTAX ERROR: Expected " << tokenName[expected] << " but instead found " << saved_Lexeme << "." << endl;
  cout << "Terminating the program." << endl;

  exit(0);
}

// Type of error: Syntax error
void syntaxerror2(string saved_Lexeme, string parserFunction)
{
  cout << endl << "SYNTAX ERROR: Unexpected " << saved_Lexeme << " found in " << parserFunction << " function." << endl;
  cout << "Terminating the program." << endl;

  exit(0);
}

// Purpose: To see what token comes next when the scanner is called based on if the token space is available
//There are also cases for if there is a lexical error or the end of the story is reached.
//This function will return the saved_token
tokentype next_token()
{
  if(token_Available == false)
    {
      scanner(saved_Token, saved_Lexeme);

      cout << "Scanner called using word: " << saved_Lexeme << endl;

      if(saved_Token == ERROR)
	{
	  cout << endl << "Lexical Error: " << saved_Lexeme << " is not a valid token." << endl;
	}
      else if(saved_Token == EOFM)
	{
	  cout << "SUCCESSFULLY PARSED STORY!" << endl;
	  exit(0);
	}

      token_Available = true;
    }
  return saved_Token;
}

// Purpose: To see if tokentype expected is different from next_token()
// if it is, it will call syntaxerror1()
// if it is the same, it will be matched and return true.
bool match(tokentype expected)
{
  if(next_token() != expected)
    {
      syntaxerror1(expected, saved_Lexeme);
      return false;
    }
  else
    {
      cout << "Matched " << tokenName[expected] << "." << endl;
      token_Available = false;
      return true;
    }
}

// ----- RDP functions - one per non-term -------------------
/*

<s> ::= [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# <afterSubject> 
<afterSubject> ::= <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# <afterNoun> 
<afterNoun> ::= <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD | DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | OBJECT #gen(OBJECT) <afterObject> 
<afterObject> ::= <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD 

<noun> ::= WORD1 | PRONOUN  
<verb> ::= WORD2 
<be> ::=   IS | WAS 
<tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
*/

// Grammar: <story> :: = <s> {<s>}
void story()
{
  cout << "Processing <story>" << endl << endl;

  s();
  
  while(true)
    {
      switch(next_token())
	{
	case CONNECTOR: s();
	  break;
	case WORD1: s();
	  break;
	case PRONOUN: s();
	  break;
	default: return;
	}
    }
}

// Grammar: <s> ::= [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# <afterSubject>
void s()
{
  cout << "Processing <s>" << endl;

  if(next_token() == CONNECTOR)
    {
      match(CONNECTOR);
      getEword();
      gen("CONNECT");
    }

  noun();
  getEword();

  match(SUBJECT);
  gen("ACTOR");

  afterSubject();
}

// Grammar: <afterSubject> ::= <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# <afterNoun>
void afterSubject()
{
  cout << "Processing <afterSubject>" << endl;

  switch(next_token())
    {
    case WORD2: verb(); getEword(); gen("ACTION"); tense(); gen("TENSE"); match(PERIOD);
      break;
    case WORD1: noun(); getEword(); afterNoun();
      break;
    case PRONOUN: noun(); getEword(); afterNoun();
      break;
    default:
      syntaxerror2(saved_Lexeme, "afterSubject");
    }
}

// Grammar: <afterNoun> ::= <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD | DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | OBJECT #gen(OBJECT) <afterObject>
void afterNoun()
{
  cout << "Processing <afterNoun>" << endl;

  switch(next_token())
    {
    case IS: be(); gen("DESCRIPTION"); gen("TENSE"); match(PERIOD);
      break;
    case WAS: be(); gen("DESCRIPTION"); gen("TENSE"); match(PERIOD);
      break;
    case DESTINATION: match(DESTINATION); gen("TO"); verb(); getEword(); gen("ACTION"); tense(); gen("TENSE"); match(PERIOD);
      break;
    case OBJECT: match(OBJECT); gen(OBJ); afterObject();
      break;
    default:
      syntaxerror2(saved_Lexeme, "afterNoun");
    }
}

// Grammar: <afterObject> ::= <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
void afterObject()
{
  cout << "Processing <afterObject>" << endl;

  switch(next_token())
    {
    case WORD2:
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;

    case WORD1:
      noun();
      getEword();
      match(DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;

    case PRONOUN:
      noun();
      getEword();
      match(DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;

    default:
      syntaxerror2(saved_Lexeme, "afterObject");
    }
}

// Grammar: <noun> ::= WORD1 | PRONOUN
void noun()
{
  cout << "Processing <noun>" << endl;

  switch (next_token())
    {
    case WORD1:
      match(WORD1);
      break;

    case PRONOUN:
      match(PRONOUN);
      break;

    default:
      syntaxerror2(saved_Lexeme, "noun");
    }
}

// Grammar: <verb> ::= WORD2
void verb()
{
  cout << "Processing <verb>" << endl;

  match(WORD2);
}

//Grammar: <be> ::=   IS | WAS
void be()
{
  cout << "Processing <be>" << endl;
  
switch (next_token())
    {
    case IS:
      match(IS);
      break;

    case WAS:
      match(WAS);
      break;

    default:
      syntaxerror2(saved_Lexeme, "be");
    }
}

// Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
void tense()
{
  cout << "Processing <tense>" << endl;
  
  switch (next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;

    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;

    case VERB:
      match(VERB);
      break;

    case VERBNEG:
      match(VERBNEG);
      break;

    default:
      syntaxerror2(saved_Lexeme, "tense");
    }
}

//******TRANSLATOR.CPP BEGINS HERE******
//=================================================
// File translator.cpp 
//=================================================

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt
struct dictionarySection
{
  string section;
  string eWord[20];
  string jWord[20];
};
dictionarySection lexicon[5];

ofstream fout;


void getEword()
{
  int i = 0;
  
  switch(saved_Token)
    {
    case PRONOUN:
      i = 0;
      break;

    case CONNECTOR:
      i = 1; 
      break;

    case WORD1:
      (saved_Lexeme[saved_Lexeme.size()-1]=='i' && saved_Lexeme[saved_Lexeme.size()-2]== 'i')? i=3 : i=2;
      break;

    case OBJECT:
    case SUBJECT:
    case DESTINATION:
      i = 2;
      break;

    case VERB:
    case VERBNEG:
    case VERBPAST:
    case VERBPASTNEG:
    case WORD2:
      i = 4;
      break;
  
    }
  saved_E_word = saved_Lexeme;

  for(int j = 0; j < 20; j++)
    {
      if(lexicon[i].jWord[j] == saved_Lexeme)
	{
	    
	  saved_E_word = lexicon[i].eWord[j];
	  //cout << " English translation is " << saved_E_word << endl << endl;
	  break;
	}
      if(lexicon[i].jWord[j]=="")
	break;
    }
}

//gen(line_type) - using the line type,
//sends a line of an IR to translated.txt
//(saved_E_word or saved_token is used)
void gen(string line_type)
{
  if(line_type == "CONNECT")
    {
      fout << "CONNECTOR: " << saved_E_word << endl;
    }

  if (line_type == "TENSE")
    {
      fout << "TENSE: "  << tokenName[saved_Token] << endl;
    }
  
  else if (line_type == "DESCRIPTION")
    {
      fout << "DESCRIPTION: " << saved_E_word << endl;
    }

  else if (line_type == "OBJ")
    {
      fout << "OBJECT: " << saved_E_word << endl;
    }
  
  else if (line_type == "ACTION")
    {
      fout << "ACTION: " << saved_E_word << endl;
    }

  else if (line_type == "PERIOD")
    {
      fout << "PERIOD: " << saved_E_word << endl;
    }
    
  else if (line_type == "TO")
    {
      fout << "TO: " << saved_E_word << endl;
    }
  
  else if (line_type == "ACTOR")
    {
      fout << "ACTOR: " << saved_E_word << endl;
    }
  
  else
    fout << "JAPANESE WORD: " << saved_Lexeme << endl;     
}

// The final test driver to start the translator
int main()
{
  string word;
  int i = 0;
  int j = 0;
  string section;

  for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 20; j++)
	{
	  lexicon[i].section = "";
	  lexicon[i].jWord[j] = "";
	  lexicon[i].eWord[j] = "";
	}
    }
  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt
  fin.open("lexicon.txt");
  fin >> word;
  lexicon[0].section = "pronoun";
  lexicon[0].jWord[0] = word;

  while(fin >> word)
    {
      lexicon[i].eWord[j] = word;
      j++;
      fin >> word;
      
      if(word == "mata")
        {
	  section = "connector";
	  j = 0;
	  i = 1;
        }
      else if(word == "daigaku")
        {
	  section = "noun";
	  j = 0;
	  i = 2;
        }
      else if(word == "yasashii")
        {
	  section = "adjective";
	  j = 0;
	  i = 3;
        }
      else if(word == "nakI")
        {
	  section = "verb";
	  j = 0;
	  i = 4;
	}
      lexicon[i].section = section;
      lexicon[i].jWord[j] = word;
    }

  fin.close();

  //** opens the output file translated.txt
  fout.open("translated.txt");

  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file
  //** closes traslated.txt


  fin.close();
  fout.close();
}// end
