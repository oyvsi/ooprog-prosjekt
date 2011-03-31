#ifndef __DIVISION_H
#define __DIVISION_H

class Result;
#include "global.h"
#include "team.h"
#include "result.h"
#include "listtool2.h"

using namespace std;

struct tableobject {
	Team* team;
	int no_win;
	int no_draw;
	int no_loss;
	int no_goals;
	int score;
};

class Division : public Text_element {
private:
	//	char* text;
    int no_teams;
    Result*** results;
    Team* teams[MAXTEAMS];
public:
    Division();
    Division(istream* infile, char* divname);
    ~Division();
    
    int get_team(char* name);
    void display();
	bool read_results(istream* in, bool update);
    void term_list(ostream* out);
    void result_list(ostream* out, char* in_date);
	void table(ostream* out, int type);
    void write(ostream* out);
	void write_results(ostream* out);
	void write_top_ten();
};

#endif
