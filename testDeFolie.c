#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "colors.h"
#include <string.h>

int parcourirChaine(char *chaine)
{
	int i=0;

	while (chaine[i] != '\0')
	{
		printf("%c", chaine[i]);
		i++;		
	}

	return i;
}

int main(int argc, char const *argv[])
{
	printf("123456789123456789\n");
	printf("\t123456789\n");
	
	return 0;
}
