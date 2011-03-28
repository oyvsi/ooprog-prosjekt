#include <fstream>
#include <iostream>
#include "listtool2.h"
#include "division.h"
#include "iofunc.h"

Division::Division() {  
}

Division::Division(istream* infile, char* divname) : Text_element(divname) { //Creating division from file
    extern IOfunc io;
    no_teams = 0;
    int h_team_no, a_team_no;
    char* h_team;
    char* a_team;

    *infile >> no_teams; infile->ignore();
    if(no_teams <= MAXTEAMS) {
        results = new Result**[no_teams];       // array for home-teams
        for(int i = 0; i < no_teams; i++) {
            teams[i] = new Team(infile);        // Create team-object. From there players are added
            results[i] = new Result*[no_teams]; // array for away-teams
            for (int j = 0; j < no_teams; j++)
                results[i][j] = new Result;     // end result object
        }
        
        for(int i = 0; i < (no_teams*no_teams)-no_teams; i++) {    // Create schedule
            h_team_no = get_team(io.read_string(infile));
            a_team_no = get_team(io.read_string(infile));
            if(h_team_no != -1 && a_team_no != -1) 
                results[h_team_no][a_team_no]->set_date(io.read_string(infile)); 
            else
                cout << "Feil i iterasjon: " << i << " h_team: " << h_team << ' ' << "a_team: " << a_team << '\n';
        }
        
    }
    else {
        cout << "Feil: antall lag kan ikke overgå " << MAXTEAMS << '\n';
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
        if(!strcmp(teams[i]->get_team(), name))
            return i;
    }
    return -1;
}

void Division::display() {	// Menu-option i 
	cout << "Navn: " << text << '\n';
	cout << "Ant. lag: " << no_teams;
	for (int i = 0; i < no_teams; i++)
		teams[i]->display();
}

/*for (int i = 0; i < no_teams; i++) {	//Menu option T
 for (int j = 0; j < no_teams; j++) {
 if(i != j) { // Team will not play against itself
 cout << teams[i]->get_team() << " - " 
 << teams[j]->get_team() << " - ";
 results[i][j]->display();
 }
 }
 
 }*/ 

void Division::term_list(ostream* out) {    //Menu option L
    char date[DATELEN];
    for (int i = 0; i < no_teams; i++)
        *out << "\t\t" << teams[i]->get_team();   //Columns
    *out << '\n';
    for (int i = 0; i < no_teams; i++) {        //Rows
        *out << teams[i]->get_team();
        for (int j = 0; j < no_teams; j++) {
            *out << "\t\t";
            if (i != j) {
				results[i][j]->get_date(date);
                *out << date[6] << date[7] << '/' << date[4] << date[5];
			}
        }              
        *out << '\n';
    }        
}

void Division::result_list(ostream* out, char* in_date) {	//Menu option K
    char date[DATELEN];
    int h_goals;
    for (int i = 0; i < no_teams; i++) {
        for (int j = 0; j < no_teams; j++) {
            if(i != j) {
				results[i][j]->get_date(date);
				if (!strcmp(date, in_date)) {
					*out << teams[i]->get_team() 
						<< " - " << teams[j]->get_team() << '\n';
					h_goals = results[i][j]->get_hgls();
					if (h_goals != -1)
						*out << " - " << h_goals << "-" 
                         << results[i][j]->get_agls() << '\n';
				}
            }
        }
    }
}

bool Division::read_results(istream* in, bool update) {	// Menu option R + reading programdata
	extern IOfunc io;
	bool valid = false;
	char date[DATELEN];
	int h_team, a_team;
    in->getline(date, DATELEN);
	while (!in->eof()) {
		h_team = get_team(io.read_string(in));
		a_team = get_team(io.read_string(in));
	    in->getline(date, DATELEN);
		valid = results[h_team][a_team]->read_result(in, date, update);
		in->getline(date, DATELEN);
		if (!update && valid)
			valid = (h_team != -1 && a_team != -1);
		if(!valid)
			return false;
	}
	return true;	
}

void Division::write(ostream* out) {
	char date[DATELEN];
	*out << text << '\n';
	*out << no_teams << '\n';
	for (int i = 0; i < no_teams; i++) {
		teams[i]->write(out);
	    for (int i = 0; i < no_teams; i++) {
			for (int j = 0; j < no_teams; j++) {
				if(i != j) {
					results[i][j]->get_date(date);
					*out << teams[i]->get_team() << '\n';
					*out << teams[j]->get_team() << '\n';
					*out << date << '\n';
				}
			}	
		}
	}
}

void Division::write_results(ostream* out) {
	*out << text << '\n';
	for (int i = 0; i < no_teams; i++) {
	    for (int i = 0; i < no_teams; i++) {
			for (int j = 0; j < no_teams; j++) {
				if(i != j)
					results[i][j]->write(out);
			}	
		}
	}
}

