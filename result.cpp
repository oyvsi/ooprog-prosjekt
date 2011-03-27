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

void Result::read_results(std::istream* infile) {  //TODO: check for errors
    infile->getline(date, DATELEN);
    *infile >> h_goals;
    *infile >> a_goals;
    *infile >> extra_time;
    
    for(int i = 0; i < h_goals; i++)
        *infile >> h_scorers[i];
    for(int i = 0; i < a_goals; i++)
        *infile >> a_scorers[i];
    infile->ignore();
}



void Result::display() {    
    if(h_goals != -1) { // We have results from the game
        cout << "Vi har resultatene fra kampen\n";

    } else {
        cout << "Dato: " << date << '\n'; 
    }
}