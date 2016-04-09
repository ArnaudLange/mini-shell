#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "utils.h"

//commentaire test
int main(int argc, char const *argv[])
{
	char * curdir = malloc(64*sizeof(char));
	getcwd(curdir , 64*sizeof(char));
	printf("%s\n", curdir);
	


	// -----------------------------------
    // Declaration tableau deux dimensions pour les options

    char* options = NULL;
    options = (char*) calloc(15, sizeof(*options));
    if (options == NULL)
    {
        perror("options");
        exit(1);
    }


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

    char** files = NULL;
    files = malloc(sizeof(char**));
    if (files == NULL)
    {
        perror("files");
        exit(1);
    }
    files[0] = malloc(sizeof(char*));
    if (files[0] == NULL)
    {
        perror("files[x]");
        exit(1);
    }

    // -----------------------------------

    int nbOptions = 0;
    int nbFiles = 0;
    int i, c;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {
        while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'},
            {"verbose",  no_argument,       0, 'v'}
        };

       c = getopt_long(argc, argv, "hv", long_options, &option_index);

        if (c == -1) break;

       switch (c) {

         case 'h':
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: mv [OPTION]... SOURCE DEST\n");
           printf("Rename SOURCE to DEST\n\n");
           printf("    -v, --verbose        explain what is being done\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

         case 'v':
           options[nbOptions] = c; 
           nbOptions++;
           break;

       default:
            printf("Try 'mv --help' for more information.\n");
            exit(1);
      }
    }

        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files[nbFiles] = malloc(16*sizeof(char*));

                concatenateTables(files[nbFiles],argv[i]);


            }
        }
        // if there are 2 files
        if (nbFiles == 2)
        {
            myMv(files[1],files[2], options, nbOptions);   
        }
        else
        {
            printf("mv : invalid number of arguments\n");
            printf("Try 'mv --help' for more information.\n");
        }
        free(files);
        free(options);


    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("mv : invalid number of arguments\n");
    }

    return 0;
}
