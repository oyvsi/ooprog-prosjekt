#include <iostream>
#include <fstream>

#include "global.h"
#include "iofunc.h"

using namespace std;

IOfunc* io;

int main() {
    cout << "hello world2!" << endl;
    
    int tall = io->read_number("Tall fra 7 til 19: ", 7, 19);    
    cout << "Takk for at du skrev " << tall << "!";
    system("pause");
    
    return 0; // comment
}
