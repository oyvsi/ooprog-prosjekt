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
    for(int i = 0; i < no_players; i++)
        player_nos[i] = players.read_player(infile);
}

Team::~Team() {
    delete [] name;
    delete [] address;
}

char* Team::get_team() {
    return name;
}

void Team::add_player(int player_no) {
    if (no_players < MAXPLAYERS) 
        player_nos[++no_players] = player_no;
    else
        cout << name << " has " << MAXPLAYERS 
        << " players, there is no room for more.";
}

void Team::rem_player(int player_no) {
    int hit = -1;
    for(int i = 0; i < no_players; i++) {
        if(player_nos[i] == player_no)
            hit = i;
    }
    if(hit != -1) {         
        player_nos[hit] = 0;
        for(int i = hit; i < no_players; i++)   //Reaarrange array
            player_nos[i] = player_nos[i+1];
        no_players--;
    } else {
        cout << "Player number " << player_no << " was not found";
    }
}

void Team::write_team() {
	for (int i = 0; i < no_players; i++) 
		players.display(player_nos[i]);	
}

void Team::display() {
	cout << name << '\n'
		 << address << '\n'
		 << "Ant. spillere: " << no_players << '\n';
}

void Team::write(ostream* out) {
	*out << name << '\n';
	*out << address << '\n';
	for (int i = 0; i < no_players; i++) 
		*out << player_nos[i] << '\n';
}
