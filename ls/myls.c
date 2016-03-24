#include "parametre.h"


int openFile(char *filename)
{
	return open(filename, O_RDONLY);
}

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
	int file, ligne;

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
		case Sd:
			ligne++;
			if (ligne >= 4)
			{
				printf("\n");
				ligne=0;
			}
			if (S_ISDIR(statbuf.st_mode))	//CHECK si c'est un dossier
			{
				printf("%s%s",KBLU,flux->d_name);		//si oui on l'ecrit en bleu pour que ce soit visuel
				printf("%s\t\t",KNRM);	//puis on remet la couleur normale
			}
			else
			{	
				printf("%s\t\t",flux->d_name);	//sinon on ecrit normalement
			}
			break;
		
		case Sc:
			printf("Case -c\n.");
			break;
		}
	}
	printf("\n"); //saut de ligne
	closedir(repertoire);	//on ferme le dossier
}

int main(int argc, char *argv[])
{
	char *param = "d";
	int i;
	if (argc >1)
		for (i=1;i<argc;i++)
		{
			ls(argv[i],param);
		}	
	else	//si il n'y a pas d'arguments on lance ls dans le fichier courant
	{
		ls("./","");
	}
	return 0;
}