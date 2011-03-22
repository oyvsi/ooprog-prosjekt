#ifndef __IOFUNC_H
#define __IOFUNC_H

#include <fstream>
#include "global.h"

class IOfunc {
	private:
		bool validate(char* txt, val_type v);
		bool is_number(char* c);
	public:
    char* read_string(std::istream* in, char delim);
		char* read_valid(char* txt, val_type v);
		int	  read_number(char* txt, int min, int max);
};

#endif
