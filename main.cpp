#include <iostream>
#include <fstream>

#include "global.h"
#include "iofunc.h"
#include "players.h"
#include "sports.h"

using namespace std;

IOfunc io;
Players players;
Sports sports;

int main() {
	cout << "Oppretter idrett\n";
	sports.new_sport();
	cout << "Legger til divisjon\n";
	sports.add_division();
	cout << "Prøver å displaye terminlist\n";
	sports.term_list();
/*
//  TEST AV IOFUNC:
  char* nvn = io.read_valid("Navn: ", NAME);
  
  if (nvn)
    cout << "Bra navn!" << endl;
  else
    cout << "Ugyldig navn!" << endl;
    
  nvn = io.read_valid("Adresse: ", ADDRESS);
  
  if (nvn)
    cout << "Bra adresse!" << endl;
  else
    cout << "Ugyldig adresse!" << endl;

      
  cout << "Oppretter ny spiller...\n";
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
