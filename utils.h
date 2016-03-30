#include <stdlib.h>

#ifndef _COLOR_H
#define _COLOR_H

#include <stdio.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KBLU "\x1B[32m"

#endif

int openFile(char *filename);
int parcourirChaine(char *chaine);
void affichageTableau(char *tab);
void concatenationTableaux(char *tab1, char *tab2);