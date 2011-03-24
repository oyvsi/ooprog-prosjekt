#include <iostream>
#include <fstream>
#include "result.h"
#include "iofunc.h"


Result::Result() {  // called from division 
    h_goals = -1;   // We have no results;    
}

void Result::read_results(std::ifstream* infile) {
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
        std::cout << "Vi har resultatene fra kampen\n";

    } else {
        std::cout << "Vi har desverre ingen resultater"; 
    }
}

/*
<date>
<h_goals> <a_goals>
<extra_time>
<h_scorer1> <h_scorer2> etc
<a_scorer1> <a_scorer2> etc */