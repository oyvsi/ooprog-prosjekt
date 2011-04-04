#ifndef __DIVISION_H
#define __DIVISION_H

#include "global.h"
#include "team.h"
#include "result.h"
#include "listtool2.h"

using namespace std;

class Division : public Text_element {
private:
	//	char* text;
    int no_teams;
    Result*** results;
    Team* teams[MAXTEAMS];
	Team* get_team();
	int get_team(char* name);

public:
    Division();
    Division(istream* infile, char* divname);
    ~Division();
    
    void display();
	bool read_results(istream* in, bool update);
    void term_list(ostream* out);
    void result_list(ostream* out, char* in_date);
	void table(ostream* out, int type);
    void write(ostream* out);
	void write_results(ostream* out);
	void write_top_ten();
	void write_team();
	void edit_team();
	void remove_player(int player_no);
};

#endif
