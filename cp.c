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

//** à décommenter et à completer une fois la fonction finies **//
//#include "../../include/commands/cp.h"

#include "cp.h" //à virer une fois les tests effectués


int cp_lib(int argc, char *argv[]){

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

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"help",                 no_argument,           0, 'h'},
            {"recursive",            no_argument,           0, 'r'},
            {"target-directory",     required_argument,     0, 't'},
            {"no-target-directory",  no_argument,           0, 'T'},
            {"verbose",              no_argument,           0, 'v'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "hvTrt:", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: cp [OPTION]... [-T] SOURCE DEST\n");
           printf("       cp [OPTION]... SOURCE... DIRECTORY\n");
           printf("       cp [OPTION]... -t DIRECTORY SOURCE...\n");
           printf("Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.\n\n");
           printf("    -v, --verbose                 explain what is being done\n");
           printf("    -r, --recursive               copy directories recursively\n");
           printf("    -t, --target-directory        copy all SOURCE arguments into DIRECTORY\n");
           printf("    -T, --no-target-directory     treat DEST as a normal file\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

         case 'v':
           options[nbOptions] = c; 
           nbOptions++;
           break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'fonction --help' for more information.\n");
            exit(1);
      }
    }
        //Boucle pour parcourir les arguments qui ne sont pas des options
        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files[nbFiles] = malloc(16*sizeof(char*));

                concatenateTables(files[nbFiles],argv[i]);


            }
        }
        // if nombre d'arguments invalide
        if (nbFiles == 2)
        {
            myMv(files[1],files[2], options, nbOptions);   
        }
        else
        {
            printf("fonction : invalid number of arguments\n");
            printf("Try 'fonction --help' for more information.\n");
        }
        free(files);
        free(options);


    }
    //** A changer **//
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("fonction : invalid number of arguments\n");
    }

    return 0;
}
