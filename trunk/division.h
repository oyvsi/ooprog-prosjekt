#ifndef __DIVISION_H
#define __DIVISION_H

#include "global.h"

class Division : public Text_element {
	private:
//		char* text;
		int no_teams;
		Team* teams[DATELEN];
		Result* results;	//Matrix shall be created dynamically
	public:

};

#endif