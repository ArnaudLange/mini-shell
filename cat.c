#include "cat.h"


// -E, --show-ends : display $ at end of each line

// -n, --number : number all output lines

// -T, --show-tabs : display TAB character as ^I

void cat(char* files, char**options, int iOptions)
{
	Options etat;
	etat = etatNormal;
	int h;
	for (h = 0; h <= iOptions; h++)
	{
		printf("h : %d\n",h);
		printf("Options : %s\n",options[h]);
		readOptions(options[h], &etat);
	}
	if (etat == etatETL)
	{
		printf("ETAT MAXIMUM\n");
	}
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
		exit(-1);
	}
	options[0] = malloc(sizeof(char*));
	if (options[0] == NULL)
	{
		perror("options[x]");
		exit(-1);
	}
	options[0]="";


	// -----------------------------------
	// Declaration tableau deux dimensions pour les files

	char **files = NULL;
	files = malloc(sizeof(char*));
	if (files == NULL)
	{
		perror("files");
		exit(-1);
	}
	files[0] = malloc(sizeof(char*));
	if (files[0] == NULL)
	{
		perror("files[x]");
		exit(-1);
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
		
		for(j = 0; j <= iFiles; j++)
		{
			printf("\nFILE : %s\n\n",files[j]);
			cat(files[j],options,iOptions);
			free(files[j]);
		}	
		
		free(files);


	}
	//SI pas d'arguments => on affiche une erreur
	else
	{
		printf("cat : no existing file entered\n");
	}

	return 0;
}