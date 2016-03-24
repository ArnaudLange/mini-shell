#ifndef _PARAMETRE_LS_H
#define _PARAMETRE_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "colors.h"

typedef enum
{
	SRien,
	Sl,	//avec details
	Sd, //que les dossiers
	Sc //en colomne

} Parametres;

typedef struct MaillonChar
{
	struct MaillonChar *suiv;
	char *elem;
} Maillon;

typedef struct PileChar
{
	int nb;
	Maillon *sommet;
} Pile;

#endif