#include <iostream>
#include <fstream>
#include "result.h"

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
	if (update) {
		*infile >> h_goals;
		*infile >> a_goals;
		*infile >> extra_time;
    
		for(int i = 0; i < h_goals; i++)
			*infile >> h_scorers[i];
		for(int i = 0; i < a_goals; i++)
			*infile >> a_scorers[i];
		infile->ignore();
		return true;
	} else {
		return (h_goals == -1 && !strcmp(in_date, date));
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
	*out << date;
	*out << h_goals << '\n';
	*out << a_goals;
	for (int i = 0; i < h_goals; i++)
		*out << h_scorers[i] << ' ';
	for (int i = 0; i < a_goals; i++)
		*out << a_scorers[i] << ' ';
	*out << '\n';
}
