#include <iostream>

#include "player.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

extern IOfunc io;

Player::Player() : Num_element(0) {
	cout << "PLAYER.CPP - WARNING!! - This constructor should not be called";
}
Player::Player(int n) : Num_element(n) {
	name = io.read_valid("Spillernavn", aname);
	address = io.read_valid("Adresse", anaddress);
}
Player::~Player() {
	delete [] name;
	delete [] address;
}
void Player::display() {
	cout << number << " - " << name << '\n' << address << '\n';
}
bool Player::name_is(char* inname) {
	if(strcmp(name, inname) == 0) return true;
	else false;
}