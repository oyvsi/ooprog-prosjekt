//Prosjektoppgaven - Gruppe O

#include <iostream>
#include <fstream>

#include "global.h"
#include "iofunc.h"
#include "players.h"
#include "sports.h"
#include "sport.h"

using namespace std;

IOfunc io;
Players players;
Sports sports;

void read_all_file();
void write_all_file();
void display_menu();
void new_psd();					// New player/sport/division
void remove_psd();
void read_results();
void write_results();

int main() {
	read_all_file();

	char choice;
	display_menu();

	bool quit = false;
	while (!quit){
		cout << "\n\tKommando: "; cin >> choice;
		cin.ignore();
		switch (io.to_upper(choice)){
			case 'S' : players.display();	break;
			case 'I' : sports.display();	break;
			case 'N' : new_psd();			break;
			case 'F' : remove_psd();		break;
			case 'L' : sports.lists('L');	break;
			case 'K' : sports.lists('K');	break;
			case 'T' : sports.lists('T');	break;
			case 'R' : read_results();		break;
			case 'D' : sports.write_team(); break;
			case 'E' : sports.edit_team();  break;
			case 'C' : sports.write_top_ten(); break;
			case 'Q' : quit = true;			break;
			default  : display_menu(); break;
		}
	}
	write_all_file();
	return 0;
}

void read_all_file(){   // Leser inn hele datastrukturen fra fil

	int no_pls;         // ant spillere

	ifstream i_players(PLAYERSFILE);

	if (!i_players)
        return;

	i_players >> no_pls;
	i_players.ignore();

	for (int i = 0; i < no_pls; i++){   // Les alle spillere:
		players.read_player(&i_players, true);
	}

	sports.read_file(); // Les idretter
	read_results(); // Les resultater
}

void write_all_file(){  // Skriver hele datasturukturen til fil
	sports.write_file();
	players.write_file();
	write_results();
}

void display_menu(){
	cout <<

	"Menyvalg:\n\n"
	"S - skriv spiller / alle spillere\n"
	"I - skriv idrett / alle idretter\n"
	"N - ny spiller/idrett/divisjon\n"
	"F - fjern s/i/d\n"
	"L - skriv terminliste for divisjon\n"
	"K - skriv resultat av kamper en gitt dato for i/d\n"
	"T - skriv tabell\n"
	"R - les resultatliste fra fil\n"
	"D - sriver data om alle spillerne på et gitt lag\n"
	"E - legg til/ fjer spillere på et lag\n"
	"C - skriv toppscorere\n";
}

void new_psd(){ // Ny spiller/idrett/divisjon
	char choice;
	cin >> choice; cin.ignore();

	switch (io.to_upper(choice)){
		case 'S'	: players.new_player(); 	break;
		case 'I'	: sports.new_sport();			break;
		case 'D'	: sports.add_division();	break;
	}
}

void remove_psd(){ // Fjern spiller/idrett/divisjon
	char choice;
	cin >> choice; cin.ignore();

	switch (io.to_upper(choice)){
		case 'S'	: players.remove_player(); 	break;
		case 'I'	: sports.remove_sport();	break;
		case 'D'	: sports.remove_division();	break;
	}
}

void read_results(){                                        // leser inn resultater fra fil
	ifstream* infile = new ifstream("results.dta");

	if (*infile){
		if (sports.read_results(infile, false)) {	// Leser uten å oppdatere resultater
			infile->clear();						// Fjern filflagg
			infile->seekg(0, ios::beg);             // GŒ til starten av fila
			sports.read_results(infile, true);		// Ingen feil funnet, oppdater res.
		} else {
			cout << "Fila inneheld feil, fool!\n";
		}
	}
	else {
		cout << "Kunne ikke Œpne fila 'results.dta'";
	}
}

void write_results(){                                   // skriver resultater til fil
	ofstream* outfile = new ofstream("results_ut.dta");

	if (*outfile){
        sports.write_results(outfile);		// skriv res
    } else {
        cout << "Kunne ikke Œpne fila 'results.dta'";
	}
}

