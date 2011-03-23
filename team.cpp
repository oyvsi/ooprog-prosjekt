#include <iostream>
#include <fstream>

using namespace std;
#include "team.h"


Team::Team() {
}

Team::Team(ifstream* infile) {  //Read such things as name, address, no_players

}

Team::~Team() {
    delete [] name;
    delete [] address;
}


void Team::add_player(int player_no) {
    if (no_players < MAXPLAYERS) 
        players[++no_players] = player_no;
    else
        cout << name << " has " << MAXPLAYERS 
             << " players, there is no room for more.";
}

void Team::rem_player(int player_no) {
    int hit = -1;
    for(int i = 0; i < no_players; i++) {
        if(players[i] == player_no)
            hit = i;
    }
    if(hit != -1) {
        players[hit] = 0;
        no_players--;
    } else {
        cout << "Player number " << player_no << " was not found";
    }
}
