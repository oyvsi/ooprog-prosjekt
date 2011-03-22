/*  iofunc.cpp 

    IO-funksjoner og validering av input.
*/

#include<iostream>
#include "iofunc.h"

using namespace std;

bool IOfunc::validate(char* txt, val_type v = none){

}

bool IOfunc::is_number(char* c){
   for (int i = 0; i < strlen(c); i++) {
       if (!isdigit(c[i]))
           return false;
   }
   return true;
}

char* IOfunc::read_string(std::istream* in, char delim = '\n'){
  char* ptr, temp[STRLEN];
  in->get(temp, STRLEN, delim);               //  Leser fra in til temp
  ptr = new char[strlen(temp)+1];             //  Allok�r minne for tekst + \0
  strcpy(ptr, temp);                          //  Kopier tekst
  return ptr;                                 //  Return�r peker til tekst
}

char* IOfunc::read_valid(char* txt, val_type v = none){
}

int IOfunc::read_number(char* txt, int min = 0, int max = 0){
  char* c_read;
  int   i_read = -1;
  
  do{                                         //  Loop til vi f�r et gyldig tall
    cout << txt;
    c_read = read_string(&cin);
    cin.ignore();
    if (is_number(c_read))
      i_read = atoi(c_read);
  } while(!is_number(c_read) || i_read > max || i_read < min);

  return i_read;                              //  Returnerer gyldig tall
}