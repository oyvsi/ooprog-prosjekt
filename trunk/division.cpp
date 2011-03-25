#include <fstream>
#include <iostream>
#include "listtool2.h"
#include "division.h"
#include "iofunc.h"

Division::Division() {  
}

Division::Division(std::ifstream* infile) { //Creating division from file
    IOfunc io;
    no_teams = 0;
    int h_team_no, a_team_no;
    
    *infile >> no_teams;
    if(no_teams <= MAXTEAMS) {
        text = io.read_string(infile);          // Divisionname
        results = new Result**[no_teams];       // array for home-teams
        for(int i = 0; i < no_teams; i++) {
            teams[i] = new Team(infile);        // Create team-object. From there players are added
            results[i] = new Result*[no_teams]; // array for away-teams
            for (int j = 0; j < no_teams; j++)
                results[i][j] = new Result;     // end result object
        }
        
        for(int i = 0; i < no_teams*no_teams; i++) {    // Create schedule 
            h_team_no = get_team(io.read_string(infile));
            a_team_no = get_team(io.read_string(infile));
            results[h_team_no][a_team_no]->set_date(io.read_string(infile)); 
        }
        
    }
    else {
        std::cout << "Feil: antall lag kan ikke overgå " << MAXTEAMS << '\n';
    }
}

Division::~Division() {                         // Deallocate memory
    for(int i = 0; i < no_teams; i++) {
        delete results[i];
        for(int j = 0; j < no_teams; j++)
            delete results[i][j];
    }
    delete [] results;
}

int Division::get_team(char* name) {        // Finds team_no from name
    for(int i = 0; i < no_teams; i++) {
        if(!strcpy(teams[i]->get_team(), name))
            return i;
    }
    return -1;
}

void Division::display() {
    results[0][1]->display();
    
}
