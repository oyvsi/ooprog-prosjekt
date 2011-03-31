#ifndef __RESULT_H
#define __RESULT_H

struct tableobject;
#include <vector>
#include "global.h"
#include "division.h"

using namespace std;

class Result {
	private:
		char date[DATELEN];
		int h_goals;
		int a_goals;			//(GUESTS)? According to wikipedia away team is the correct term
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
        void display();
		void table_add(tableobject* home, tableobject* away, int type);

};

#endif
