//	SPORT.CPP
//
//	Sourcecode for the Sport class.

#include <iostream>
#include <fstream>
#include <string.h>

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
Sport::Sport(char* name) : Text_element(name) { // Oppretter ny idrett
	divisionlist = new List(Sorted);				//Create the list

	cout << "\t\tHvilken tabelltype skal brukes?\n"
		 << "\t\t1 - \"2-1-0\"\n"
		 << "\t\t2 - \"3-1-0\"\n"
		 << "\t\t3 - \"3-2-1-0\"\n";
	tabletype = io.read_number("Tast inn et valg", 1, 3);	//Read tabletype
}
Sport::Sport(char* name, istream* input) : Text_element(name) { // Ny idrett fra fil
	divisionlist = new List(Sorted);				//Create the list
	int no_divisions; char* divname;
	Division* tmp_div;
	*input >> tabletype >> no_divisions;
	input->ignore();
	for(int i = 1; i <= no_divisions; i++) {    // for alle divisjoner
		divname = io.read_string(input);        //      legg til divisjon
		tmp_div = new Division(input, divname);
		divisionlist->add(tmp_div);
		delete [] divname;
	}
}
Sport::~Sport() {
	delete divisionlist;
}
void Sport::display() { // Skriver ut idrett
	cout << '\t' << text << " (" << divisionlist->no_of_elements()
		 << " avdelinger) - Tabellform:";
	switch (tabletype) {
		case 1: cout << "2-1-0\n"; break;
		case 2: cout << "3-1-0\n"; break;
		case 3: cout << "3-2-1-0\n"; break;
	};
}

void Sport::display_name(ostream* out) {
    *out << text;
}

void Sport::display_all() {
	display();
	divisionlist->display_list();
}
void Sport::write(ostream* out) {   //  Skriver ut idrett
	Division* tmp; int i = 1;
	*out << text << '\n' << tabletype << '\n'
		 << divisionlist->no_of_elements() << '\n';
	while(tmp = (Division*) divisionlist->remove_no(i)) {   // Alle divisjoner
		tmp->write(out);
		divisionlist->add(tmp);
		i++;
	}
}

bool Sport::read_results(istream* infile, bool update){ // Leser resultater fra fil
	int no_div;      // Antall divisjoner
	bool read_ok = true;            // Return-verdi
	char* divisionname;
	Division* tmp_div;
	int i = 0;
	no_div = io.lines_in_level(infile, 1);
	while (read_ok && i < no_div) {                                                 // Les alle divisjoner:
		divisionname = io.read_string(infile, '\n');
		if (divisionlist->in_list(divisionname)){
			tmp_div = (Division*) divisionlist->remove(divisionname);
			read_ok = tmp_div->read_results(infile, update);
			divisionlist->add(tmp_div);
		} else {
			read_ok = false; // feil på fil
			cout << "Divisjonen " << divisionname << " finnes ikke!\n";
		}
		i++;
		delete [] divisionname;
	}
	return read_ok;
}

void Sport::write_results(ostream* outfile){    // Skriver resultater til fil
	Division* tmp_div;

    for (int i = 1; i <= divisionlist->no_of_elements(); i++){  // For alle divisjoner
			tmp_div = (Division*) divisionlist->remove_no(i);
			tmp_div->write_results(outfile);    // Skriv resultater
			divisionlist->add(tmp_div);
    }
}

bool Sport::name_is(char* nvn) {    // Returnerer om navn == nvn
	if(strcmp(nvn, text) == 0)
		return true;
	else
		return false;
}
void Sport::add_division() {    // Legg til divisjon
	char* divisionname, * filename;
	Division* tmp_division;

	divisionname = io.read_valid("Divisjon", NONE); // Les navn
	if(divisionlist->in_list(divisionname)) {
		cout << "Divisjonen finnes fra f¯r!\n";
	} else {
		filename = io.read_valid("Filnavn", NONE);
		ifstream in(filename);
		if(in) {
			tmp_division = new Division(&in, divisionname); // Ny divisjon fra fil
			divisionlist->add(tmp_division);
		} else {
			cout << "Filen \"" << filename << "\" Finnes ikke!\n";
		}
		delete [] filename;
	}
	delete [] divisionname;
}

void Sport::remove_division() { // fjerner divisjon
	char* divisionname;
	Division* tmp_division;

	divisionname = io.read_valid("Divisjon", NONE); // Les navn
	if(divisionlist->in_list(divisionname)){
		char* sure = io.read_valid("Er du sikker?? J/n", NAME);
		if (io.to_upper(sure[0]) == 'J'){
			if (tmp_division = (Division*) divisionlist->remove(divisionname)) {
				delete tmp_division;
				cout << "Divisjonen " << divisionname << " ble slettet.";
			}
		}
	} else
		cout << "Fant ikke divisjonen!\n";
	delete [] divisionname;
}

void Sport::remove_player(int player_no) {  // Fjern spiller
	Division* div_ptr;
	for (int i = 1; i <= divisionlist->no_of_elements(); i++) { // for alle divisjoner
		div_ptr = (Division*) divisionlist->remove_no(i);
		div_ptr->remove_player(player_no);  // Fjern spiller fra divisjon
		divisionlist->add(div_ptr);
	}
}

void Sport::term_list(ostream* out) {   // Sriv terminliste
	char* division;
	Division* tmp_division;
	division = io.read_valid("Divisjon", NAME);
	if(divisionlist->in_list(division)) {
		tmp_division = (Division*) divisionlist->remove(division);
		tmp_division->term_list(out);   // skriv terminliste for divisjon
		divisionlist->add(tmp_division);
	} else {
		cout << "Finner ikke divisjonen\n";
	}
	delete [] division;
}
void Sport::result_list(ostream* out, char typ) {   // Skriver ut resultater/tabell for en divisjon
	char* division, * date;
	Division* tmp_division;

	division = io.read_valid("Divisjon", NAME);
	if(typ == 'K') date = io.read_valid("Dato", NONE);

	if(strlen(division) == 0) {
		for(int i = 1; i <= divisionlist->no_of_elements(); i++) {
			tmp_division = (Division*) divisionlist->remove_no(i);
			if(typ == 'K') 	tmp_division->result_list(out, date);
			if(typ == 'T') 	tmp_division->table(out, tabletype);
			divisionlist->add(tmp_division);
		}
	} else if (divisionlist->in_list(division)) {
		tmp_division = (Division*) divisionlist->remove(division);
			if(typ == 'K') 	tmp_division->result_list(out, date);
			if(typ == 'T') 	tmp_division->table(out, tabletype);
		divisionlist->add(tmp_division);
	} else
		cout << "Finner ikke divisjonen";

	delete [] division;
	if(typ == 'K') delete [] date;
}

Division* Sport::get_division() {
	Division* div_ptr = NULL;
	char* div_name = io.read_valid("Divisjon", NAME);

	div_ptr = (Division*) divisionlist->remove(div_name);
	if (div_ptr)
		divisionlist->add(div_ptr);
	else
		cout << "Divisjonen " << div_name << " finnes ikke!\n";
	delete [] div_name;
	return div_ptr;
}

void Sport::write_top_ten(){    // Skriver toppscorerliste
	Division* div_ptr = get_division();
	if (div_ptr)
		div_ptr->write_top_ten();
}

void Sport::write_team() {
	Division* div_ptr = get_division();
	if (div_ptr)
		div_ptr->write_team();
}

void Sport::edit_team() {
	Division* div_ptr = get_division();
	if (div_ptr)
		div_ptr->edit_team();
}

