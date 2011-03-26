#ifndef __DIVISION_H
#define __DIVISION_H

#include "global.h"
#include "team.h"
#include "result.h"
#include "listtool2.h"

class Division : public Text_element {
private:
	//	char* text;
    int no_teams;
    Result*** results;
    Team* teams[MAXTEAMS];
public:
    Division();
    Division(std::istream* infile);
    ~Division();
    
    int get_team(char* name);
    void display();
  //  void write(std::ostream* out);
    
    
};

#endif