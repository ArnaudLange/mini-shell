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

#include "../../include/commands/du.h"


    int du_lib(int argc, char *argv[]){

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
        files = malloc(256*sizeof(char**));
        if (files == NULL)
        {
            perror("files");
            exit(1);
        }
        files[0] = malloc(32*sizeof(char*));
        if (files[0] == NULL)
        {
            perror("files[x]");
            exit(1);
        }
        
        // -----------------------------------

        int nbOptions = 0;
        int nbFiles = 0;
        int i, c;
        long int size = 0;

        // -----------------------------------
        // parcourt des arguments de la fonction

        if (argc >1) {

            //Boucle pour parcourir les options, exemple avec les options verbose et help
            while (1) {
                int option_index = 0;

                //structure donnant les options gérées par la commande
                //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
                static struct option long_options[] = {
                    {"help",            no_argument,       0,   0},
                    {"all",             no_argument,       0, 'a'},
                    {"human-readable",  no_argument,       0, 'h'},
                    {"total",           no_argument,       0, 'c'}
                };

                //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
                //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
                c = getopt_long(argc, argv, "hca0", long_options, &option_index);

                if (c == -1) break;

                //switch en fonction des options rentrées par l'user
                switch (c) {

                    case 0: 
                    printf("\n-----------------------------------------------------------\n");
                    printf("Usage: du [OPTION]... FILE\n");
                    printf("estimate FILE space usage\n\n");
                    printf("    -c, --total               produce a grand total\n");
                    printf("    -a, --all                 write counts for all files, not just directories\n");
                    printf("    -h, --human-readable      print sizes in human readable format\n");
                    printf("\n-----------------------------------------------------------\n\n");
                    exit(0);
                    break;

                    case 'c':
                    options[nbOptions] = c;
                    nbOptions++;
                    break;

                    case 'a':
                    options[nbOptions] = c;
                    nbOptions++;
                    break;

                    case 'h':
                    options[nbOptions] = c;
                    nbOptions++;
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

            size = giveSize(files[1], options);   
        }
        else if(nbFiles == 0){

            size = giveSize(".", options);
        }
        else
        {
            for (i=1;i<=nbFiles;i++){
                size += giveSize(files[i], options);
            }
        }
        


    }
    //SI pas d'arguments 
    else
    {
        size = giveSize(".", options);
    }
    printf("\n");
    if(strstr(options, "c") !=NULL){
        if(strstr(options, "h") != NULL){
            affichePropreConv(size, "Taille totale");
        }
        else affichePropre(size, "Taille totale");
        
    }

    for (i=1;i<=nbFiles;i++){
        free(files[i]);
    }

        free(files);
        free(options);
    return 0;
}

int giveSize(char* file, char * options){
    struct stat statbuf;

    long int size = 0;
    DIR *dirp;
    struct dirent *dptr;
    
    char* recur = NULL;
    recur = malloc(PATH_MAX*sizeof(char));
    if (recur == NULL)
    {
        perror("recur");
        exit(1);
    }

    if (lstat(file,&statbuf)==-1) {
        printf("du : '%s' n'existe pas\n", file);
        return 0;
    }
    size=statbuf.st_size;

    if(S_ISDIR(statbuf.st_mode)){

        if((dirp=opendir(file))==NULL){
            printf("du : impossible d'ouvrir '%s'\n", file);
        }
        else {
            
            while((dptr=readdir(dirp))){

                if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")){
                    continue;
                } 

                if (file[strlen(file)-1]=='/'){
                    sprintf(recur,"%s%s",file,dptr->d_name);
                } 
                else { 
                    sprintf(recur,"%s/%s",file,dptr->d_name);
                }
                size += giveSize(recur, options);
            }
            //affichage de la taille des dossiers
            if (file[strlen(file)-1]=='/'){
                affichePropre(size, file);
            }
            else{
                if(strstr(options, "h") !=NULL){
                    affichePropreConv(size, file);
                }

                else affichePropre(size, file);
            }
            closedir(dirp);
        }
    }
    else {
        //affichage de la taille des fichiers
        if(strstr(options, "a") !=NULL){
            if(strstr(options, "h") !=NULL){
                affichePropreConv(size, file);
            }

            else affichePropre(size, file);
        }

    }
    free(recur);
    return size;
}

void affichePropre(long int size, char * string){
    int nbDigits = floor(log10(abs(size))) + 1;
    int i;
    char * monoSpace = " ";
    char * spaces = NULL;
    spaces = calloc(16, sizeof(char*));
    if (spaces == NULL)
    {
        perror("files[x]");
        exit(1);
    }

    for(i=0; i<=(10-nbDigits); i++){

        spaces=concatenateTables(spaces, monoSpace);
    }

    printf("%ld%s%s\n",size, spaces, string);
    free(spaces);
}

void affichePropreConv(long int size, char * string){
    int nbDigits = floor(log10(abs(size))) + 1;
    int i;
    double nSize =0.0;
    char * monoSpace = " ";

    char * spaces = NULL;
    spaces = calloc(16, sizeof(char*));
    if (spaces == NULL)
    {
        perror("files[x]");
        exit(1);
    }

    if(nbDigits<=3){
        nSize = (double) size;

        nbDigits = floor(log10(abs(nSize))) + 1;
        for(i=0; i<=(8-nbDigits); i++){

            spaces=concatenateTables(spaces, monoSpace);
        }
        printf("%.1lf%s%s\n", nSize, spaces, string);
    }

    if(nbDigits>3 && nbDigits<=6){
        nSize = (double) size/1000;

        nbDigits = floor(log10(abs(nSize))) + 1;
        for(i=0; i<=(7-nbDigits); i++){

            spaces=concatenateTables(spaces, monoSpace);
        }
        printf("%.1lfK%s%s\n", nSize, spaces, string);
    }

    if(nbDigits>6 && nbDigits<=9){
        nSize = (double) size/1000000;

        nbDigits = floor(log10(abs(nSize))) + 1;
        for(i=0; i<=(7-nbDigits); i++){

            spaces=concatenateTables(spaces, monoSpace);
        }
        printf("%.1lfM%s%s\n", nSize, spaces, string);
    }

    if(nbDigits>9 && nbDigits<=12){
        nSize = (double) size/1000000000;

        nbDigits = floor(log10(abs(nSize))) + 1;
        for(i=0; i<=(7-nbDigits); i++){

            spaces=concatenateTables(spaces, monoSpace);
        }
        printf("%.1lfG%s%s\n", nSize, spaces, string);
    }

    if(nbDigits>12 && nbDigits<=15){
        nSize = (double) size/1000000000000;

        nbDigits = floor(log10(abs(nSize))) + 1;
        for(i=0; i<=(7-nbDigits); i++){

            spaces=concatenateTables(spaces, monoSpace);
        }
        printf("%.1lfT%s%s\n", nSize, spaces, string);
    }
   
    free(spaces);
}