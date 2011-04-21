/*  TEAM.CPP

*/

#include <iostream>
#include <fstream>
#include "iofunc.h"
#include "player.h"
#include "players.h"
#include "team.h"

extern IOfunc io;
extern Players players;

Team::Team() {
}

Team::Team(istream* infile) {  // Read from file
    name = io.read_string(infile);
    address = io.read_string(infile);
    *infile >> no_players; infile->ignore();
    for(int i = 0; i < no_players; i++)	// Players reads each player
        player_nos[i] = players.read_player(infile);
}

Team::~Team() {  // Deallocate memory
    delete [] name;
    delete [] address;
}

char* Team::get_team() { // Getter for the team name
    return name;
}

int Team::get_player(int player_no) {  // Find no in array from player no
	int hit = -1;
	for(int i = 0; i < no_players; i++) {
        if(player_nos[i] == player_no)
            hit = i;  // We got a match
    }
	return hit;
}

void Team::add_player(int player_no) {
    if (no_players < MAXPLAYERS) {	// Check that we have room for another player
		if (get_player(player_no != -1))
			player_nos[no_players++] = player_no;	// inc. after since array
		else										// begins at 0
			cout << player_no << " er allerede pÃ¥ " << name << '\n';
		} else {
			cout << name << " har " << MAXPLAYERS
			<< " spillere, det er ikke plass til flere.\n";
		}
}
	// Remove player based on unique id in param
bool Team::remove_player(int player_no) {	
	int hit = get_player(player_no);	// Find no in array
    if(hit != -1) {
        for(int i = hit; i < no_players; i++)   // Reaarrange array
            player_nos[i] = player_nos[i+1];
        no_players--;
		return true;
    } else {
		return false;
    }
}

void Team::write_team() {	// Display every player on team
	for (int i = 0; i < no_players; i++)
		players.display(player_nos[i]);
}

void Team::edit_team() {	// Add/remove player from team
	bool result;
	char choice;
	int player_no;
	do {	// Get users choice
		cout << "¯nsker du Œ (f)jerne eller (l)egge til spiller? ";
		cin >> choice;
	} while (choice != 'f' && choice != 'l');

	do {	// Get valid player no
		cout << "Spillernummer: "; cin >> player_no;
	} while (!players.in_list(player_no));

	if (choice == 'f') {	// Remove the player
		result = remove_player(player_no);
		if (result)
			cout << "Fjernet spiller " << player_no << " fra " << name << '\n';
		else
			cout << "Spiller " << player_no << " er ikke med pŒ " << name << '\n';
	}
	else if (choice == 'l')
		add_player(player_no);
}

void Team::display() {
	cout << name << '\n'
		 << address << '\n'
		 << "Ant. spillere: " << no_players << '\n';
}

void Team::write(ostream* out) {	// Write team info to file
	*out << TEAMLVL << name << '\n';
	*out << TEAMLVL << address << '\n';
	*out << TEAMLVL << no_players << '\n';
	for (int i = 0; i < no_players; i++)	// Write player nos
		*out << TEAMLVL << player_nos[i] << '\n';
}
