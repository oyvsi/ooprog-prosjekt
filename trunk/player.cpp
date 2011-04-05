//	PLAYER.CPP
//
//	Sourcecode for the Player class.

#include <iostream>
#include <fstream>
#include <string.h>

#include "player.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

extern IOfunc io;

Player::Player() : Num_element(0) {		//This class shall
	cout << "PLAYER.CPP - WARNING!! - "	//  never be constructed
		 << "This constructor should "	//  without a parameter.
		 << "never be called";
}
Player::Player(int n) : Num_element(n) {
	name = io.read_valid("Spillernavn", NAME);		//Read name and address from
	address = io.read_valid("Adresse", ADDRESS);	//  the user.
}
Player::Player(int n, char* in_name, char* in_address) : Num_element(n) {
	name = io.store_string(in_name);
	address = io.store_string(in_address);
}
Player::~Player() {			//release the memory this class used.
	delete [] name;
	delete [] address;
}
void Player::display() {	//Write out the number and name, to a list over
	cout << endl << name << " (" << number << ")";		//  several players.
}
void Player::display_all() {			//Writes out all the playerdata.
	cout << number << ": " << name		//  Used where data from only one
		 << '\n' << address << '\n';	//  player is displayed.
}
void Player::display_name() {			//Writes out all the playerdata.
	cout << name;
}
void Player::write(ostream* out) {		//Write data to stream
	*out << number << ' ' << name << '\n'
		 << address << '\n';
}
bool Player::name_is(char* inname) {	//Returns true if name == inname.
	if(strcmp(name, inname) == 0) return true;	//  False otherwise.
	else return false;
}
int Player::get_number() {
	return number;
}
