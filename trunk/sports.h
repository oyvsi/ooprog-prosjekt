#ifndef __SPORTS_H
#define __SPORTS_H

#include <fstream>
#include "listtool2.h"
class Sport;	// Forward declaration

using namespace std;

class Sports {
	private:
		List* sportlist;
		Sport* get_sport();
	public:
		Sports();
		~Sports();

		void new_sport();
		void remove_sport();
		void read_file();
		bool read_results(istream* infile, bool update);
		void write_file();
		void display();
		void add_division();
		void lists(char valg);	//Valg == K || Valg == L
		void remove_division();
		void write_top_ten();
		void write_team();
		void edit_team();
};

#endif
