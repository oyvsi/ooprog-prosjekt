//	SPORTS.CPP
//	
//	Sourcecode for the Sports class.

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
Sports::~Sports() {
	delete sportlist;
}

void Sports::new_sport() {
	Sport* sprt; char* tmp_string;
	tmp_string = io.read_valid("Idrett", NAME);	//Read sportname
	sprt = new Sport(tmp_string);				//Create a new sport object
	sportlist->add(sprt);						//Add it to a list
	delete [] tmp_string;						//Clean up tmp variable.
}

void Sports::remove_sport() {
	Sport* sprt; char* tmp_string;
	tmp_string = io.read_valid("Idrett", NAME);	//Read sportname
	if (sportlist->in_list(tmp_string)){
		char* sure = io.read_valid("Er du sikker?? J/n", NAME);
		if (io.to_upper(sure[0]) == 'J'){
			if (sportlist->destroy(tmp_string))
				cout << "Idretten " << tmp_string << " ble slettet.";
		}
	} else
		cout << "Fant ikke idretten!\n";
}

void Sports::read_file() {
	char* tmp_str; Sport* tmp_sport;
	tmp_str = io.read_valid("Filnavn", NONE);

	ifstream in;
	in.open(tmp_str);
	delete [] tmp_str;
	if(in) {
		tmp_str = io.read_string(&in);
		while(!in.eof()) {
			tmp_sport = new Sport(tmp_str, &in);
			sportlist->add(tmp_sport);
			delete [] tmp_str;
			tmp_str = io.read_string(&in);
		}
		delete [] tmp_str;
	} else
		cout << "Finner ikke filen";
}

void Sports::read_results(istream* infile){
	sportname = read_string(infile, '\n');
	
	if (sportlist->in_list(sportname)){
		tmp_sport = sportlist.remove(sportname);
		tmp_sport->read_results(infile);
		sportlist->add(tmp_sport);
	} else {}
	
	
}

void Sports::write_file() {
	char* filename; 
	Sport* tmp;
	int i = 1;

	filename = io.read_valid("Filnavn", NONE);		//Read filename from user
	
	ofstream out;									//Create ofstream object
	out.open(filename);								//Open the file
	while(tmp = (Sport*) sportlist->remove_no(i)) {	//While more in list
		tmp->write(&out);							//write sport to file
		sportlist->add(tmp);						//Add it back to list
		i++;										//increment by one
	}
}
void Sports::display() {
	char* c_read = io.read_string(&cin);	//Reads what the user want to see
	int i_read;
	bool found = false;
	Sport* tmp;

	//If the user writes 'A':
	if(strlen(c_read) == 1 && (io.to_upper(c_read[0]) == 'A')) {
		if(sportlist->is_empty()) {
			cout << "Det finnes ingen idretter i systemet.\n";
		} else {
			cout << "F�lgende idretter finnes i systemet:\n";
			sportlist->display_list();		//Display all players
		}
	} else {	//If the user writes something else (read: a text)
		//Loop trough all players, and look for the one with the right name.
		for(int i = 1; i <= sportlist->no_of_elements(); i++) {
			tmp = (Sport*) sportlist->remove_no(i);	//Pick player i out.   
			if(tmp->name_is(c_read)) {	//If it is the right name,
				tmp->display_all();		//Display it, and
				found = true;			//mark that we found something.
			}
			sportlist->add(tmp);		//Put the player back in the list.
		}
		if(!found)	//If we did'nt find a player, write a error message.
			cout << "Det finnes ingen idretter med dette navnet";
	}
	delete [] c_read;	//Delete the string we read in.
}
void Sports::add_division() {
	char* team;
	Sport* tmp_sport;

	team = io.read_valid("Idrett", NAME);
	if(sportlist->in_list(team)) {
		tmp_sport = (Sport*) sportlist->remove(team);
		tmp_sport->add_division();
		sportlist->add(tmp_sport);
	} else {
		cout << "Finner ikke idretten!\n";
	}
	delete [] team;
}

void Sports::remove_division(){
	char* tmp_str;
	Sport* tmp_sport;

	tmp_str = io.read_valid("Idrett", NAME);
	if(sportlist->in_list(tmp_str)) {
		tmp_sport = (Sport*) sportlist->remove(tmp_str);
		tmp_sport->remove_division();
		sportlist->add(tmp_sport);
	} else {
		cout << "Finner ikke idretten!\n";
	}
	delete [] tmp_str;
}

void Sports::term_list() {
	char* sport, * filename;
	Sport* tmp_sport;
	ostream* out;

	filename = io.read_valid("Filnavn (tomt for skjerm)", NONE);
	if(strlen(filename) == 0) {
		out = &cout;
	} else {
		out = new ofstream(filename);
	}

	sport = io.read_valid("Idrett", NAME);
	if(sportlist->in_list(sport)) {
		tmp_sport = (Sport*) sportlist->remove(sport);
		tmp_sport->term_list(out);
		sportlist->add(tmp_sport);
	} else {
		cout << "Finner ikke idretten\n";
	}

	if(out != &cout)
		delete out;
}