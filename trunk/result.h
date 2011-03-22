#ifndef __RESULT_H
#define __RESULT_H

class Result {
	private:
		char date[DATELEN];
		int h_goals;
		int a_goals;				//Is g_goals better (GUESTS)?
		bool extra_time;
		int h_scorers[MAXGOALS];
		int a_scorers[MAXGOALS];	//Is g_scorers better (GUESTS)?
	public:

};

#endif