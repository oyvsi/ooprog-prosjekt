#include <iostream>
#include <fstream>

#include "global.h"
#include "iofunc.h"
#include "players.h"

using namespace std;

IOfunc io;
Players players;

int main() {
    //cout << "hello world2!" << endl;
    //int tall = io.read_number("Tall fra 7 til 19: ", 7, 19);    
    //cout << "Takk for at du skrev " << tall << "!";
	

	players.new_player();
	players.new_player();
	players.display();

    system("pause");
    
    return 0; // comment
}
