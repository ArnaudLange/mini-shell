#include "cat.h"

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
		exit(1);
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
		exit(1);
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

void cat(char* files, char**options, int iOptions)
{
	// ----------------------------------
	// Lecture des options
	// ----------------------------------
	Options etat;
	etat = etatNormal;
	int h;
	for (h = 0; h <= iOptions; h++)
	{
		readOptions(options[h], &etat);
	}
	// ----------------------------------
	// Initialisation
	// ----------------------------------
	FILE *fichier = NULL;
	char caractere;

	if (strcmp(files, "")!=0)
	{
		fichier = fopen(files,"r");
		if (fichier == NULL)
		{
			perror("fopen");
			exit(1);
		}
		do
        {
            
            switch (etat)
            {
            	case etatNormal:
            		caractere = fgetc (fichier);
            		printf("%c", caractere);
            		break;

            	case etatEnds:

            		break;

            	case etatLines:

            		break;

            	case etatTabs:

            		break;

            	case etatET:

            		break;

            	case etatEL:

            		break;

            	case etatTL:

            		break;

            	case etatETL:

            		break;
            }

        } while (caractere != EOF);
	}
	else
	{
		printf("Pas de file en entree");
		exit(0);
	}
	// ----------------------------------
	// Si il n'y a pas de fichiers en entrée
	// ----------------------------------
}

int main(int argc, char const *argv[])
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
				printf("\nFILE : %s\n\n",files[j]);
				cat(files[j],options,iOptions);
				free(files[j]);
			}	
		}
		else
		{
			cat("",options,iOptions);
		}
		free(files);
		free(options);


	}
	//SI pas d'arguments => on affiche une erreur
	else
	{
		printf("cat : no existing file entered\n");
	}

	return 0;
}