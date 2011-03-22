#include <iostream>
#include <fstream>

#include "global.h"
#include "iofunc.h"
#include "players.h"

using namespace std;

IOfunc io;
Players players;

int main() {
	char* test;
    //cout << "hello world2!" << endl;
    //int tall = io.read_number("Tall fra 7 til 19: ", 7, 19);    
    //cout << "Takk for at du skrev " << tall << "!";
	
	test = io.read_valid("Tekst", aname);
	cout << test;
	test = io.read_valid("Tekst", aname);
	cout << test;

    system("pause");
    
    return 0; // comment
}
