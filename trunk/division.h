#ifndef __DIVISION_H
#define __DIVISION_H

#include "global.h"
#include "team.h"
#include "result.h"

class Division {//: public Text_element {
	private:
		char* text;
		int no_teams;
        Result*** results;
		Team* teams[MAXTEAMS];
	public:
        Division();
        Division(std::ifstream* infile);
        void display();

        ~Division();
    


};

#endif