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

bool Sport::read_results(istream* infile, bool update){
	int no_div;							// Antall divisjoner
	bool read_ok = true;		// Return-verdi
	char* divisionname;
	Division* tmp_div;

	*infile >> no_div; infile->ignore();
	cout << "Las ant. div: " << no_div << endl;
	
	if (divisionlist->no_of_elements() == no_div){		// Dersom dette stemmer
		for (int i = 0; i < no_div; i++){								// Les alle divisjoner:
			divisionname = io.read_string(infile, '\n');
			if (divisionlist->in_list(divisionname)){
				tmp_div = (Division*) divisionlist->remove(divisionname);
				tmp_div->read_results(infile, update);		// flash?
				divisionlist->add(tmp_div);
			} else read_ok = false;												// feil p� fil
		}
	} else read_ok = false;
	
	return read_ok;
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
		cout << "Divisjonen finnes fra f�r!\n";
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
void Sport::result_list(ostream* out) {
	char* division, * date;
	Division* tmp_division;
	
	division = io.read_valid("Divisjon", NAME);
	date = io.read_valid("Dato", NONE);
	
	if(strlen(division) == 0) {
		for(int i = 1; i <= divisionlist->no_of_elements(); i++) {
			tmp_division = (Division*) divisionlist->remove_no(i);
			tmp_division->result_list(out, date);
			divisionlist->add(tmp_division);
		}
	} else if (divisionlist->in_list(division)) {
		tmp_division = (Division*) divisionlist->remove(division);
		tmp_division->result_list(out, date);
		divisionlist->add(tmp_division);
	} else
		cout << "Finner ikke divisjonen";

	delete [] division;
	delete [] date;
}

void Sport::write_top_ten(){
	Division* current_division;
	char* divisionname = io.read_valid("Divisjon", NONE);
	current_division = (Division*) divisionlist->remove(divisionname);
	current_division->write_top_ten();
	divisionlist->add(current_division);
}

