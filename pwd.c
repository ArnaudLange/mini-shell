#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
//#include "utils.h"

int main(int argc, char *argv[]){
	
	// -----------------------------------
    // Declaration tableau  pour les options

    char* options = NULL;
    options = (char*) calloc(15, sizeof(*options));
    if (options == NULL)
    {
        perror("options");
        exit(1);
    }

    // -----------------------------------

    int nbFiles = 0;
    int i, c;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {
        while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'}
        };

       c = getopt_long(argc, argv, "h", long_options, &option_index);

        if (c == -1) break;

       switch (c) {

         case 'h':
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: pwd \n");
           printf("Give the current working directory\n\n");
           printf("    no options available\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

       default:
            printf("Try 'pwd --help' for more information.\n");
            exit(1);
      }
    }

        for (i=1; i<argc; i++){

            if(argv[i][0] != '-'){
                nbFiles++;
            }
        }
        // if there are 2 files
        if (nbFiles > 0){
            printf("pwd : invalid number of arguments\n");
            printf("Try 'pwd --help' for more information.\n");
        }

        free(options);


    }
    //SI pas d'arguments => on affiche le dossier courrant
    else{
        char * curdir = malloc(64*sizeof(char));
        getcwd(curdir , 64*sizeof(char));
        printf("%s\n", curdir);    
    }

    return 0;
}
