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
    int tall = io.read_number("Tall fra 7 - 9");    
    cout << "Takk for at du skrev " << tall << "!";

	/*cout << "Oppretter ny spiller...\n";
	players.new_player();
	cout << "Oppretter ny spiller...\n";
	players.new_player();
	cout << "Vis: A(lle) | <nr> | <navn> : ";
	players.display();
	cout << "Slett: <nr> | <navn> : ";
	players.remove_player();
	cout << "Vis: A(lle) | <nr> | <navn> : ";
	players.display();
	players.write_file();*/

    system("pause");
    
    return 0; // comment
}
