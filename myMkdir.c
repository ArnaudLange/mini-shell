#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils.h"


void myMkdir(char *arg)
{
	struct stat st = {0};

	if (stat(arg, &st) == -1) {
    	mkdir(arg, 0700);
	}
	else{
		printf("Le dossier %s existe deja, victime.\n", arg);
	}
	
}


int main(int argc, char* argv[])
{
	int i;
	if (argc > 1)
	{
		for(i=1; i<argc; i++)
		{
			myMkdir(argv[i]);
		}
	}
	else
	{
		printf("\t-----\t\n");
		printf("Erreur, pas de nom de dossier en input.\n");
		printf("\t-----\t\n");
	}
	
	return 0;
}