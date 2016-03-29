#include "parametre.h"
#include "utils.h"





void lectureParam(char * param, Parametres *etat)
{
	if (strcmp(param, "l")==0)
	{
		*etat=Sl;
	}
	else if (strcmp(param, "d")==0)
	{
		*etat=Sd;
	}
	else if (strcmp(param, "c")==0)
	{
		*etat=Sc;
	}
	else 
		*etat=SRien;
		printf("Pas de parametre valide.\n");
}

void tabulation(int nb)
{
	int i;
	for (i=0;i<nb;i++)
	{
		printf("\t");
	}
}

void testParam()
{
	char *parametre = "c";
	Parametres etat = SRien;

	lectureParam(parametre,&etat);
	if (etat == Sl)
	{
		printf("Etat -l\n");
	}
	else if (etat == Sd)
	{
		printf("Etat -d\n");
	}
	else if (etat == Sc)
	{
		printf("Etat -c\n");
	}
	printf("Done.\n");
}

void ls(char *input, char *param)
{
	Parametres etat = SRien;	//definition de l'etat
	lectureParam(param,&etat);

	DIR *repertoire;

	struct dirent *flux;
	struct stat statbuf;
	int file;
	int ligne = -1;

	if( (repertoire = opendir(input)) ==NULL)
	{
		printf("Error\n");
	}

	while((flux=readdir(repertoire)))
	{	
		file = openFile(flux->d_name);
		fstat(file,&statbuf);
		switch (etat)
		{
		case SRien:

			if (S_ISDIR(statbuf.st_mode))	//CHECK si c'est un dossier
			{
				printf("%s%s",KBLU,flux->d_name);		//si oui on l'ecrit en bleu pour que ce soit visuel
				printf("%s | ",KNRM);	//puis on remet la couleur normale
			}
			else
			{	
				printf("%s | ",flux->d_name);	//sinon on ecrit normalement
			}
			break;
		
		case Sl:
			printf("Case -l\n.");
			break;

		case Sc:
			ligne++;
			if (ligne >= 4)
			{
				printf("\n");
				ligne=0;
			}
			if (S_ISDIR(statbuf.st_mode))	//CHECK si c'est un dossier
			{
				int taille=0;
				taille = parcourirChaine(flux->d_name);

				printf("%s%s",KBLU,flux->d_name);		//si oui on l'ecrit en bleu pour que ce soit visuel

				printf("%s",KNRM);	//puis on remet la couleur normale
				if(taille > 8)
				{
					tabulation(2);
				}
				else
					tabulation(3);
			}
			else
			{	
				int taille=0;
				taille = parcourirChaine(flux->d_name);

				printf("%s",flux->d_name);	//sinon on ecrit normalement
				if(taille >= 8)
				{
					tabulation(2);
				}
				else
					tabulation(3);
			}
			break;
		
		case Sd:
			printf("Case -c\n.");
			break;
		}
	}
	printf("\n"); //saut de ligne
	closedir(repertoire);	//on ferme le dossier
}

int main(int argc, char *argv[])
{
	char *param = "c";
	int i;
	if (argc >1)
		for (i=1;i<argc;i++)
		{
			ls(argv[i],param);
		}	
	else	//si il n'y a pas d'arguments on lance ls dans le fichier courant
	{
		ls("./",param);
	}
	return 0;
}