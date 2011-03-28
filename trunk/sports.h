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
		void remove_sport();
		void read_file();
		void read_result(istream* infile);
		void write_file();
		void display();
		void add_division();
		void remove_division();
		void term_list();
};

#endif
