//	PLAYERS.CPP
//	
//	Sourcecode for the Players class.

#include <iostream>
#include <fstream>

#include "players.h"
#include "player.h"
#include "global.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

extern IOfunc io;

Players::Players() {	//Initializes the class
	last_used = 0;
	playerlist = new List(Sorted);
}
Players::~Players() {	//deletes the players
	delete playerlist;
}
void Players::new_player() {	//Adds a new player.
	Player* tmp;
	tmp = new Player(++last_used);	//Create a new player, and
	playerlist->add(tmp);			//  add it to the playerlist.
}
bool Players::remove_player() {
	int i_read;		
	char* c_read = io.read_string(&cin);	//Read, and store input.
	Player* tmp;

	//If c_read is a number, wa want to delete the player by number.
	if (io.is_number(c_read)) {	
		i_read = atoi(c_read);	//Convert the stirng to a number
		if(tmp = (Player*) playerlist->remove(i_read)) {
			delete tmp;			//Delete it,
			delete [] c_read;	//delete the string
			return true;		//and return true
		}
	} else	//If it is not a number, we want to delete the player by name.
		//Loop trough all players
		for(int i = 1; i <= playerlist->no_of_elements(); i++) {
			tmp = (Player*) playerlist->remove_no(i);//Pick player out of list
			if(tmp->name_is(c_read)) {		//If the name is right
				delete tmp;			//Delete the player,
				delete [] c_read;	//  delete the string
				return true;		//	and return true
			} else	//If the name was not right
				playerlist->add(tmp);	//Put it back in the list.
		}
	//If the player was not found, 
	delete [] c_read;	//delete the string
	return false;		//and return false.
}
void Players::write_file() {
	Player* tmp;
	ofstream out;				//Create ostream object
	out.open("players.dat");	//Open file
	out << last_used << '\n';	//Write out the last used number
	for(int i = 1; i <= playerlist->no_of_elements(); i++) {	//Go trough all 
		tmp = (Player*) playerlist->remove_no(i);	//players, and write them
		tmp->write(&out);							//to file, and add them
		playerlist->add(tmp);						//back to the list
	}
	cout << playerlist->no_of_elements() 
		 << " spillere ble skrevet til fil\n";	//reciete to user
	out.close();
}
void Players::display() {
	char* c_read = io.read_string(&cin);	//Reads what the user want to see
	int i_read;
	bool found = false;
	Player* tmp;

	//If the user writes 'A':
	if(strlen(c_read) == 1 && (io.to_upper(c_read[0]) == 'A')) {
		playerlist->display_list();				//Display all players
	} else if (io.is_number(c_read)) {	//If user writes a number
		i_read = atoi(c_read);						//Convert text to number
		if(tmp = (Player*) playerlist->remove(i_read)) {	//Pick player number x
			tmp->display_all();					//display it
			playerlist->add(tmp);				//Put it back in the list
			found = true;
		}
	} else {	//If the user writes something else (read: a text)
		//Loop trough all players, and look for the one with the right name.
		for(int i = 1; i <= playerlist->no_of_elements(); i++) {
			tmp = (Player*) playerlist->remove_no(i);	//Pick player i out.   
			if(tmp->name_is(c_read)) {	//If it is the right name,
				tmp->display_all();		//Display it, and
				found = true;			//mark that we found something.
			}
			playerlist->add(tmp);		//Put the player back in the list.
		}
		if(!found)	//If we did'nt find a player, write a error message.
			cout << "Det finnes ingen spiller med dette navnet";
	}
	delete [] c_read;	//Delete the string we read in.
}
int Players::read_player(istream* input) {
	Player* tmp_player;
	char* tmp_name, *tmp_address;
	int tmp_number;
	tmp_name = io.read_string(input);			//Read first string from file

	if(io.is_number(tmp_name)) {				//If the string is a number
		tmp_number = atoi(tmp_name);			//Convert it to an int
		if(!playerlist->in_list(tmp_number))	//If a player with that number
			tmp_number = 0;						//dont exist, set nr to 0

		delete [] tmp_name;						//Delete the tmp string.
		return tmp_number;						//Return playernumber, or 0.
	} else {								//If the string is not a number
		tmp_address = io.read_string(input);	//Read the second line
												//Create a new player
		tmp_player = new Player(++last_used, tmp_name, tmp_address);
		playerlist->add(tmp_player);			//Add it to a list
		delete [] tmp_name;						//Delete the tmp lines
		delete [] tmp_address;					
		return last_used;						//And return the number
	}
}
