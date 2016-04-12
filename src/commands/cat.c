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
#include "../../include/commands/cat.h"
void cat(char* files, char**options, int iOptions, int *nbLigne)
{
	// ----------------------------------
	// Lecture des options
	// ----------------------------------
	Options etat;
	etat = etatNormal;
	int h;
	for (h = 0; h <= iOptions; h++)
	{
		readCatOptions(options[h], &etat);
	}
	// ----------------------------------
	// Initialisation
	// ----------------------------------
	FILE *fichier = NULL;
	char character;
	int premiere=0;

	if (strcmp(files, ""))
	{
		fichier = fopen(files,"r");
		if (fichier == NULL)
		{
			perror(files);
			exit(1);
		}
		while ((character=fgetc(fichier)) != EOF)
        {
            
            switch (etat)
            {
            	case etatNormal:

            		printf("%c", character);

            		break;

            	case etatEnds:

            		if (character == 10)
            		{
            			printf("$");
            			printf("%c", character);
            		}
            		else
            		{
            			printf("%c", character);
            		}

            		break;

            	case etatLines:

            		if (premiere == 0)
            		{
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;	
            			premiere = 1;
            		}

            		//character = fgetc (fichier);
            		if (character == 10)
            		{
            			printf("%c", character);
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;
            		}
            		else
            		{
            			printf("%c", character);
            		}
            		break;
            		

            	case etatTabs:

            		//character = fgetc (fichier);
					if (character == 9)
            		{
            			printf("^I");
            		}
            		else
            		{
            			printf("%c", character);
            		}

            		break;

            	case etatET:

            		//character = fgetc (fichier);
					if (character == 9)
            		{
            			printf("^I");
            		}
            		else if (character == 10)
            		{
            			printf("$");
            			printf("%c", character);
            		}
            		else
            		{
            			printf("%c", character);
            		}

            		break;

            	case etatEL:

            		if (premiere == 0)
            		{
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;	
            			premiere = 1;
            		}

            		//character = fgetc (fichier);
            		if (character == 10)
            		{
            			printf("$");
            			printf("\n");
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;
            		}
            		else if (character == 10)
            		{
            			printf("%c", character);
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;
            		}
            		else
            		{
            			printf("%c", character);
            		}

            		break;


            	case etatTL:

            		if (premiere == 0)
            		{
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;	
            			premiere = 1;
            		}

            		//character = fgetc (fichier);
            		if (character == 9)
            		{
            			printf("^I");
            		}
            		else if (character == 10)
            		{
            			printf("%c", character);
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;
            		}
            		else
            		{
            			printf("%c", character);
            		}

            		break;

            	case etatETL:

            		if (premiere == 0)
            		{
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;	
            			premiere = 1;
            		}

            		//character = fgetc (fichier);
            		if (character == 9)
            		{
            			printf("^I");
            		}
            		else if (character == 10)
            		{
            			printf("$");
            			printf("%c", character);
            			printf("\t%d  ",*nbLigne);
            			(*nbLigne)++;
            		}
            		else
            		{
            			printf("%c", character);
            		}

            		break;
            }

        }
        printf("\n"); 
	}
	else
	{
		printf("Pas de file en entree\n");
		exit(0);
	}

	// ----------------------------------
	// Si il n'y a pas de fichiers en entrée
	// ----------------------------------
}

int cat_lib(int argc, char *argv[])
{
	// -----------------------------------
	// Declaration tableau deux dimensions pour les options

	char **options = NULL;
	options = malloc(sizeof(char*));
	if (options == NULL)
	{
		perror("options");
		exit(1);
	}
	options[0] = malloc(sizeof(char*));
	if (options[0] == NULL)
	{
		perror("options[x]");
		exit(1);
	}
	options[0]="";


	// -----------------------------------
	// Declaration tableau deux dimensions pour les files

	char **files = NULL;
	files = malloc(sizeof(char*));
	if (files == NULL)
	{
		perror("files");
		exit(1);
	}
	files[0] = malloc(sizeof(char*));
	if (files[0] == NULL)
	{
		perror("files[x]");
		exit(1);
	}

	// -----------------------------------

	int iOptions = -1;
	int iFiles = -1;
	int nbLigne = 1;
	int i,j;

	// -----------------------------------
	// parcourt des arguments de la fonction

	if (argc >1)
	{
		for (i=1; i<argc; i++)
		{
			if(argv[i][0] == '-')
			{
				iOptions++;
				options[iOptions] = malloc(sizeof(char*));
				concatenateTables(options[iOptions],argv[i]);

			}
			else {
				iFiles++;
				files[iFiles] = malloc(sizeof(char*));

				concatenateTables(files[iFiles],argv[i]);
			}
		}
		// if there are different files
		if (iFiles >=0)
		{
			for(j = 0; j <= iFiles; j++)
			{
				cat(files[j],options,iOptions, &nbLigne);
				free(files[j]);
			}	
		}
		else
		{
			cat("",options,iOptions,&nbLigne);
		}
		free(files);
		int l;
		for (l=0;l<iOptions;l++)
		{
			free(options[l]);
		}
		free(options);


	}
	//SI pas d'arguments => on affiche une erreur
	else
	{
		printf("cat : no existing file entered\n");
	}

	return 0;
}

