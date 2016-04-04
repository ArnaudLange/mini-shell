#ifndef _CAT_H
#define _CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

void readOptions(char *options, Options *etat);
void concatenateTables(char *tab1, const char *tab2);



#endif