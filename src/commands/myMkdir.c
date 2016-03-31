#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


void myMkdir(char *arg)
{
	mkdir(arg,0777);
}


int main(int argc, char* argv[])
{
	int i;
	if (argc > 1)
	{
		for(i=0; i<argc; i++)
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