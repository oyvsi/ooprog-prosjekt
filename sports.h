#ifndef __SPORTS_H
#define __SPORTS_H

#include <fstream>
#include "listtool2.h"

using namespace std;

class Sports {
	private:
		List* sportlist;
	public:
		Sports();
		Sports(istream* input);
		~Sports();

		void new_sport();
		void write_file();
		void display();
};

#endif