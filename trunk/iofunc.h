#ifndef __IOFUNC_H
#define __IOFUNC_H

#include "global.h"

class Iofunc {
	private:
		bool validate(char* txt, val_type v = none);
	public:
		char* read_string(istream* in, char delim = '\n');
		char* read_valid(char* desc, val_type v);
		int	  read_number(char* desc, int min = -1, int max = -1);
};

#endif