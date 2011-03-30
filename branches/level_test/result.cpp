#include <iostream>
#include <fstream>
#include "result.h"
#include "iofunc.h"
extern IOfunc io;


Result::Result() {  // called from division 
    h_goals = -1;   // We have no results;    
}

void Result::set_date(char in_date[DATELEN]) {
    strcpy(date, in_date);
}

void Result::get_date(char in_date[]) {
    strcpy(in_date, date);
}

int Result::get_hgls() {
    return h_goals;
}

int Result::get_agls() {
    return a_goals;
}

bool Result::read_result(istream* infile, char in_date[], bool update) {
	char* dummy;
	if (update) {
		*infile >> h_goals >> a_goals >> extra_time;
    
		for(int i = 0; i < h_goals; i++)
			*infile >> h_scorers[i];
		for(int i = 0; i < a_goals; i++)
			*infile >> a_scorers[i];
		infile->ignore();
		return true;
	} else {
		for (int i = 0; i < 4; i++) {	// Skip past game info lines
			dummy = io.read_string(infile);
			delete [] dummy;
		}
		return (!strcmp(in_date, date));
	}
}

void Result::display() {    
    if(h_goals != -1) { // We have results from the game
        cout << "Vi har resultatene fra kampen\n";

    } else {
        cout << "Dato: " << date << '\n'; 
    }
}

void Result::write(ostream* out) {
	*out << date
	     << h_goals << ' '
	     << a_goals << '\n'
		 << extra_time << '\n';
	for (int i = 0; i < h_goals; i++)
		*out << h_scorers[i] << ' ';
	*out << '\n';
	for (int i = 0; i < a_goals; i++)
		*out << a_scorers[i] << ' ';
	*out << '\n';
}
