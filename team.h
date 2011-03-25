#ifndef __TEAM_H
#define __TEAM_H
#include <fstream>
#include "global.h"

class Team {
	private:
		char* name;
		char* address;
		int players[MAXPLAYERS];
		int no_players;
	public:
        Team();
        Team(std::ifstream* infile);
        ~Team();

        void add_player(int player_no);
        void rem_player(int player_no);        

};

#endif