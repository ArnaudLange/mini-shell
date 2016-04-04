#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "../utils.h"

typedef enum
{
	etatNormal,
	etatEnds,	
	etatTabs, 
	etatLines,
	etatET,
	etatEL,
	etatTL,
	etatETL	

} Options;

void readCatOptions(char *options, Options *etat);


void cat(char* files, char**options, int iOptions, int *nbLigne);
int cat_lib(int argc, char *argv[]);



#endif