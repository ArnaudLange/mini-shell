#include "utils.h"

int openFile(char *filename)
{
    return open(filename, O_RDONLY);
}

int parcourirChaine(char *chaine)
{
    int i=0;

    while (chaine[i] != '\0')
    {
        i++;        
    }

    return i;
}

void affichageTableau(char * tab)
{
	int j=0;
	while (tab[j] != '\0')
	{
		printf("%c", tab[j]);
		j++;
	}
	printf("\n");
}

void concatenationTableaux(char *tab1, char *tab2)
{
	//RECUPERER TAILLE DES DEUX TABLEAUX
	int taille1=0, taille2=0;

	while(tab1[taille1] != '\0')
	{
		taille1++;
	}

	while(tab2[taille2] != '\0')
	{
		taille2++;
	}

	//REALLOC TABLEAU
	//on met la taille a la somme des deux tailles
	tab1 = realloc(tab1, (taille1 + taille2)*sizeof(char));

	int i = taille1;
	int j = 0;
	//on ajoute les caracteres a ajouter
	while(tab2[j] != '\0')
	{
		tab1[i] = tab2[j];
		i++;
		j++;
	}
}