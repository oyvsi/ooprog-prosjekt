// Et jævla morsomt program! =D

// Bruk:   program.exe <antall spillere>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool generer(int antall);
vector<string> les_navn_fil(ifstream* inn);
vector<char*> les_adr_fil(ifstream* inn);

int main(int argc, char* argv[])
{
	if (argc == 2){
		cout << "Genererer fil med " << atoi(argv[1]) << " navn...\n";
		if (!generer(atoi(argv[1])))
			cout << "Kunne ikke generere filen!\n";
	} else {
		cout << "Programmet må startes med ett numerisk argument!" << endl;
	}
	return 0;
}

bool generer(int antall)
{	
	ifstream inn_fnvn_m("fornavn_menn.txt");
	ifstream inn_fnvn_k("fornavn_kvinner.txt");	
	ifstream inn_envn("etternavn.txt");
	ifstream inn_adresser("adresser.txt");
	
	if (!(inn_fnvn_k.is_open() && inn_fnvn_m.is_open() && inn_envn.is_open() && inn_adresser.is_open())){
		cout << "Feil ved lesing av fil!" << endl;
		return false;
	}
	
	vector<string> herrenavn  = les_navn_fil(&inn_fnvn_m);
	vector<string> kvinnenavn = les_navn_fil(&inn_fnvn_k);
	vector<string> etternavn  = les_navn_fil(&inn_envn);
	vector<char*>  adresser   = les_adr_fil(&inn_adresser);
	
	ofstream utfil("players.txt");
	
	string rnd_fnvn, rnd_mnvn, rnd_knvn, rnd_envn;
	char* rnd_adr;
	
	srand(0); 
  int random;	
	
	utfil << antall << endl;
	
	for (int i = 1; i <= antall; i++){
		random =(rand()%herrenavn.size());
		rnd_mnvn = herrenavn[random];
		random =(rand()%herrenavn.size());
		rnd_knvn = kvinnenavn[random];
		random =(rand()%etternavn.size());
		rnd_envn = etternavn[random];
		random =(rand()%adresser.size());
		rnd_adr = adresser[random];
		
		rnd_fnvn = (rand()%2) ? rnd_knvn : rnd_mnvn; 
		
		utfil << /*i << " " <<*/ rnd_fnvn << " " << rnd_envn << endl
					<< rnd_adr << endl;
	}
	
	for (int i = 0; i < adresser.size(); i++)
		delete [] adresser[i];
		
	return true;
}


vector<string> les_navn_fil(ifstream* inn)
{
	vector<string> navn;
	string tmp;	

	*inn >> tmp;
	
	while (!inn->eof()){
		navn.push_back(tmp);
		*inn >> tmp;
	}	
	cout << "Las " << navn.size() << " unike navn fra fil." << endl;	
	return navn;
}

vector<char*> les_adr_fil(ifstream* inn)
{
	vector<char*> adr;
	
		
	char* ptr, temp[50];

	inn->getline(temp, 50);	
	
	while (!inn->eof()){
		ptr = new char[strlen(temp)+1]; 	//Allokér minne for tekst + \0
		strcpy(ptr, temp);								//Kopier tekst
		adr.push_back(ptr);
		inn->getline(temp, 50);
	}
	cout << "Las " << adr.size() << " unike adresser fra fil." << endl;
	return adr;
}
