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
const int UNI_ae = -111;
const int UNI_AE = -110;
const int UNI_oe = -101;
const int UNI_OE =  -99;
const int UNI_aa = -122;
const int UNI_AA = -113;
#else
const int UNI_ae = 0xFFC3;
const int UNI_AE = 0xFFC3;
const int UNI_oe = 0xFFC3;
const int UNI_OE = 0xFFC3;
const int UNI_aa = 0xFFC3;
const int UNI_AA = 0xFFC3;
#endif

#endif
