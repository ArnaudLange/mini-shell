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
//#include "../../include/commands/du.h"

#include "du.h" //à virer une fois les tests effectués


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

    //int nbOptions = 0;
    int nbFiles = 0;
    int i, c, size;
    size = 0;
    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"help",            no_argument,       0, 'h'},
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "hH", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: du [OPTION]... FILE\n");
           printf("estimate FILE space usage\n\n");
           printf("    no options available\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;


        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'du --help' for more information.\n");
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
        if (nbFiles == 1){

            size = giveSize(files[1]);   
        }
        else if(nbFiles == 0){

            size = giveSize(".");
        }
        else
        {
            size=0;
            for (i=1;i<nbFiles;i++){
                size+=giveSize(files[nbFiles]);
            }
        }
        free(files);
        free(options);


    }
    //** A changer **//
    //SI pas d'arguments => on affiche une erreur
    else
    {
        size = giveSize(".");
    }

    printf("Taille totale : %d\n", size);
    return 0;
}

int giveSize(char* file) {
    struct stat st;

    int size = 0;
    DIR *dirp;
    struct dirent *dptr;

    char* slash = "/";
    
    char* recur = NULL;
    recur = malloc(sizeof(char*));
    if (recur == NULL)
    {
        perror("recur");
        exit(1);
    }


    if (lstat(file,&st)==-1)
    {
        fprintf(stderr,"error (%d) %s\n",errno,strerror(errno));
        return 0;
    }
    size=st.st_size;
    printf("taille : %d\n", size);

    if (S_ISDIR(st.st_mode)){

        if ((dirp=opendir(file))==NULL){
            fprintf(stderr,"error (%d) %s\n",errno,strerror(errno));
        }
        else{

            while((dptr=readdir(dirp))){
                printf("taille2 : %d\n", size);

                if (file[strlen(file)-1]=='/'){
                    /*
                    printf("taille2.5 : %s\n", dptr->d_name);
                    recur= concatenateTables(file,dptr->d_name);
                    printf("taille3 : %d\n", size);
                    */
                    printf("%s%s\n",file,dptr->d_name);
                    sprintf(recur,"%s%s",file,dptr->d_name);
                } 
                else{
                    /*
                    printf("taille3.5 : %s\n", dptr->d_name);
                    recur = concatenateTables(file,slash);
                    printf("taille3.6 : %d\n", size);
                    recur = concatenateTables(recur,dptr->d_name);
                    printf("taille4 : %d\n", size);
                    */
                    printf("%s/%s\n",file,dptr->d_name);
                    sprintf(recur,"%s/%s",file,dptr->d_name);
                }
                printf("taille5 : %d\n", size);
                size += giveSize(recur);
                printf("taille6 : %d\n", size);
            }
            closedir(dirp);
        }
    }
    printf("taille7 : %d\n", size);
    return size;
}