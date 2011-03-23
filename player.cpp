#include <iostream>

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
	name = io.read_valid("Spillernavn", aname);		//Read name and address from
	address = io.read_valid("Adresse", anaddress);	//  the user.
}
Player::~Player() {			//release the memory this class used.
	delete [] name;
	delete [] address;
}
void Player::display() {	//Write out the number and name, to a list over
	cout << number << ": " << name << '\n';		//  several players.
}
void Player::display_all() {			//Writes out all the playerdata.
	cout << number << ": " << name		//  Used where data from only one
		 << '\n' << address << '\n';	//  player is displayed.
}
bool Player::name_is(char* inname) {	//Returns true if name == inname.
	if(strcmp(name, inname) == 0) return true;	//  False otherwise.
	else return false;
}