#ifndef __PLAYERS_H
#define __PLAYERS_H

#include "listtool2.h"

class Players {
	private:
		int last_used;
		List* playerlist;
	public:
		Players();
		~Players();

		void new_player();
		bool remove_player(char* c_read);
		void display();
};

#endif