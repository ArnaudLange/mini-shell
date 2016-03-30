#include "utils.h"


void lectureParametres(char * param, char * options, char *arg)
{
	char * temp = malloc(2*sizeof(char));
	if (temp == NULL)
	{
		perror("Erreur malloc lectureParametres()\n");
		exit(1);
	}
	int i=0;
	int k=0;
	int etat=0;

	if (arg[0] == '-')	//si c'est une options
	{
		etat = 0;
	}
	else 
	{			// si c'est un parametre
		etat = 1;
	}

	while (arg[i] != '\0')	// on parcourt l'input
	{
		//printf("%c", arg[i]);
		if (etat == 0 && i>0)
		{
			temp[k]=arg[i];
			printf("TEMP[i] = %c\n",temp[k]);
			// on remplit un tableau temporaire avec la chaine a ajouter
			temp = realloc(temp, (i+1)*sizeof(char));
			if (temp == NULL) {
				perror("Erreur realloc lectureParametres()\n");
				exit(1);
			}
			k++;
		}
		else if (etat == 1)
		{
			temp[i]=arg[i];
			printf("TEMP[i] = %c\n",temp[i]);
			// on remplit un tableau temporaire avec la chaine a ajouter
			temp = realloc(temp, (i+1)*sizeof(char));
			if (temp == NULL) {
				perror("Erreur realloc lectureParametres()\n");
				exit(1);
			}
			k++;
		}
		i++;
	}


	affichageTableau(temp);

	if (etat == 0)
	{
		concatenationTableaux(options,temp);
	}
	else
	{
		concatenationTableaux(param,temp);
	}

	free(temp);
}

int main(int argc, char *argv[])
{
	int i;
	char * param = (char *)malloc(sizeof(char));
	char * options = (char *)malloc(sizeof(char));

	if (argc >1)
	{
		for (i=1;i<argc;i++)
		{
			lectureParametres(param, options, argv[i]);
		}	
		printf("PARAMETRE(S) : %s\n",param);
		printf("OPTION(S) : %s\n",options);
	}
	else 
	{
		printf("Pas d'arguments.\n");
	}
	return 0;
}