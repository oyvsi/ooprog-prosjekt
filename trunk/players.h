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

		void new_player();
		bool remove_player();
		void write_file();
		void display();
};

#endif