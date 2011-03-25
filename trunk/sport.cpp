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
	divisionlist = new List(Sorted);

	cout << "Hvilken tabelltype skal brukes?\n"
		 << "1 - \"2-1-0\"\n"
		 << "2 - \"3-1-0\"\n"
		 << "3 - \"3-2-1-0\"\n";
	tabletype = io.read_number("Tast inn et valg", 1, 3);
}
Sport::Sport(char* name, istream* input) : Text_element(name) {

}
Sport::~Sport() {
	delete divisionlist;
}
void Sport::display() {
	cout << text << '\n';
	divisionlist->display_list();
}
void Sport::write(ostream* out) {
	Division* tmp; int i = 1;
	*out << text << '\n' << tabletype << '\n';
	while(tmp = (Division*) divisionlist->remove_no(i)) {
		tmp->write(out);
		divisionlist->add(tmp);
		i++;
	}
};

