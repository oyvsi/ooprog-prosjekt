#ifndef __IOFUNC_H
#define __IOFUNC_H

#include <fstream>
#include "global.h"

class IOfunc {
	private:
		bool validate(char* txt, val_type v);
		bool isalex(char c);                    //  Sjekker om c er ������
		bool is_number(char* c);                //  Sjekker om *c er et tall
	public:
		char* read_string(std::istream* in, char delim = '\n');
		char* read_valid(char* txt, val_type v);
		int	  read_number(char* txt, int min, int max);
};

#endif
