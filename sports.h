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
		~Sports();

		void new_sport();
		void read_file();
		void write_file();
		void display();
		void term_list();
};

#endif