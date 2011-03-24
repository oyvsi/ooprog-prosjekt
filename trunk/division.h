#ifndef __DIVISION_H
#define __DIVISION_H

#include "global.h"
#include "team.h"
#include "result.h"

class Division : public Text_element {
	private:
//		char* text;
		int no_teams;
		Team* teams[MAXTEAMS];
		Result* results;	//Matrix shall be created dynamically
	public:
        Division();
        Division(char *name, std::ifstream* infile);
        ~Division();
    
        virtual void display();


};

#endif