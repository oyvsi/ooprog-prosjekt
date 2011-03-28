/*	iofunc.cpp 
		IO-funksjoner og validering av input.
*/

#include<iostream>
#include "iofunc.h"

using namespace std;

bool IOfunc::validate(char* txt, val_type v = NONE){
	int ch;
	for (int i = 0; i < strlen(txt); i++){
		ch = (int) txt[i];
		switch (v){
			case NAME:
											if ( !(isalpha(txt[i]) || isalex(txt[i])
																						 || txt[i] == ' '
																						 || txt[i] == '-') )
												return false;
											break;
			case ADDRESS :	if ( !(isalnum(txt[i]) || isalex(txt[i])
																						 || txt[i] == ' ') ) 
												return false;
											break;
		}
	}
	return true;
}

bool IOfunc::isalex(char c){				//returnerer om c er æÆøØåÅ
	int ic = (int) c;

	return (ic == UNI_ae || ic == UNI_AE ||
					ic == UNI_oe || ic == UNI_OE ||
					ic == UNI_aa || ic == UNI_AA);
}

bool IOfunc::is_number(char* c){
	for (int i = 0; i < strlen(c); i++) {
		if (!isdigit(c[i]))
			return false;
	}
	return true;
}

char IOfunc::to_upper(char up){			//Returnerer uppercaset char
	return ((char) toupper(up));
} 

char* IOfunc::read_string(std::istream* in, char delim){
	char* ptr, temp[STRLEN];
	in->getline(temp, STRLEN, delim); //Leser fra in til temp
	ptr = new char[strlen(temp)+1]; 	//Allokér minne for tekst + \0
	strcpy(ptr, temp);								//Kopier tekst
	return ptr;												//Returnér peker til tekst
}

char* IOfunc::read_valid(char* txt, val_type v = NONE){
	char* c_read = NULL;

	while (!c_read){
		cout << '\t' << txt << ": ";
		c_read = read_string(&cin, '\n');
		if (validate(c_read, v)) {
			return c_read;
		} else {
			delete [] c_read;
			c_read = NULL;
		}
	}
}

char* IOfunc::store_string(char* txt){
	char* ptr;
	ptr = new char[strlen(txt) + 1];
	strcpy(ptr, txt);
	return ptr;
}

int IOfunc::read_number(char* txt, int min, int max){
	char* c_read;
	int i_read = -1;

	do{ 																//Loop til vi får et gyldig tall
		cout << '\t' << txt << ": ";
		c_read = read_string(&cin);
		if (is_number(c_read))
			i_read = atoi(c_read);
		if (!is_number(c_read) || i_read > max || i_read < min)
				cout << "\tUgyldig tallverdi!" << endl;
		} while(!is_number(c_read) || i_read > max || i_read < min);
	
	return i_read;											//Returnerer gyldig tall
}
