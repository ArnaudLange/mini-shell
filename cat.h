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

void readOptions(char *options, Options *etat)
{
	/**
	 * Compares options and different types of options handled
	 * And updates etat accordingly
	 */

	if (strcmp(options, "--help")==0)
	{
		printf("Usage: cat [OPTION]... [FILE]...\n");
		printf("Concatenate FILE(s), or standart input, to standart output\n");
		printf("\n\t-E, --show-ends\t\tdisplay $ at the end of each line\n");
		printf("\n\t-T, --show-tabs\t\tdisplay TAB character as ^I\n");
		printf("\n\t-n, --number   \t\tnumber all input lines\n");
		exit(-1);
	}

	switch (*etat)
	{
		case etatEnds:
			if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
			{
				*etat = etatEL;
			}
			if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
			{
				*etat = etatET;
			}
			break;

		case etatLines:
			if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
			{
				*etat = etatEL;
			}
			if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
			{
				*etat = etatTL;
			}
			break;

		case etatTabs:
			if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
			{
				*etat = etatET;
			}
			if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
			{
				*etat = etatTL;
			}
			break;

		case etatTL:
			if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
			{
				*etat = etatETL;
			}
			break;

		case etatEL:
			if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
			{
				*etat = etatETL;
			}
			break;

		case etatET:
			if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
			{
				*etat = etatETL;
			}
			break;

		case etatETL:
			break;		

		case etatNormal:
			if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
			{
				*etat = etatEnds;
			}
			if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
			{
				*etat = etatLines;
			}
			if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
			{
				*etat = etatTabs;
			}
			break;
	}
	
	
	if (strcmp(options, "-E")!=0 && strcmp(options, "--show-ends")!=0 && strcmp(options, "-n")!=0 && strcmp(options, "--number")!=0 && strcmp(options, "-T")!=0 && strcmp(options, "--show-tabs")!=0 )
	{
		/**
		 * Error if the options isn't handled
		 * Precise which options were at fault
		 * And quits the program
		 */
		printf("cat: invalid option %s\n",options);
		printf("Try 'cat --help' for more information.\n");
		exit(-1);
	}

}

void concatenateTables(char *tab1, const char *tab2)
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