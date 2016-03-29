#include <stdio.h>
#include <stdlib.h>

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