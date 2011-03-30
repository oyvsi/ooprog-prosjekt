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
		Player(int n, char* in_name, char* in_address);
		~Player();

		virtual void display();
		void display_all();
		void write(ostream* out);
		bool name_is(char* inname);
		int get_number();
};

#endif