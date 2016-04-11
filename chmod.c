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

#include "chmod.h" //à virer une fois les tests effectués


void myChmod(int option, char* mode, char* file){
    if (option){
        printf("Option verbose.\n");
        printf("mode of '%s' changed from [...] to %s\n",file,mode);
    }
    printf("Mode : %s\n",mode);
    printf("File : %s\n",file);
    printf("\n");

    int sf;
    struct stat statbuf;

    sf = openFile(file);
    if(sf == -1){
        perror(file);
        exit(1);
    }
    else{
        printf("Ouverture de '%s' reussie.\n",file);
    }
    
    if (fstat(sf,&statbuf)==-1){
        perror("fstat");
        exit(1);
    }
    else{
        printf("Prise du buffer stat sur '%s' reussie.\n",file);
    }

    printf("Mode de '%s' : %d\n",file,statbuf.st_mode);


}

int main(int argc, char *argv[]){


    // -----------------------------------
    int i, c;
    int option=0;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'},
            {"verbose",  no_argument,       0, 'v'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "hv", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: chmod [OPTION]... MODE[,MODE]... FILE...\n");
           printf("Change the mode of each FILE to MODE.\n\n");
           printf("    -v, --verbose        output a diagnostic for every file processed\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

         case 'v':
           option=1;
           break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("chmod : invalid option.\n");
            printf("Try 'chmod --help' for more information.\n");
            exit(1);
        }
        }
        if (argc<3){
            printf("chmod : invalid option.\n");
            printf("Try 'chmod --help' for more information.\n");
            exit(1);
        }
    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("chmod : invalid number of arguments.\n");
        printf("Try 'chmod --help' for more information.\n");
        exit(1);
    }

    if (argc>3){
        for (i=3; i<argc && *argv[i]!='-'; i++){
            myChmod(option, argv[2], argv[i]);
        }
    }

    return 0;
}
