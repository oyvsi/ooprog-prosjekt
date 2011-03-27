#ifndef __GLOBAL_H
#define __GLOBAL_H

enum val_type {NONE, NAME, ADDRESS};

const int NAMELEN = 50;		//Default length on names
const int STRLEN = 100;		//Default length on strings
const int MAXTEAMS = 30;	//Maximum teams in a division
const int MAXPLAYERS = 50;	//Maximum players in a team
const int MAXGOALS = 50;	//Maximum goals in a match
const int DATELEN = 9;		//Default length on date strings


#ifdef _WIN32                                        //  Bokstavkoder for ∆ÿ≈:
const unsigned short UNI_ae = 0xFF91;
const unsigned short UNI_AE = 0xFF92;
const unsigned short UNI_oe = 0xFF9B;
const unsigned short UNI_OE = 0xFF9D;
const unsigned short UNI_aa = 0xFF86;
const unsigned short UNI_AA = 0xFF8F;
#else
const unsigned short UNI_ae = 0xFFC3;
#endif

#endif
