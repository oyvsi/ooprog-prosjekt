#ifndef __PLAYER_H
#define __PLAYER_H

#include <fstream>
#include "listtool2.h"

using namespace std;

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
		void display_all();
		void write(ostream* out);
		bool name_is(char* inname);
};

#endif