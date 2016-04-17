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
//#include "../../include/commands/su.h"

#include "su.h" //à virer une fois les tests effectués


int main(int argc, char *argv[]){

    // -----------------------------------
    // Declaration tableau deux dimensions pour les options

    char* options = NULL;
    options = (char*) calloc(16, sizeof(*options));
    if (options == NULL)
    {
        perror("options");
        exit(1);
    }


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

    char** files = NULL;
    files = malloc(36*sizeof(char**));
    if (files == NULL)
    {
        perror("files");
        exit(1);
    }
    files[0] = malloc(36*sizeof(char*));
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
                {"help",     no_argument,       0, 'h'}
            };

            //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
                //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
            c = getopt_long(argc, argv, "hv", long_options, &option_index);

            if (c == -1) break;

            //switch en fonction des options rentrées par l'user
            switch (c) {

                case 'h': 
                printf("\n-----------------------------------------------------------\n");
                printf("Usage: su [OPTION]... USER\n");
                printf("Change the effective user id and group id to that of USER. \n\n");
                printf("\n-----------------------------------------------------------\n\n");
                exit(0);
                break;

                //message par défaut quand l'option rentrée n'est pas gérée par la commande
                default:
                printf("Try 'su --help' for more information.\n");
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
        // if nombre d'arguments valide
        if (nbFiles = 1)
        {
            changeUser(files[1], options);   
        }
        else
        {
            printf("su : invalid number of arguments\n");
            printf("Try 'su --help' for more information.\n");
        }
        free(files);
        free(options);


    }
    //SI pas d'arguments => on se log en root
    else {
        changeUser("root", options);
    }

    return 0;
}
