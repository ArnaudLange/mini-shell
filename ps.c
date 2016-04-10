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
//#include "../../include/commands/fonction.h"

#include "ps.h" //à virer une fois les tests effectués


int main(int argc, char *argv[]){

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
    int c;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"helpArg",     required_argument,       0, 'z'},
            {"help",     no_argument ,       0, 'h'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "h", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: ps [OPTION]\n\n");
           printf("\tTry 'ps --helpArg <simple|list|output|threads|misc|all>'\n");
           printf("\tor 'ps --helpArg <s|l|o|t|m|a>'\n");
           printf("\tfor additional help text.");
           printf("\n-----------------------------------------------------------\n");
           exit(0);
           break;

         case 'z':
            if(!strcmp(optarg,"simple") || !strcmp(optarg,"s")){
                printf("\n-----------------------------------------------------------\n");
                printf("Basic options:\n");
                printf("\t-A, -e               all processes\n");
                printf("\t-a                   all with tty, except session leaders\n");
                printf("\t-d                   all except session leaders\n");
                printf("\t-N, --deselect       negate selection");
                printf("\n-----------------------------------------------------------\n");

            }
            else if(!strcmp(optarg,"list") || !strcmp(optarg,"l")){
                printf("On est dans list.\n");
            }
            if(!strcmp(optarg,"output") || !strcmp(optarg,"o")){
                printf("On est dans output.\n");
            }
            if(!strcmp(optarg,"threads") || !strcmp(optarg,"t")){
                printf("On est dans threads.\n");
            }
            else if(!strcmp(optarg,"misc") || !strcmp(optarg,"m")){
                printf("On est dans misc.\n");
            }
            else if(!strcmp(optarg,"all") || !strcmp(optarg,"a")){
                printf("On est dans all.\n");
            }
            break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'fonction --help' for more information.\n");
            exit(1);
      }
    }
    

    }
    return 0;
}
