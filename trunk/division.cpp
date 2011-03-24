#include <fstream>
#include <iostream>
#include "listtool2.h"
#include "division.h"
#include "iofunc.h"

Division::Division() {  
}

Division::Division(std::ifstream* infile) {//: Text_element(name) {
    IOfunc io;
    *infile >> no_teams;
    if(no_teams <= MAXTEAMS) {
        text = io.read_string(infile);          // Divisionname
        results = new Result**[no_teams];       // array for home-teams
        for(int i = 0; i < no_teams; i++) {
            results[i] = new Result*[no_teams]; // array for away-teams
            for (int j = 0; j < no_teams; j++)
                results[i][j] = new Result;     // end result object
        }
    }
    else {
        std::cout << "Feil: antall lag kan ikke overgå " << MAXTEAMS << '\n';
    }
}

void Division::display() {
    results[0][3]->display();
        
}

Division::~Division() {                         // Deallocate memory
    for(int i = 0; i < no_teams; i++) {
        delete results[i];
        for(int j = 0; j < no_teams; j++)
            delete results[i][j];
    }
    delete [] results;
}
