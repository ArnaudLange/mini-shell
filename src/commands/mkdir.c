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

#include "../../include/commands/mkdir.h"



    int mkdir_lib(int argc, char *argv[]){

    // -----------------------------------
    // Declaration tableau pour les options


        char* options = NULL;
        options = calloc(1, sizeof(char));
        if (options == NULL)
        {
            perror("options");
            exit(1);
        }


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

        char** files = NULL;
        files = calloc(1,sizeof(char*));
        if (files == NULL)
        {
            perror("files");
            exit(1);
        }
        files[0] = calloc(1,sizeof(char));
        if (files[0] == NULL)
        {
            perror("files[x]");
            exit(1);
        }

    // -----------------------------------
        char* mode = calloc(1,sizeof(char));
        mode = "0777";
        int nbOptions = 0;
        int nbFiles = 0;
        int i, c;

    // -----------------------------------
    // parcourt des arguments de la fonction

        if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
            while (1) {
                int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
                static struct option long_options[] = {
                    {"help",     no_argument,             0, 'h'},
                    {"mode",     required_argument,       0, 'm'},
                    {"verbose",  no_argument,             0, 'v'}
                };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
                c = getopt_long(argc, argv, "hvm:", long_options, &option_index);

                if (c == -1) break;

        //switch en fonction des options rentrées par l'user
                switch (c) {

                 case 'h': 
                 printf("\n-----------------------------------------------------------\n");
                 printf("Usage: mkdir [OPTION]... DIRECTORY...\n");
                 printf("Create the DIRECTORY(ies), if they do not already exist.\n\n");
                 printf("    -v, --verbose        explain what is being done\n");
                 printf("    -m, --mode=MODE      set file mode (as in chmod)\n");
                 printf("\n-----------------------------------------------------------\n\n");
                 exit(0);
                 break;

                 case 'v':
                 
                 options[nbOptions] = c;
                 nbOptions++;
                 
                 break;

                 case 'm':
                 if (atoi(optarg)){
                    mode = optarg;
                    options[nbOptions] = c;
                    nbOptions++;
                    
                }
                else {
                    printf("mkdir : -m option requires a mode as an argument\n");
                    printf("Try 'mkdir --help' for more information.\n");
                    exit(1);
                }
                break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
                default:
                printf("Try 'mkdir --help' for more information.\n");
                exit(1);
            }
        }
        //Boucle pour parcourir les arguments qui ne sont pas des options
        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files=realloc(files, (nbFiles)*sizeof(char*));
                if (files == NULL)
                {
                    perror("files");
                    exit(1);
                }
                files[nbFiles] = calloc(1,sizeof(char));
                if (files[nbFiles] == NULL)
                {
                    perror("files[x]");
                    exit(1);
                }
                files[nbFiles-1]=concatenateTables(files[nbFiles-1], argv[i]);
            }
        }
        // if bon nombre d'arguments
        if (nbFiles > 0)
        {
            create_dir(files, nbFiles, options, nbOptions, mode);   
        }
        else
        {
            printf("mkdir : invalid number of arguments\n");
            printf("Try 'mkdir --help' for more information.\n");
        }

        int l;
        for(l=0;l<nbFiles;l++){
            free(files[nbFiles]);
        }
        free(files);
        free(options);


    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("mkdir : invalid number of arguments\n");
        printf("Try 'mkdir --help' for more information.\n");
    }

    return 0;
}

void create_dir(char** files, int nbFiles, char* options, int nbOptions, char* modeS){
    // ----------------------------------
    // Initialisation
    // ----------------------------------
    struct stat statbuf;
    // ----------------------------------
    // Lecture des options
    // ----------------------------------
    mode_t mode;
    int i;
    for(i=0; i<=nbFiles; i++){
        if (stat(files[i], &statbuf) != -1) { //si il existe déjà un dossier/fichier déjà nommé comme celui qu'on essaye de créer
            printf("mkdir : '%s' already exists\n", files[i]);
        }
        else {
            if(strstr(options, "v") != NULL) {
                printf("Creating %s/\n", files[i]);
            }
            mode = strtol(modeS, NULL, 8);
            mkdir(files[i], mode);
        }
    }
}