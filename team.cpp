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

Team::Team(istream* infile) {  //Read such things as name, address, no_players
    name = io.read_string(infile);
    address = io.read_string(infile);
    *infile >> no_players; infile->ignore();
    for(int i = 0; i < no_players; i++){
        *infile >> player_nos[i]; //= players.read_player(infile);
        infile->ignore();
		}
}

Team::~Team() {
    delete [] name;
    delete [] address;
}

char* Team::get_team() {
    return name;
}

int Team::get_player(int player_no) {
	int hit = -1;
	for(int i = 0; i < no_players; i++) {
        if(player_nos[i] == player_no)
            hit = i;
    }
	return hit;
}

void Team::add_player(int player_no) {
    if (no_players < MAXPLAYERS) {
		if (get_player(player_no != -1))
			player_nos[no_players++] = player_no;	// add after since array
		else										// begins at 0
			cout << player_no << " er allerede pÃ¥ " << name << '\n';
		} else {
			cout << name << " har " << MAXPLAYERS 
			<< " spillere, det er ikke plass til flere.\n";
		}
}

bool Team::remove_player(int player_no) {
	int hit = get_player(player_no);
    if(hit != -1) {         
        player_nos[hit] = 0;
        for(int i = hit; i < no_players; i++)   //Reaarrange array
            player_nos[i] = player_nos[i+1];
        no_players--;
		return true;
    } else {
		return false;
    }
}

void Team::write_team() {
	for (int i = 0; i < no_players; i++) 
		players.display(player_nos[i]);	
}

void Team::edit_team() {
	bool result;
	char choice;
	int player_no;
	do {
		cout << "Ã˜nsker du Ã¥ (f)jerne eller (l)egge til spiller? ";
		cin >> choice;
	} while (choice != 'f' && choice != 'l');
	
	do {
		cout << "Spillernummer: "; cin >> player_no;
	} while (!players.in_list(player_no));
	
	if (choice == 'f') {
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

void Team::write(ostream* out) {
	*out << TEAMLVL << name << '\n';
	*out << TEAMLVL << address << '\n';
	*out << TEAMLVL << no_players << '\n';
	for (int i = 0; i < no_players; i++) 
		*out << TEAMLVL << player_nos[i] << '\n';
}

bool Team::in_team(int player){					// True dersom spilleren fins på laget
	for (int i = 0; i < no_players; i++){
		if (player_nos[i] == player)
			return true;
	}
	return false;
}
