#ifndef __RESULT_H
#define __RESULT_H

#include <vector>
#include "global.h"

using namespace std;

class Team;

struct tableobject {
	Team* team;
	int no_win;
	int no_draw;
	int no_loss;
	int no_goals;
	int score;

	tableobject(Team* t) {
		team = t;
		no_draw = 0;
		no_loss = 0;
		no_win = 0;
		score = 0;
		no_goals = 0;
	}
};

class Result {
	private:
		char date[DATELEN];
		int h_goals;
		int a_goals;			
		bool extra_time;
		int h_scorers[MAXGOALS];
		int a_scorers[MAXGOALS];	
	public:
        Result();
        vector<int>* all_goals();								// Returnerer vector med alle mål
        void set_date(char in_date[DATELEN]);
        void get_date(char in_date[]);
        bool read_result(istream* infile, char in_date[], bool update);
		void write(ostream* out);
        int get_hgls();
        int get_agls();
		void table_add(tableobject* home, tableobject* away, int type);

};

#endif
