#include <iostream>
#include <fstream>
#include "iofunc.h"
#include "players.h"
#include "team.h"


Team::Team() {
}

Team::Team(std::ifstream* infile) {  //Read such things as name, address, no_players
    IOfunc io;
    extern Players players;
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
        std::cout << name << " has " << MAXPLAYERS 
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