void readCatOptions(char *options, Options *etat)
{
        /**
         * Compares options and different types of options handled
         * And updates etat accordingly
         */
         int etatOptions = -1;

        if (strcmp(options, "--help")==0)
        {
                printf("Usage: cat [OPTION]... [FILE]...\n");
                printf("Concatenate FILE(s), or standart input, to standart output\n");
                printf("\n\t-E, --show-ends\t\tdisplay $ at the end of each line\n");
                printf("\n\t-T, --show-tabs\t\tdisplay TAB character as ^I\n");
                printf("\n\t-n, --number   \t\tnumber all input lines\n");
                exit(0);
        }

        switch (*etat)
        {
                case etatEnds:
                        if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
                        {
                                etatOptions = 0;
                                *etat = etatEL;
                        }
                        if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
                        {
                                etatOptions = 0;
                                *etat = etatET;
                        }
                        break;

                case etatLines:
                        if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
                        {
                                etatOptions = 0;
                                *etat = etatEL;
                        }
                        if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
                        {
                                etatOptions = 0;
                                *etat = etatTL;
                        }
                        break;

                case etatTabs:
                        if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
                        {
                                etatOptions = 0;
                                *etat = etatET;
                        }
                        if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
                        {
                                etatOptions = 0;
                                *etat = etatTL;
                        }
                        break;

                case etatTL:
                        if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
                        {
                                etatOptions = 0;
                                *etat = etatETL;
                        }
                        break;

                case etatEL:
                        if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
                        {
                                etatOptions = 0;
                                *etat = etatETL;
                        }
                        break;

                case etatET:
                        if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
                        {
                                etatOptions = 0;
                                *etat = etatETL;
                        }
                        break;

                case etatETL:
                        break;          

                case etatNormal:
                        if (strcmp(options, "-E")==0 || strcmp(options, "--show-ends")==0)
                        {
                                etatOptions = 0;
                                *etat = etatEnds;
                        }
                        if (strcmp(options, "-n")==0 || strcmp(options, "--number")==0)
                        {
                                etatOptions = 0;
                                *etat = etatLines;
                        }
                        if (strcmp(options, "-T")==0 || strcmp(options, "--show-tabs")==0)
                        {
                                etatOptions = 0;
                                *etat = etatTabs;
                        }
                        if (strcmp(options, "-TE")==0 || strcmp(options, "-ET")==0 )
                        {
                                etatOptions = 0;
                                *etat = etatET;
                        }
                        if (strcmp(options, "-En")==0 || strcmp(options, "-nE")==0 )
                        {
                                etatOptions = 0;
                                *etat = etatEL;
                        }
                        if (strcmp(options, "-Tn")==0 || strcmp(options, "-nT")==0 )
                        {
                                etatOptions = 0;
                                *etat = etatTL;
                        }
                        if (strcmp(options, "-ETn")==0 || strcmp(options, "-EnT")==0 || strcmp(options, "-nET")==0 || strcmp(options, "-nTE")==0 || strcmp(options, "-TEn")==0 || strcmp(options, "-TnE")==0)
                        {
                                etatOptions = 0;
                                *etat = etatETL;
                        }
                        break;
        }
        
        
        //if (strcmp(options, "-E")!=0 && strcmp(options, "--show-ends")!=0 && strcmp(options, "-n")!=0 && strcmp(options, "--number")!=0 && strcmp(options, "-T")!=0 && strcmp(options, "--show-tabs")!=0 )
        if (etatOptions == -1)
        {
                /**
                 * Error if the options isn't handled
                 * Precise which options were at fault
                 * And quits the program
                 */
                printf("cat: invalid option %s\n",options);
                printf("Try 'cat --help' for more information.\n");
                exit(1);
        }

}
