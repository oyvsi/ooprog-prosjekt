/*  iofunc.cpp 

    IO-funksjoner og validering av input.
*/

#include<iostream>
#include "iofunc.h"

using namespace std;

bool IOfunc::validate(char* txt, val_type v = none){
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
  in->get(temp, STRLEN, delim);               //  Leser fra in til temp
  ptr = new char[strlen(temp)+1];             //  Allokér minne for tekst + \0
  strcpy(ptr, temp);                          //  Kopier tekst
  return ptr;                                 //  Returnér peker til tekst
}

char* IOfunc::read_valid(char* txt, val_type v = none){
  cout << '\t' << txt << ": ";
  char* c_read = read_string(&cin, '\n');
  cin.ignore();
  return c_read;
}

int IOfunc::read_number(char* txt, int min = 0, int max = 0){
  char* c_read;
  int   i_read = -1;
  
  do{                                         //  Loop til vi får et gyldig tall
    cout << '\t' << txt << ": ";
    c_read = read_string(&cin);
    cin.ignore();
    if (is_number(c_read))
      i_read = atoi(c_read);
  } while(!is_number(c_read) || i_read > max || i_read < min);

  return i_read;                              //  Returnerer gyldig tall
}
