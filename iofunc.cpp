/*	IOFUNC.CPP
		IO-funksjoner og validering av input.
*/

#include<iostream>
#include <stdlib.h>
#include <string.h>
#include "iofunc.h"

using namespace std;

bool IOfunc::validate(char* txt, val_type v = NONE){ // returnerer om txt er gyldig ihht regler for val_type
	int ch;
	for (int i = 0; i < strlen(txt); i++){  // For hvert tegn i txt
		ch = (int) txt[i];
		switch (v){
			case NAME:
				if ( !(isalex(txt[i]) || isalpha(txt[i])    // dersom ulik alle bokstaver samt mellomrom og bindestrek
									 || txt[i] == ' '
									 || txt[i] == '-') )
				return false;
				break;
			case ADDRESS :	if ( !(isalex(txt[i]) || isalpha(txt[i]) // dersom ulik alle tall og bokstaver samt mellomrom
												 || txt[i] == ' '
												 || isalnum(txt[i])) )
				return false;
				break;
		}
	}
	return true;
}

bool IOfunc::isalex(char c){				//returnerer om c er ������
	int ic = (int) c;

	return (ic == UNI_ae || ic == UNI_AE ||
					ic == UNI_oe || ic == UNI_OE ||
					ic == UNI_aa || ic == UNI_AA);
}

bool IOfunc::is_number(char* c){            // returnerer om c er et tall
	for (int i = 0; i < strlen(c); i++) {   // for alle tegn i c
		if (!isdigit(c[i]))                 // dersom tegnet ikke er et tall
			return false;
	}
	return true;
}

char IOfunc::to_upper(char up){			//Returnerer uppercaset char
	return ((char) toupper(up));
}

char* IOfunc::strip(char* input) {  // Trims whitespace from string
	char temp_str[STRLEN], * return_str;
	int startstr = 0;

	while (input[startstr] == ' ')	 // find first non-blank (trim left)
		startstr++;

	while (input[strlen(input)-1] == ' ')	// trim right
		input[strlen(input)-1] = '\0';

	for(int i = startstr, j = 0; i <= strlen(input); i++)  // copy over
		temp_str[j++] = input[i];

	return_str = new char[strlen(temp_str)+1];  // allocate memory
	strcpy(return_str, temp_str);
	return return_str;
}

char* IOfunc::read_string(std::istream* in, char delim){ // leser streng fra in til delim blir funnet
	char* ptr, temp[STRLEN];
	in->getline(temp, STRLEN, delim); //Leser fra in til temp
	ptr = strip(temp); 	// strip whitespace
	return ptr;			//Return�r peker til tekst
}

char* IOfunc::read_valid(char* txt, val_type v = NONE){ // returnerer lovlig tekst ihht regler for val_type
	char* c_read = NULL;

	while (!c_read){
		cout << '\t' << txt << ": ";
		c_read = read_string(&cin, '\n');
		if (validate(c_read, v)) {
			return c_read;          // returnerer lovlig
		} else {
			delete [] c_read;
			c_read = NULL;          // returnerer NULL dersom ulovlig
		}
	}
}

char* IOfunc::store_string(char* txt){
	char* ptr;
	ptr = new char[strlen(txt) + 1];
	strcpy(ptr, txt);
	return ptr;
}

int IOfunc::read_number(char* txt, int min, int max){   // Returnerer tall mellom min og max
	char* c_read;
	int i_read = -1;

	do{ 																//Loop til vi f�r et gyldig tall
		cout << '\t' << txt << ": ";
		c_read = read_string(&cin);
		if (is_number(c_read))
			i_read = atoi(c_read);
		if (!is_number(c_read) || i_read > max || i_read < min)
				cout << "\tUgyldig tallverdi!" << endl;
		} while(!is_number(c_read) || i_read > max || i_read < min);

	return i_read;											//Returnerer gyldig tall
}


/* If level is 0 function returns number of level 0 items in file.
 Otherwise it returns the number of items in specified level (from current
 position in file to the next outer level relative to specified level.) */

int IOfunc::lines_in_level(istream* infile, int level) {
    streamoff cur_pos, new_pos;
	streamoff temp_pos = 0;
	int outer_level = -1;
    int no_in_level = 0;
	char line[STRLEN];
    char dummy;
	bool stop = false;

	cur_pos = infile->tellg();    // Position we were at before function call

	if (level > 0)  // All levels but 0 has an outer level.
		outer_level = level-1;
	else
		infile->seekg(0, ios::beg);   // Move to start (and collect $100)
	temp_pos = cur_pos;
	*infile >> dummy;                 // Read first non-blank
		while(!infile->eof() && !stop) {
		new_pos = infile->tellg();      // Position after first non-blank
		  // Check if we're at desired level
        if(new_pos == temp_pos+1+(level*LEVEL_BLANKS))
            no_in_level++;
		  // Check if we're at the outer level
		if(outer_level != -1 && new_pos == temp_pos+1+(outer_level*LEVEL_BLANKS)) {
			stop = true;    // We're at the next level, so we can stop the loop
		}
        infile->getline(line, STRLEN);  // Read rest of line so we can continue at next
		temp_pos = infile->tellg();     // Position for start at line
        *infile >> dummy;               // Read first non-blank
    }
	infile->clear();                   // Cear state flags
    infile->seekg(cur_pos, ios::beg);  // Move back to original position
	return no_in_level;                // Return no of items
}

void IOfunc::write_blank(ostream* out, int no) {
	for (int i = 0; i < no; i++)
		*out << ' ';
}
