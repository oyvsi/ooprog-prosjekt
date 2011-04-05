#ifndef __PLAYERS_H
#define __PLAYERS_H

#include <fstream>
#include "listtool2.h"

using namespace std;

class Players {
	private:
		int last_used;
		List* playerlist;
	public:
		Players();
		~Players();

		virtual void display();
		void display(int no);
		void display_name(int no);
		void new_player();
		bool remove_player();
		void write_file();
		int read_player(istream* input);
		bool in_list(char* name);
		bool in_list(int player_no);
		int get_id(char* name);
};

#endif
