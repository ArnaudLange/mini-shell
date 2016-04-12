/*
    This file is part of Binsh.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "../../include/commands/mv.h"


int mv_lib(int argc, char *argv[]){

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
            mv(files[1],files[2], options, nbOptions);   
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

void mv(char* arg1, char* arg2, char* options, int iOptions){
    // ----------------------------------
    // Initialisation
    // ----------------------------------
    struct stat statbuf;

    // ----------------------------------
    // Lecture des options
    // ----------------------------------
    
   
    if (stat(arg1, &statbuf) == -1) { //si il n'existe aucun fichier déjà nommé comme celui qu'on essaye de déplacer
        printf("mv : '%s' invalid path\n", arg1);
    }
    else if(stat(arg2, &statbuf) != -1) { //si le fichier dest existe déjà

        if(S_ISDIR(statbuf.st_mode)){ //si c'est un dossier, déplacement de arg1 dans arg2

            if(strcmp(options, "v") == 0) {
                printf("Moving %s to %s/\n", arg1, arg2);
            }

            concatenateTables(arg2, "/");
            concatenateTables(arg2, arg1);
            rename(arg1, arg2);
        }
        else printf("mv : '%s' already exists\n", arg2);
    }
    else{
    	if(strcmp(options, "v") == 0) {
        	printf("Renaming %s to %s\n", arg1, arg2);
    	}
        rename(arg1, arg2);
    }
    
}
