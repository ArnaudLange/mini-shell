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
#include "../../include/commands/cat.h"

void cat(char* files, char*options, int *nbLigne)
{
	// ----------------------------------
	// Lecture des options
	// ----------------------------------
	Options etat;
	etat = etatNormal;
	readCatOptions(options, &etat);
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
		printf("Pas de file en entree.\n");
		//
	}

	// ----------------------------------
	// Si il n'y a pas de fichiers en entrée
	// ----------------------------------
}

int cat_lib(int argc, char *argv[])
{   
    // -----------------------------------
    // Declaration tableau une dimension pour les options

    char* options = NULL;
    options = (char*) calloc(3,sizeof(char));
    if (options == NULL)
    {
        perror("options");
        
    }


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

    char** files = NULL;
    files = calloc(1,sizeof(char**));
    if (files == NULL)
    {
        perror("files");
        
    }
    files[0] = calloc(1,sizeof(char*));
    if (files[0] == NULL)
    {
        perror("files[x]");
        
    }
    // -----------------------------------

    int nbFiles = 0;
    int nbLigne = 1;
    int i, c, j;

    // -----------------------------------
    // parcourt des arguments de la fonction
    if (argc >1) {
        while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'},
            {"number",     no_argument,       0, 'n'},
            {"show-tabs",  no_argument,       0, 'T'},
            {"show-ends",  no_argument,       0, 'E'}
        };

       c = getopt_long(argc, argv, "hnTE", long_options, &option_index);

        if (c == -1) break;

       switch (c) {

         case 'h':

            printf("Usage: cat [OPTION]... [FILE]...\n");
            printf("Concatenate FILE(s), or standart input, to standart output\n");
            printf("\n\t-E, --show-ends\t\tdisplay $ at the end of each line\n");
            printf("\n\t-T, --show-tabs\t\tdisplay TAB character as ^I\n");
            printf("\n\t-n, --number   \t\tnumber all input lines\n");
            
            break;

         case 'n':
           options[0]=1; 
           break;

         case 'T':
           options[1]=1; 
           break;

         case 'E':
           options[2]=1; 
           break;

       default:
            printf("cat: invalid option %s\n",options);
            printf("Try 'cat --help' for more information.\n");
            
      }
    }

        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files=realloc(files, (nbFiles+1)*sizeof(char*));
                if(files == NULL){
                    perror("files");
                    
                }
                files[nbFiles] = calloc(1,sizeof(char));
                if (files[nbFiles] == NULL)
                {
                    perror("files[x]");
                    
                }
                files[nbFiles-1]=concatenateTables(files[nbFiles-1], argv[i]);
            }
        }
        // if there are 2 files
        if (nbFiles >0)
        {
            for(j = 0; j < nbFiles; j++)
            {
                cat(files[j],options, &nbLigne);
                free(files[j]);
            }   
        }
        else
        {
            cat("",options,&nbLigne);
        }
        free(files);
        free(options);


    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("cat : invalid number of parameters\n");
        printf("Try 'cat --help' for more information.\n");
        
    }

    return 0;
}

void readCatOptions(char *options, Options *etat)
{
        /**
         * Compares options and different types of options handled
         * And updates etat accordingly
         */
        if (options[0] == 1)
        {
            if (options[1]==1)
            {
                if (options[2]==1){
                    *etat=etatETL;
                }
                else{
                    *etat=etatTL;
                }
            }
            else
            {
                if (options[2]==1){
                    *etat=etatEL;
                }
                else{
                    *etat=etatLines;
                }
            }
        }
        else
        {
            if (options[1]==1)
            {
                if (options[2]==1){
                    *etat=etatET;
                }
                else{
                    *etat=etatTabs;
                }
            }
            else
            {
                if (options[2]==1){
                    *etat=etatEnds;
                }
                else{
                    *etat=etatNormal;
                }
            }
        }   

}
