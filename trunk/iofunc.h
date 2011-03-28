#ifndef __IOFUNC_H
#define __IOFUNC_H

#include <fstream>
#include "global.h"

class IOfunc {
	private:
		bool validate(char* txt, val_type v);
		bool isalex(char c);									//  Sjekker om c er æøåÆØÅ
	public:
		bool	is_number(char* c);							//  Sjekker om *c er et tall
		char	to_upper(char up);							//  Returnerer uppercase
		char*	read_string(std::istream* in, char delim = '\n');
		char*	read_valid(char* txt, val_type v);
		char*	store_string(char* txt);
		int		read_number(char* txt, int min, int max);
};

#endif
