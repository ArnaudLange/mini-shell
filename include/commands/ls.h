/*
    This file is part of Binsh.

    Binsh is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Binsh is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LS_H
#define LS_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <dirent.h>

#include <time.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>

#include <fcntl.h>


#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "../redirection.h"
#include "../utils.h"
#include "../parameters.def"
#include "../typedef.h"

#define NORMAL "\x1B[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


int ls_lib(int argc, char* argv[]);

/**
 * @brief	Options enumeration
 * Manages the differents kinds of options of our ls command
 *
 */

typedef enum
{
	etatNormal,
	etatDetails,	
	etatDossiers, 
	etatDetailsDossiers	

} Options;

void ls(char *directory, char *options);

/**
 * @brief 	Sets the options depending on the entries
 * Also concatenates if there are more than two options and that the concatenation is possible
 * 
 */

void readLsOptions(char *options, Options *etat);

#endif