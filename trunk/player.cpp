#include <iostream>
#include <fstream>

#include "player.h"
#include "global.h"
#include "listtool2.h"
#include "iofunc.h"

using namespace std;

Player::Player() : Num_element(0) {
	cout << "PLAYER.CPP - WARNING!! - This constructor should not be called";
}
Player::Player(int n) : Num_element(n) {
	name = read_valid("Spillernavn", name);
	address = read_valid("Adresse", address);
}
Player::~Player() {
	delete [] name;
	delete [] address;
}