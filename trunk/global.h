#ifndef __GLOBAL_H
#define __GLOBAL_H

enum val_type {NONE, NAME, ADDRESS};

const int NAMELEN			=  50;	//Default length on names
const int STRLEN			= 100;	//Default length on strings
const int MAXTEAM			=  30;	//Maximum teams in a division
const int MAXPLAYERS	=  50;	//Maximum players in a team
const int MAXGOALS		=  50;	//Maximum goals in a match
const int DATELEN			=   9;	//Default length on date strings


#ifdef _WIN32									//  Bokstavkoder for ∆ÿ≈ (windows):
const int UNI_ae = -111;
const int UNI_AE = -110;
const int UNI_oe = -101;
const int UNI_OE =  -99;
const int UNI_aa = -122;
const int UNI_AA = -113;
#else													//	Kanskje dette fungerer for unix:
const int UNI_ae =  -61;
const int UNI_AE =  -61;
const int UNI_oe =  -61;
const int UNI_OE =  -61;
const int UNI_aa =  -61;
const int UNI_AA =  -61;
#endif

#endif
