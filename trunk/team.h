#ifndef __TEAM_H
#define __TEAM_H
#include <fstream>
#include "global.h"

using namespace std;

class Team {
private:
    char* name;
    char* address;
    int player_nos[MAXPLAYERS];
    int no_players;
public:
    Team();
    Team(istream* infile);
    char* get_team();
    ~Team();
    
	void write(ostream* out);
    void add_player(int player_no);
    void rem_player(int player_no);
	void display();
    
};

#endif