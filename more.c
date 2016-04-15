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

#include "more.h" //à virer une fois les tests effectués


int main(int argc, char *argv[]){

    // -----------------------------------
    // Declaration tableau une dimension pour les options

    char* options = NULL;
    options = (char*) calloc(3,sizeof(char));
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

    int nbLigne = 1;
    int nbFiles = 0;
    int i, c, j;

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
        c = getopt_long(argc, argv, "h", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: more [OPTION] FILE... \n\n");
           printf("press 'h' while the function is running to see the\n");
           printf("'in-function' options.\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'more --help' for more information.\n");
            exit(1);
      }
    }
        //Boucle pour parcourir les arguments qui ne sont pas des options
        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files=realloc(files, (nbFiles+1)*sizeof(char*));
                if(files == NULL){
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
        // if there are 2 files
        if (nbFiles >0)
        {
            for(j = 0; j < nbFiles; j++)
            {
                more(files[j],options, &nbLigne);
                free(files[j]);
            }   
        }
        else
        {
            more("",options,&nbLigne);
        }
        free(files);
        free(options);


    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("more : invalid number of parameters\n");
        printf("Try 'more --help' for more information.\n");
        exit(1);
    }

    return 0;
}


void getEtat(Etat *curEtat, char c){
    char command=getchar();

    if (command == 'h'){
        printf("\n----------------------------------------\n");
        printf("<space> \t\t\tDisplay next k lines of text [current screen size]\n");
        printf("<return>\t\t\tDisplay next 1 line of text\n");
        printf("q or Q  \t\t\tExit from more\n");
        printf("s       \t\t\tSkip forward 1 line of text\n");
        printf("f       \t\t\tSkip forward k screenfuls of text\n");
        printf("=       \t\t\tDisplay current line number\n");
        printf("----------------------------------------\n");
    }

    command=getchar();

    if (command == 10){
        printf("\33[2K");
        printf("\033[A\r%c",c);
        *curEtat = etatEntree;
    }
    else if (command == ' '){
        printf("\33[2K");
        printf("\033[A\r%c",c);
        *curEtat = etatSpace;
    }
    else if (command == 'q' || command == 'Q'){
        *curEtat = etatExit;
    }
    else if (command == 'f'){
        *curEtat = etatSkipKLignes;
    }
    else if (command == 's'){
        *curEtat = etatSkipScreenLignes;
    }
    else if (command == '='){
        *curEtat = etatLigneNumber;
    }
}

void more(char *file, char *option, int *nbLigne){
    printf("Nom du fichier : %s\n",file);

    FILE *fichier = NULL;
    char character;

    int i=1;
    char command;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);


    int ligneScreen = w.ws_row;

    if(strcmp(file,"")){
        fichier = fopen(file,"r");
        if(fichier == NULL){
            perror(file);
            exit(1);
        }

        Etat curEtat;
        curEtat=etatSpace;

        while((character=fgetc(fichier)) != EOF){

            switch (curEtat){
                case etatSpace:
                    if (i<ligneScreen){
                        printf("%c",character);

                        if (character == 10){
                            i++;
                            nbLigne++;
                        }
                        break;
                    }
                    else{
                        getEtat(&curEtat,character);
                        i=1;
                        break;
                    }

                case etatEntree:
                    if (character == 10){
                            getEtat(&curEtat,character);
                            break;
                        }
                    else{
                        printf("%c",character);
                    }
                    break;

                case etatExit:
                    exit(0);

                case etatSkipKLignes:
                    printf("Etat SkipKLignes\n");
                    break;

                case etatSkipScreenLignes:
                    printf("Etat SkipScreenLignes\n");
                    break;

                case etatLigneNumber:
                    printf("etatLigneNumber\n");
                    printf("%c",character);
                    break;


            }
        }
    }
    else{
        printf("\n-----------------------------------------------------------\n");
        printf("Usage: more [OPTION] FILE... \n\n");
        printf("press 'h' while the function is running to see the\n");
        printf("'in-function' options.\n");
        printf("\n-----------------------------------------------------------\n\n");
    }
}