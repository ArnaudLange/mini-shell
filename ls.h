#ifndef _LS_H
#define _LS_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>

#include <time.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>

#include <fcntl.h>

#define NORMAL "\x1B[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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

/**
 * @brief 	Opens a file with the read only mode
 * 
 * @return 	The file in Integer
 */

int openFile(char *filename)
{
    return open(filename, O_RDONLY);
}

/**
 * @brief 	Sets the options depending on the entries
 * Also concatenates if there are more than two options and that the concatenation is possible
 * 
 */

void readOptions(char *options, Options *etat)
{
	/**
	 * Compares options and different types of options handled
	 * And updates etat accordingly
	 */
	if (strcmp(options, "-l")==0)
	{
		*etat=etatDetails;
	}
	else if (strcmp(options, "-d")==0)
	{
		*etat=etatDossiers;
	}
	else if (strcmp(options, "")==0)
	{
		*etat=etatNormal;
	}
	else if ((strcmp(options, "-dl")==0) || (strcmp(options, "-ld")==0) || (strcmp(options, "-d-l")==0) || (strcmp(options, "-l-d")==0))
	{
		*etat=etatDetailsDossiers;
	}
	else
	{
		/**
		 * Error if the options isn't handled
		 * Precise which options were at fault
		 * And quits the program
		 */
		printf("ls: invalid option -- \"%s\"\n",options);
		printf("Get more information on the README.md document.");
		exit(-1);
	}

}

/**
 * @brief 	Concatenates two tables
 *
 *
 */

void concatenateTables(char *tab1, char *tab2)
{
	/**
	 * Gets the size of each table
	 *
	 */
	int taille1=0, taille2=0;

	while(tab1[taille1] != '\0')
	{
		taille1++;
	}

	while(tab2[taille2] != '\0')
	{
		taille2++;
	}

	/**
	 * Resets the memory of the table 
	 * Sets it to the addition of both tables' size
	 */
	tab1 = realloc(tab1, (taille1 + taille2)*sizeof(char));

	int i = taille1;
	int j = 0;


	while(tab2[j] != '\0')
	{
		tab1[i] = tab2[j];
		i++;
		j++;
	}
}

#endif