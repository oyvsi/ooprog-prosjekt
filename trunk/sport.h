/*  SPORT.H

*/

#ifndef __SPORT_H
#define __SPORT_H

#include <fstream>
#include "global.h"
#include "listtool2.h"

class Division;	// forward declaration
using namespace std;

class Sport : public Text_element {
	private:
//		char* text;
		List* divisionlist;
		int tabletype;
		Division* get_division();

	public:
		Sport();
		Sport(char* name);
		Sport(char* name, istream* input);
		~Sport();

		virtual void display();
		void display_all();
		void display_name(ostream* out);
		bool read_results(istream* infile, bool update);
		void write_results(ostream* outfile);
		void write(ostream* out);
		bool name_is(char* nvn);
		void add_division();
		void remove_division();
		void remove_player(int player_no);
		void term_list(ostream* out);
		void result_list(ostream* out, char typ);
		void write_top_ten();
		void write_team();
		void edit_team();
};

#endif
