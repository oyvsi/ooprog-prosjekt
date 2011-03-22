#ifndef __PLAYER_H
#define __PLAYER_H

#include "listtool2.h"

class Player : public Num_element {
	private:
//		int number
		char* name;
		char* address;
	public:
		Player();
		Player(int n);
		~Player();

		virtual void display();
};

#endif