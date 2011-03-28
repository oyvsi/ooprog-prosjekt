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

Sport::Sport() : Text_element("")  {	//This class shall 
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
	divisionlist = new List(Sorted);				//Create the list
	int no_divisions; char* divname;
	Division* tmp_div;
	*input >> tabletype >> no_divisions;
	input->ignore();
	for(int i = 1; i <= no_divisions; i++) {
		//divname = io.read_string(input);
		//tmp_div = new Division(divname, input);
		//divisionlist->add(tmp_div);
		//delete [] divname;
	}
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
	*out << text << '\n' << tabletype << '\n'
		 << divisionlist->no_of_elements() << '\n';
	while(tmp = (Division*) divisionlist->remove_no(i)) {
		//tmp->write(out);
		divisionlist->add(tmp);
		i++;
	}
}

void Sport::read_result(istream* infile){
	char* divisionname;
	Division* tmp_div;
	int no_div;							// Antall divisjoner
	*infile >> no_div;
	
	
	if (divisionlist->no_in_list() == no_div){
		for (int i = 0, i < no_div, i++){
			divisionname = read_string(infile, '\n');
			if (divisionlist->in_list(divisionname)){
				tmp_division = (Division*) divisionlist->remove(divisionname);
				tmp_division->read_results();
				divisionlist->add(tmp_division);
			}
		}
	}
}


bool Sport::name_is(char* nvn) {
	if(strcmp(nvn, text) == 0) 
		return true;
	else 
		return false;
}
void Sport::add_division() {
	char* divisionname, * filename;
	Division* tmp_division;

	divisionname = io.read_valid("Divisjon", NONE);
	if(divisionlist->in_list(divisionname)) {
		cout << "Divisjonen finnes fra før!\n";
	} else {
		filename = io.read_valid("Filnavn", NONE);
		ifstream in(filename);
		if(in) {
			tmp_division = new Division(&in, divisionname);
			divisionlist->add(tmp_division);
		} else {
			cout << "Filen \"" << filename << "\" Finnes ikke!\n";
		}
		delete [] filename;
	}
	delete [] divisionname;
}

void Sport::remove_division() {
	char* divisionname;
	Division* tmp_division;

	divisionname = io.read_valid("Divisjon", NONE);
	if(divisionlist->in_list(divisionname)){
		char* sure = io.read_valid("Er du sikker?? J/n", NAME);
		if (io.to_upper(sure[0]) == 'J'){
			if (divisionlist->destroy(divisionname))
				cout << "Divisjonen " << divisionname << " ble slettet.";
		}
	} else
		cout << "Fant ikke divisjonen!\n";
	delete [] divisionname;
}

void Sport::term_list(ostream* out) {
	char* division;
	Division* tmp_division;
	division = io.read_valid("Divisjon", NAME);
	if(divisionlist->in_list(division)) {
		tmp_division = (Division*) divisionlist->remove(division);
		tmp_division->term_list(out);
		divisionlist->add(tmp_division);
	} else {
		cout << "Finner ikke divisjonen\n";
	}
}

