/*  iofunc.cpp 

    IO-funksjoner og validering av input.
*/

#include<iostream>
#include "iofunc.h"

using namespace std;

bool IOfunc::validate(char* txt, val_type v = NONE){
  int ch;
  for (int i = 0; i < strlen(txt); i++){
    switch (v){
      case NAME    :
                      if ( !(isalpha(txt[i]) || txt[i] == ' ' 
                                             || txt[i] == '-') )
                        return false;
                      break;
      case ADDRESS :  if ( !(isalnum(txt[i]) || txt[i] == ' ') ) 
                        return false;
                      break;
    }
  }
  
	return true;
}

bool IOfunc::is_number(char* c){
   for (int i = 0; i < strlen(c); i++) {
       if (!isdigit(c[i]))
           return false;
   }
   return true;
}

char* IOfunc::read_string(std::istream* in, char delim){
	char* ptr, temp[STRLEN];
	in->getline(temp, STRLEN, delim);           //  Leser fra in til temp
	ptr = new char[strlen(temp)+1];             //  Allok�r minne for tekst + \0
	strcpy(ptr, temp);                          //  Kopier tekst
	return ptr;                                 //  Return�r peker til tekst
}

char* IOfunc::read_valid(char* txt, val_type v = NONE){
  cout << '\t' << txt << ": ";
  char* c_read = read_string(&cin, '\n');
  
  if (validate(c_read, v))
    return c_read;
  else
    return NULL;
}

int IOfunc::read_number(char* txt, int min, int max){
  char* c_read;
  int   i_read = -1;
  
  do{                                         //  Loop til vi f�r et gyldig tall
    cout << '\t' << txt << ": ";
    c_read = read_string(&cin);
    if (is_number(c_read))
      i_read = atoi(c_read);
    if (!is_number(c_read) || i_read > max || i_read < min)
		  cout << "\tUgyldig tallverdi!" << endl;
  } while(!is_number(c_read) || i_read > max || i_read < min);

  return i_read;                              //  Returnerer gyldig tall
}
