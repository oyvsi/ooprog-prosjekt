#include <iostream>
#include <fstream>

#include "sports.h"
#include "sport.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

extern IOfunc io;

Sports::Sports() {
	sportlist = new List(Sorted);
}
Sports::Sports(istream* input) {

}
Sports::~Sports() {
	delete sportlist;
}

void Sports::new_sport() {
	Sport* sprt;
	sprt = new Sport;
	sportlist->add(sprt);
}
void Sports::write_file() {
	char* filename; 
	Sport* tmp;
	int i = 1;

	filename = io.read_valid("Filnavn", NONE);
	
	ofstream out;
	out.open(filename);
	while(tmp = (Sport*) sportlist->remove_no(i)) {
		tmp->write(&out);
		sportlist->add(tmp);
		i++;
	}
}