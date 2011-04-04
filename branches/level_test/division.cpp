#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "listtool2.h"
#include "division.h"
#include "iofunc.h"

extern IOfunc io;

Division::Division() {  
}

Division::Division(istream* infile, char* divname) : Text_element(divname) { //Creating division from file
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
        for(int j = 0; j < no_teams; j++)
            delete results[i][j];
        delete [] results[i];
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
				if (results[i][j]->get_hgls() == -1)
					*out << date[6] << date[7] << '/' << date[4] << date[5];
				else
					*out << results[i][j]->get_hgls() << '-'
					<< results[i][j]->get_agls();
			}
        }              
        *out << '\n';
    }        
}

void Division::result_list(ostream* out, char* in_date) {       //Menu option K
    char date[DATELEN];
    int h_goals;
	char* h_team, * a_team;
    for (int i = 0; i < no_teams; i++) {
        for (int j = 0; j < no_teams; j++) {
            if(i != j) {
				results[i][j]->get_date(date);
				if (!strcmp(date, in_date)) {
					h_team = teams[i]->get_team();
					a_team = teams[j]->get_team();
					*out << h_team << " - " << a_team;
					h_goals = results[i][j]->get_hgls();
					if (h_goals != -1)
						*out << " - " << h_goals << "-" 
						<< results[i][j]->get_agls() << '\n';
				}
                
			}
        }
    }
}

bool Division::read_results(istream* in, bool update) { // Menu option R + reading programdata
	bool valid = true;
	char* date;
	char* h_team, * a_team;
	int i, j, h_team_no, a_team_no, no_dates, no_games;
	no_dates = io.lines_in_level(in, 2);
	i = 0;
	while (valid && i < no_dates) { // loop all dates
		date = io.read_string(in, '\n');        
		no_games = io.lines_in_level(in, 3)/2;
		j = 0;
		while (valid && j < no_games) { // loop all games at date
			h_team = io.read_string(in);    // team names
			a_team = io.read_string(in);
			h_team_no = get_team(h_team);   // no in team-array
			a_team_no = get_team(a_team);
			
			if (h_team_no != -1 && a_team_no != -1) {       // One of the team names does not exist
				// Check if dates match
				if(results[h_team_no][a_team_no]->read_result(in, date, update)) {                              
					// Check if we have a result stored allready
					if(!update && results[h_team_no][a_team_no]->get_hgls() != -1) {        
						valid = false;
						cout << date << ": " << h_team << " - " << a_team
						<< " har allerede et innlest resultat\n";
					}
				} else {
					valid = false;
					cout << "Iflg. terminlista skal ikke " << h_team << " - " 
					<< a_team << " spilles " << date << '\n';
				}
			} else {
				valid = false;
				cout << ((h_team_no == -1) ? h_team : a_team) << " finnes ikke\n";
			}
			delete [] h_team;
			delete [] a_team;
			j++;
		}
		delete date;
		i++;
	}
	return valid;   
}

void Division::write(ostream* out) {
	char date[DATELEN];
	*out << text << '\n';
	*out << no_teams << '\n';
	for (int i = 0; i < no_teams; i++) {
		teams[i]->write(out);
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

void Division::write_results(ostream* out) {
	*out << text << '\n';
    for (int i = 0; i < no_teams; i++) {
		for (int j = 0; j < no_teams; j++) {
			if(i != j)
				results[i][j]->write(out);
		}	
	}	
}

void Division::table(ostream* out, int type) {
	tableobject* table[MAXTEAMS];
	for(int i = 0; i < no_teams; i++) {
		table[i] = new tableobject;
		table[i]->no_draw = table[i]->no_loss =
			table[i]->no_win = table[i]->score = 
			table[i]->no_goals = 0;
		table[i]->team = teams[i];
	}

	for(int i = 0; i < no_teams; i++)
		for(int j = 0; j < no_teams; j++)
			if(i != j)
				results[i][j]->table_add(table[i], table[j], type);
			
	
	
}

void Division::write_top_ten() {
	cout << "Filnavn (blankt for skjerm): ";
	char* filename = io.read_string(&cin);
	cout << "Lag (blankt for alle): ";
	char* teamname = io.read_string(&cin);
	
	vector<int> goalscorers, * temp_vec;
	vector<int>::iterator vec_it;

	int top_ten[10];			// The top-ten table
	int no_goals[10];			// Number of goals in each of the above table positions
	int player_goals = 0;
	int current_player; 
	
	memset(top_ten, 0, sizeof(top_ten));
	memset(no_goals, 0, sizeof(no_goals));

	for(int i = 0; i < no_teams; i++){
  	for(int j = 0; j < no_teams; j++){
			temp_vec = results[i][j]->all_goals();
			vec_it = goalscorers.end();
			goalscorers.insert(vec_it,temp_vec->begin(),temp_vec->end());
			delete temp_vec;
		}
	}
	
	sort(goalscorers.begin(), goalscorers.end());
  
  for (int i = 0; i < goalscorers.size();){
		current_player = goalscorers[i];	
		while (current_player == goalscorers[i]){  // S� lenge lik ID
			++player_goals;                   				 // Legg til m�l
			++i;
		}
		int position = 0;
		while(player_goals < no_goals[position]){
			++position;
		}
		if (position <= 9){
			int y = 9 - position;
			while (y > 0){
				int a = position + y;
				int b = position + (--y);
				no_goals[a] = no_goals[b];
				top_ten[a] = top_ten[b];
			}
			no_goals[position] = player_goals;
			top_ten[position] = current_player;
		}
		player_goals = 0;
	}
	
	ostream* out;
	
	if (strlen(filename))
		out = new ofstream(filename);
	else
		out = &cout;
		
	for (int i = 0; i < 10; i++){
		*out << i+1 << ": Player ID: " << top_ten[i] << ", Goals: " << no_goals[i] << "\n"; 
	}
}