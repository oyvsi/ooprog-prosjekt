#ifndef __SPORT_H
#define __SPORT_H

#include <fstream>
#include "global.h"
#include "listtool2.h"

using namespace std;

class Sport : public Text_element {
	private:
//		char* text;
		List* divisionlist;
		int tabletype;
	public:
		Sport();
		Sport(char* name);
		Sport(char* name, istream* input);
		~Sport();

		virtual void display();
		void write(ostream* out);
};

#endif