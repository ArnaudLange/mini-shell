
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "colors.h"


int openFile(char *filename)
{
	return open(filename, O_RDONLY);
}

void ls(char *input)
{
	DIR *repertoire;

	struct dirent *flux;
	struct stat statbuf;
	int file;

	if( (repertoire = opendir(input)) ==NULL)
	{
		printf("Error\n");
	}

	while((flux=readdir(repertoire)))
	{
		file = openFile(flux->d_name);
		fstat(file,&statbuf);

		if (S_ISDIR(statbuf.st_mode))	//CHECK si c'est un dossier
		{
			printf("%s%s\n",KBLU,flux->d_name);		//si oui on l'ecrit en bleu pour que ce soit visuel
			printf("%s",KNRM);	//puis on remet la couleur normale
		}
		else
			printf("%s\n",flux->d_name);	//sinon on ecrit normalement
	}
	closedir(repertoire);	//on ferme le dossier
}

int main(int argc, char *argv[])
{
	int i;
	if (argc >1)
		for (i=1;i<argc;i++)
		{
			ls(argv[i]);
		}	
	else	//si il n'y a pas d'arguments on lance ls dans le fichier courant
	{
		ls("./");
	}
	return 0;
}