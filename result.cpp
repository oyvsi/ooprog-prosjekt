#include <iostream>
#include <fstream>
#include <vector>
#include "result.h"

Result::Result() {  // called from division 
    h_goals = -1;   // We have no results;    
}

vector<int>* Result::all_goals(){
	vector<int>* gls = new vector<int>;

	for (int i = 0; i < h_goals; i++)
		gls->push_back(h_scorers[i]);
		
	for (int i = 0; i < a_goals; i++)
		gls->push_back(a_scorers[i]);

	return gls;
}

void Result::set_date(char in_date[DATELEN]) {
    strcpy(date, in_date);
}

void Result::get_date(char in_date[]) {
    strcpy(in_date, date);
}

int Result::get_hgls() {
    return h_goals;
}

int Result::get_agls() {
    return a_goals;
}

bool Result::read_result(istream* infile, char in_date[], bool update) { 
	if (update) {
		*infile >> h_goals;
		*infile >> a_goals;
		*infile >> extra_time;
    
		for(int i = 0; i < h_goals; i++)
			*infile >> h_scorers[i];
		for(int i = 0; i < a_goals; i++)
			*infile >> a_scorers[i];
		infile->ignore();
		return true;
	} else {
		return (h_goals == -1 && !strcmp(in_date, date));
	}
}

void Result::display() {    
    if(h_goals != -1) { // We have results from the game
        cout << "Vi har resultatene fra kampen\n";

    } else {
        cout << "Dato: " << date << '\n'; 
    }
}

void Result::table_add(tableobject* home, tableobject* away, int tabletype) {
	int win_points = (tabletype == 1 || (tabletype == 3 && extra_time)) ? 2 : 3;
	int draw_points = 1;
	int loss_points = 0;
	
	if(h_goals > a_goals) {
		home->no_win++; away->no_loss++;
		home->score += win_points;
		away->score += loss_points;
	} else if (h_goals < a_goals) {
		home->no_loss++; away->no_win++;
		home->score += loss_points;
		away->score += win_points;
	} else {
		home->no_draw++; away->no_draw++;
		home->score += draw_points;
		away->score += draw_points;
	}
	home->no_goals += h_goals;
	away->no_goals += a_goals;
}

void Result::write(ostream* out) {
	*out << date;
	*out << h_goals << '\n';
	*out << a_goals;
	for (int i = 0; i < h_goals; i++)
		*out << h_scorers[i] << ' ';
	for (int i = 0; i < a_goals; i++)
		*out << a_scorers[i] << ' ';
	*out << '\n';
}
