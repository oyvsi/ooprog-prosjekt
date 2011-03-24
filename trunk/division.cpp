#include <fstream>
#include "listtool2.h"
#include "division.h"

Division::Division() {  

}

Division::Division(char *name, std::ifstream* infile) : Text_element(name) {
    // Read no_teams and teams from file
    // Create teams and players
    
    // create array the size of all teams (this index will indicate home)
    // each value in array should point to array where index will indicate away
    // from this array we point to the actual result object.

}
