#ifndef _PARAMETRE_LS_H
#define _PARAMETRE_LS_H

#include "utils.h"

typedef enum
{
	etatNormal,
	etatDetails,	//avec details
	etatDossiers //que les dossiers

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