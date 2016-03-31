#ifndef _PARAMETRE_LS_H
#define _PARAMETRE_LS_H

#include "utils.h"

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