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

#include "echo.h" //à virer une fois les tests effectués

int main(int argc, char *argv[]){

    // -----------------------------------
    // Declaration tableau une dimension pour les options

    char* options = NULL;
    options = (char*) calloc(2, sizeof(*options));
    if (options == NULL)
    {
        perror("options");
        exit(1);
    }

    char* argv2 = NULL;
    argv2 = (char*) calloc(1, sizeof(*options));
    if (argv2 == NULL)
    {
        perror("options");
        exit(1);
    }

    int c,i;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"n",     no_argument,       0, 'n'},
            {"e",     no_argument,       0, 'e'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "ne", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'n':
            options[0]=1;
            break;

         case 'e':
            options[0]=1;
            break;
         default:
            printf("default\n");
        }
        }
    }
    if (options[0]!=1 && options[1]!=1){
        for(i=1; i<argc; i++){
            printf("%s ",argv[i]);
        }
        printf("\n");
    }
    else if (options[0]==1 && options[1]!=1){
        cleanTable(argc, argv, options);
    }
    else if (options[1]==1 && options[0]!=1){
        cleanTable(argc, argv, options);
    }
    else if (options[1]==1 && options[0]==1){
        cleanTable(argc, argv, options);
    }

    return 0;
}

