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
	int get_player(int player_no);
public:
    Team();
    Team(istream* infile);
    char* get_team();
    ~Team();
    
    bool in_team(int player);
	void write(ostream* out);
    void add_player(int player_no);
    bool remove_player(int player_no);
	void display();
	void write_team();
	void edit_team();
    
};

#endif
