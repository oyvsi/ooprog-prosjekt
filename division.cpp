/*  DIVISION.CPP

*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string.h>
#include "listtool2.h"
#include "division.h"
#include "iofunc.h"
#include "players.h"

extern IOfunc io;
extern Players players;

Division::Division() {
	cout << "DIVISION.CPP - WARNING!! - "	// Should never be called
	<< "This constructor should "	
	<< "never be called";
}
	//Constructor reads division from file
Division::Division(istream* infile, char* divname) : Text_element(divname) { 
    no_teams = 0;
    int h_team_no, a_team_no;
    char* h_team;
    char* a_team;

    *infile >> no_teams; infile->ignore();
    if(no_teams <= MAXTEAMS) {					// Check that we have room for all
        results = new Result**[no_teams];       // Create array for home-teams
        for(int i = 0; i < no_teams; i++) {		// Loop through the teams
            teams[i] = new Team(infile);        // Create team-object. From there players are added
            results[i] = new Result*[no_teams]; // Create array for away-teams
            for (int j = 0; j < no_teams; j++)	// Inner loop for 2d
                results[i][j] = new Result;     // End result object
        }

			// Create schedule
        for(int i = 0; i < (no_teams*no_teams)-no_teams; i++) {    
			h_team = io.read_string(infile);	// Reads from file
            a_team = io.read_string(infile);
			h_team_no = get_team(h_team);		// Number in array
            a_team_no = get_team(a_team);
            if(h_team_no != -1 && a_team_no != -1)	// Check that team exists
                results[h_team_no][a_team_no]->set_date(io.read_string(infile));
            else
                cout << "Feil: laget " << ((h_team_no == -1) ? h_team : a_team)
					 << " eksisterer ikke!\n";
			delete [] h_team;	// Deallocate memory
			delete [] a_team;
        }

    }
    else {
        cout << "Feil: antall lag kan ikke overgå " << MAXTEAMS << '\n';
    }
}

Division::~Division() {    // Deallocates memory
    for(int i = 0; i < no_teams; i++) {	  // Loop teams
		delete [] teams[i];				  // Team obj
        for(int j = 0; j < no_teams; j++) // inner loop
            delete results[i][j];		  // Delete on actual result obj
        delete [] results[i];			  // Ptrs to array
    }
    delete [] results;					  // First ptr
}

int Division::get_team(char* name) {        // Finds team_no from name
    for(int i = 0; i < no_teams; i++) {
        if(!strcmp(teams[i]->get_team(), name))
            return i;
    }
    return -1;	// No match
}

void Division::display() {	// Menu-option i. Displays div. info and all teams
	cout << "Navn: " << text << '\n';
	cout << "Ant. lag: " << no_teams << '\n';
	for (int i = 0; i < no_teams; i++)
		teams[i]->display();
}
	//Menu option L. Displays matrix with scheduled matches' date or result
void Division::term_list(ostream* out) {    
    char date[DATELEN];

    for (int i = 0; i < no_teams; i++)	// Loop teams for home team (columns)
        *out << "\t\t" << teams[i]->get_team();   
    *out << '\n';
    for (int i = 0; i < no_teams; i++) {       // Loop teams for date/result 
        *out << teams[i]->get_team();		   // Display away team name (rows)
        for (int j = 0; j < no_teams; j++) {   // Inner loop of teams
            *out << "\t\t";
            if (i != j) {					   // Team will not play itself
				results[i][j]->get_date(date); 	
				if (results[i][j]->get_hgls() == -1) // If no results, show date
					*out << date[6] << date[7] << '/' << date[4] << date[5];
				else	// Game result is registered. Display it
					*out << results[i][j]->get_hgls() << '-'
					<< results[i][j]->get_agls();
			}
        }
        *out << '\n';
    }
}
	// Menu option K. Show games played on user-specified date. Called from sport
void Division::result_list(ostream* out, char* in_date) {   
    char date[DATELEN];
    int h_goals;
	char* h_team, * a_team;
    for (int i = 0; i < no_teams; i++) {	  // Home teams
        for (int j = 0; j < no_teams; j++) {  // Away teams
            if(i != j) {					  // No team will play itself
				results[i][j]->get_date(date); 
				if (!strcmp(date, in_date)) {  // Check user date vs match date
					h_team = teams[i]->get_team(); // Get and display team names
					a_team = teams[j]->get_team();
					*out << h_team << " - " << a_team;
					h_goals = results[i][j]->get_hgls(); 
					if (h_goals != -1)			// Check for registered result		
						*out << " - " << h_goals << "-"	
						<< results[i][j]->get_agls() << endl;
                    else
                        *out << " Ikke spilt." << endl;
				}

			}
        }
    }
}
	// Menu option R - read results from userfile + used for reading programdata
bool Division::read_results(istream* in, bool update) { 
	bool valid = true;
	char* date;
	char* h_team, * a_team;
	int i, j, h_team_no, a_team_no, no_dates, no_games;
	no_dates = io.lines_in_level(in, 2);  // Check file for dates
	i = 0;
	while (valid && i < no_dates) { // loop all dates
		date = io.read_string(in, '\n');
		no_games = io.lines_in_level(in, 3)/2; // Games á date. Two names; so / 2
		j = 0;
		while (valid && j < no_games) {		// loop all games at date
			h_team = io.read_string(in);    // team names
			a_team = io.read_string(in);
			h_team_no = get_team(h_team);   // no in team-array
			a_team_no = get_team(a_team);
				// Ensure that both teams exists
			if (h_team_no != -1 && a_team_no != -1) {  
				// Check if dates match and skip result lines. Read upon updating
				if(results[h_team_no][a_team_no]->read_result(in, date, update)) {
					// Check if we have a result stored already
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

void Division::write(ostream* out) {	// Write division data to file
	char date[DATELEN];
	*out << DIVLVL << text << '\n';
	*out << DIVLVL << no_teams << '\n';

	for (int i = 0; i < no_teams; i++)	// Each team write it's own data
		teams[i]->write(out);
										  // Schedule
	for (int i = 0; i < no_teams; i++) {    // Loop home teams
		for (int j = 0; j < no_teams; j++) {  // Loop away teams
			if(i != j) {					 // home team won't be same as away
				results[i][j]->get_date(date);	// Write game data
				*out << TEAMLVL << teams[i]->get_team() << '\n';
				*out << TEAMLVL << teams[j]->get_team() << '\n';
				*out << TEAMLVL << date << '\n';
			}
		}
	}
}

Team* Division::get_team() { // Ask user for team name and return ptr to object
	Team* team_ptr = NULL;
	char* team_name = io.read_valid("Lag", NAME);
	int team_no = get_team(team_name);
	if(team_no != -1)
		team_ptr = teams[team_no];	// We got a match
	else
		cout << "Laget " << team_name << " finnes ikke!\n";
	delete [] team_name;

	return team_ptr;
}

void Division::write_team() {
	Team* team_ptr = get_team();
	if(team_ptr)
		team_ptr->write_team();
}

void Division::edit_team() { // Menu option E.
	Team* team_ptr = get_team(); // Ask for team name
	if(team_ptr)				
		team_ptr->edit_team();	 // The team will take it from here
}

void Division::remove_player(int player_no) {  // Remove a player for all teams
	for (int i = 0; i < no_teams; i++)		  // Loop all teams and remove
		teams[i]->remove_player(player_no);   
}

void Division::write_results(ostream* out) {	// Write all results
	char date[DATELEN];
	io.write_blank(out, LEVEL_BLANKS*1); // Indent to level 1
	*out << text << '\n';	// Write division name
    for (int i = 0; i < no_teams; i++) {	// Home team
		for (int j = 0; j < no_teams; j++) {	// Away team
			if(i != j) {	// No, you can't play against yourself. 
				if (results[i][j]->get_hgls() != -1) {	// write games with resutls
					results[i][j]->get_date(date);
					io.write_blank(out, LEVEL_BLANKS*2); // Indent to level 2
					*out << date << '\n';				 // here comes the date	
					io.write_blank(out, LEVEL_BLANKS*3); // Indent to level 3
					*out << teams[i]->get_team() << '\n'; // Team names
					io.write_blank(out, LEVEL_BLANKS*3);
					*out << teams[j]->get_team() << '\n'; 
					results[i][j]->write(out);	// Result obj will write the rest
				}
			}
		}
	}
}

void Division::table(ostream* out, int type) {
	tableobject* table[MAXTEAMS];
	tableobject* tmp_tobj;
	int i, j;

	//Creates a emty table
	for(i = 0; i < no_teams; i++)
		table[i] = new tableobject(teams[i]);

	//Collects all the results
	for(i = 0; i < no_teams; i++)
		for(j = 0; j < no_teams; j++)
			if(i != j)
				results[i][j]->table_add(table[i], table[j], type);

	//Sorts the table
	for(i = 1; i < no_teams; i++) {
		if(table[i]->score < table[i-1]->score) continue;
		tmp_tobj = table[i];
		j = i - 1;
		while(j >= 0 && table[j]->score < tmp_tobj->score)
			table[j+1] = table[j--];
		table[j+1] = tmp_tobj;
	}

	//Displays the table
	*out << " #   Lagnavn                      "
		 << " S  U  T  M  Poeng\n";
	for(int i = 0; i < no_teams; i++) {
		*out << right << setw(4) << i+1 << ": "
			 << left << setw(30) << table[i]->team->get_team()
			 << setw(3) << table[i]->no_win
			 << setw(3) << table[i]->no_draw
			 << setw(3) << table[i]->no_loss
			 << setw(3) << table[i]->no_goals
			 << setw(6) << table[i]->score << '\n';
	}
}

void Division::write_top_ten() {                // Skriver topp ti-liste over målscorere
	cout << "Filnavn (blankt for skjerm): ";
	char* filename = io.read_string(&cin);
	cout << "Lag (blankt for alle): ";
	char* teamname = io.read_string(&cin);

	vector<int> goalscorers, * temp_vec;        // vector som inneholder ID til alle målscorerne
	vector<int>::iterator vec_it;               //   (antall mål for ID == antall forekomster av ID)

	int top_ten[10];			// array for topp ti-lista
	int no_goals[10];			// antall mål i hver posisjon for topp ti-lista
	int player_goals = 0;       // antall mål til den spilleren vi teller for
	int current_player;         // spilleren vi teller for

                                            // Nullstiller arrayene:
	memset(top_ten, 0, sizeof(top_ten));
	memset(no_goals, 0, sizeof(no_goals));

	for(int i = 0; i < no_teams; i++){          // For alle kamper:
  		for(int j = 0; j < no_teams; j++){
			temp_vec = results[i][j]->all_goals();  // Hent mål fra kampen
			vec_it = goalscorers.end();
			goalscorers.insert(vec_it,temp_vec->begin(),temp_vec->end());   // Legg til i vectoren
			delete temp_vec;
		}
	}

	if (strlen(teamname) > 1){			// DERSOM LAGNAVN:
		int teamidx = get_team(teamname); // hent lagindex

		if (teamidx != -1){
			for (int i = 0; i < goalscorers.size();){  	// Ta vekk folk som ikke er på laget
				if (teams[teamidx]->get_player(goalscorers[i]) == -1)
					goalscorers.erase(goalscorers.begin() + i);
                else
                    ++i;
			}
		} else {
			cout << "Feil lagnavn!\n";
		}
	}

	sort(goalscorers.begin(), goalscorers.end());   // Sorter slik at lavest ID ligger først
                                                    //   og LIK ID LIGGER ETTER HVERANDRE (viktig)
	for (int i = 0; i < goalscorers.size();){   // For alle mål
		current_player = goalscorers[i];        // Hent første ID
		while (i < goalscorers.size() && current_player == goalscorers[i]){  // for antall forekomster av denne ID
			++player_goals;                   				 // Legg til mål
			++i;
		}
		int position = 0;                           // Topp-ti posisjon, 0 er høyest
		while(player_goals < no_goals[position]){
			++position;                             // flytt et hakk ned dersom færre mål
		}
		if (position <= 9){                         // Dersom vi er innenfor topp ti
			int y = 9 - position;                   // Flytt andre spillere nedover i lista:
			while (y > 0){
				int a = position + y;
				int b = position + (--y);
				no_goals[a] = no_goals[b];
				top_ten[a] = top_ten[b];
			}
			no_goals[position] = player_goals;      // Smett ID inn i topp ti-lista
			top_ten[position] = current_player;
		}
		player_goals = 0;                           // Klargjør for neste ID
	}

	ostream* out;   // utfil

	if (strlen(filename))                       // Dersom brukeren skrev filnavn
		out = new ofstream(filename);   // skriv til fil
	else
		out = &cout;    // skriv til skjerm

	for (int i = 0; i < 10; i++){                                 // skriv ut topp ti-liste:
		*out << i+1 << ": "; players.display_name(top_ten[i]);
		*out << ", " << no_goals[i] << " maal." << "\n";
	}

	delete [] filename;
	delete [] teamname;
}
