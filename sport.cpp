//	SPORT.CPP
//	
//	Sourcecode for the Sport class.

#include <iostream>
#include <fstream>

#include "sport.h"
#include "division.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

extern IOfunc io;

Sport::Sport()  {						//This class shall 
	cout << "SPORT.CPP - WARNING!! - "	//  never be constructed
		 << "This constructor should "	//  without a parameter.
		 << "never be called";
}
Sport::Sport(char* name) : Text_element(name) {
	divisionlist = new List(Sorted);				//Create the list

	cout << "\t\tHvilken tabelltype skal brukes?\n"
		 << "\t\t1 - \"2-1-0\"\n"
		 << "\t\t2 - \"3-1-0\"\n"
		 << "\t\t3 - \"3-2-1-0\"\n";
	tabletype = io.read_number("Tast inn et valg", 1, 3);	//Read tabletype
}
Sport::Sport(char* name, istream* input) : Text_element(name) {

}
Sport::~Sport() {
	delete divisionlist;
}
void Sport::display() {
	cout << '\t' << text << " (" << divisionlist->no_of_elements()
		 << " avdelinger) - Tabellform:";
	switch (tabletype) {
		case 1: cout << "2-1-0\n"; break;
		case 2: cout << "3-1-0\n"; break;
		case 3: cout << "3-2-1-0\n"; break;
	};
}
void Sport::display_all() {
	display();
	divisionlist->display_list();
}
void Sport::write(ostream* out) {
	Division* tmp; int i = 1;
	*out << text << '\n' << tabletype << '\n';
	while(tmp = (Division*) divisionlist->remove_no(i)) {
		//tmp->write(out);
		divisionlist->add(tmp);
		i++;
	}
}
bool Sport::name_is(char* nvn) {
	if(strcmp(nvn, text) == 0) 
		return true;
	else 
		return false;
}

