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
            {"verbose",  no_argument,       0, 'v'},
            {"example",  no_argument,       0, 'e'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "hve", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: chmod [OPTION]... MODE[,MODE]... FILE...\n");
           printf("Change the mode of each FILE to MODE.\n\n");
           printf("    -v, --verbose        output a diagnostic for every file processed\n");
           printf("    -e, --example        shows an example\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

         case 'v':
           option=1;
           break;

         case 'e':
           printf("\n-----------------------------------------------------------\n");
           printf("chmod: example\n");
           printf("\tchmod [OPTION]... MODE[,MODE]... FILE...\n");
           printf("\tchmod -v u+x,g-r file1 file2\n");
           printf("\nHere, the option 'verbose' is activated\n");
           printf("chmod will add the right to execute for the user, and remove\n");
           printf("for the group, the right to read.\n");
           printf("And this, on both files : file1 and file2.\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("chmod : invalid option.\n");
            printf("Try 'chmod --help' for more information.\n");
            exit(1);
        }
        }
    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("chmod : invalid number of arguments.\n");
        printf("Try 'chmod --help' for more information.\n");
        exit(1);
    }

    if (argc>2 && option != 1){
        for (i=2; i<argc && *argv[i]!='-'; i++){
            myChmod(0, argv[1], argv[i]);
        }
    }
    else if (argc > 3 && option){
        int iOption=0;
        int k;
        for (i=1; i<argc; i++){
            if (*argv[i] == '-'){
                iOption=i+1;
            }
        }
        if (argc-2<iOption){
            printf("chmod : invalid number of arguments.\n");
            printf("Try 'chmod --help' for more information.\n");
            exit(1);
        }
        else{
            for(k = iOption+1; k<argc; k++){
                myChmod(option,argv[iOption],argv[k]);
            }
        }
    }
    else{
        printf("chmod : invalid number of arguments.\n");
        printf("Try 'chmod --help' for more information.\n");
        exit(1);
    }

    return 0;
}

void myChmod(int option, char* mode, char* file){

    int sf;
    struct stat statbuf;
    char modeAvant[9];
    char modeApres[9];

    //initialisation des tableaux
    int w;
    for (w=0; w<9; w++){
        modeAvant[w]='-';
        modeApres[w]='-';
    }

    // Prise des donnees avant changement
    sf = openFile(file);
    if(sf == -1){
        perror(file);
        exit(1);
    }
    
    if (fstat(sf,&statbuf)==-1){
        perror("fstat");
        exit(1);
    }

    //Recuperation du mode
    int valUsr=0;
    if (statbuf.st_mode & S_IRUSR){
        valUsr+=4;
        modeAvant[0]='r';
    }
    if (statbuf.st_mode & S_IWUSR){
        valUsr+=2;
        modeAvant[1]='w';
    }
    if (statbuf.st_mode & S_IXUSR){
        valUsr+=1;
        modeAvant[2]='x';
    }
    int valGrp=0;
    if (statbuf.st_mode & S_IRGRP){
        valGrp+=4;
        modeAvant[3]='r';
    }
    if (statbuf.st_mode & S_IWGRP){
        valGrp+=2;
        modeAvant[4]='w';
    }
    if (statbuf.st_mode & S_IXGRP){
        valGrp+=1;
        modeAvant[5]='x';
    }
    int valOth=0;
    if (statbuf.st_mode & S_IROTH){
        valOth+=4;
        modeAvant[6]='r';
    }
    if (statbuf.st_mode & S_IWOTH){
        valOth+=2;
        modeAvant[7]='w';
    }
    if (statbuf.st_mode & S_IXOTH){
        valOth+=1;
        modeAvant[8]='x';
    }

    int intMAvant=0;
    intMAvant=100*valUsr+10*valGrp+valOth;

    mode_t modeConv=strtol(mode,NULL,8);

    if (atoi(mode)==0){
        printf("%s n'est pas un nombre \n",mode);
    }
    else{
        if(intMAvant == atoi(mode)){
            if (option){
                printf("mode of '%s' retained as 0%d (%s)\n",file, intMAvant,modeAvant);
            }
        }
        else{
            modeConv=strtol(mode,NULL,8);
            chmod(file,modeConv);
            if (option){
                printf("mode of '%s' changed from 0%d to %o\n",file,intMAvant,modeConv);
            }
        }
    }

}