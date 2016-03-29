#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char const *argv[])
{
	char * curdir = malloc(64*sizeof(char));
	getcwd(curdir , 64*sizeof(char));
	printf("%s\n", curdir);
	return 0;
}
