#include <iostream>

#include "players.h"
#include "player.h"
#include "global.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

extern IOfunc io;

Players::Players() {
	last_used = 0;
	playerlist = new List(Sorted);
}
Players::~Players() {
	delete playerlist;
}
void Players::new_player() {
	Player* tmp;
	tmp = new Player(++last_used);
	playerlist->add(tmp);
}
void Players::display() {
	char* c_read = io.read_string(&cin);
	int i_read;
	bool found = false;
	Player* tmp;

	if(strlen(c_read) == 1 && (c_read[0] == 'a' || c_read[0] == 'A')) {
		playerlist->display_list();
	} else if (io.is_number(c_read)) {
		i_read = atoi(c_read);
		tmp = (Player*) playerlist->remove(i_read);
		tmp->display_all();
		playerlist->add(tmp);
	} else {
		for(int i = 1; i <= playerlist->no_of_elements(); i++) {
			tmp = (Player*) playerlist->remove_no(i);
			if(tmp->name_is(c_read)) {
				tmp->display_all();
				found = true;
			}
			playerlist->add(tmp);
		}
		if(!found)
			cout << "Det finnes ingen spiller med dette navnet";
	}
}