#include <iostream>

#include "players.h"
#include "player.h"
#include "global.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

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