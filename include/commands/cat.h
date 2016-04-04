/*
    This file is part of Binsh.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/

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