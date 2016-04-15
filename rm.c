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

#include "../../include/commands/rm.h"



int rm_lib(int argc, char *argv[]){

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
    files = malloc(32*sizeof(char**));
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
    int i, c, j, k;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
            int option_index = 0;

            //structure donnant les options gérées par la commande
                //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
            static struct option long_options[] = {
                {"help",        no_argument,       0, 'h'},
                {"recursive",   no_argument,       0, 'r'},
                {0,             no_argument,       0, 'i'},
                {"verbose",     no_argument,       0, 'v'}
            };

            //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
                //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
            c = getopt_long(argc, argv, "hvir", long_options, &option_index);

            if (c == -1) break;

            //switch en fonction des options rentrées par l'user
            switch (c) {

                case 'h': 
                printf("\n-----------------------------------------------------------\n");
                printf("Usage: rm [OPTION]... FILE...\n");
                printf("Remove FILE(s)\n\n");
                printf("    -v, --verbose        explain what is being done\n");
                printf("    -r, --recursive      remove directories and their contents recursively\n");
                printf("    -i                   prompt before every removal\n");
                printf("\n-----------------------------------------------------------\n\n");
                exit(0);
                break;

                case 'v':
                options[nbOptions] = c; 
                nbOptions++;
                break;

                case 'r':
                options[nbOptions] = c; 
                nbOptions++;
                break;

                case 'i':
                options[nbOptions] = c; 
                nbOptions++;
                break;

                //message par défaut quand l'option rentrée n'est pas gérée par la commande
                default:
                printf("Try 'rm --help' for more information.\n");
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
        if (nbFiles >= 1)
        {
            for(j=1; j<=nbFiles; j++){
                suppression(files[j], options);
            }   
        }
        else
        {
            printf("rm : invalid number of arguments\n");
            printf("Try 'rm --help' for more information.\n");
        }



    }
//SI pas d'arguments => on affiche une erreur
    else
    {
        printf("rm : invalid number of arguments\n");
        printf("Try 'rm --help' for more information.\n");
    }
    for(k=1; k<=nbFiles; k++){
        free(files[k]);
    }
    free(files);
    free(options);
    return 0;
}

void suppression(char * file, char * options){
    struct stat statbuf;

    char c;

    DIR *dirp;
    struct dirent *dptr;

    char* recur = NULL;
    recur = malloc(PATH_MAX*sizeof(char));
    if (recur == NULL)
    {
        perror("recur");
        exit(1);
    }

    if (lstat(file,&statbuf)==-1) { //si le fichier n'existe pas
        printf("rm : '%s' n'existe pas\n", file);
        exit(1);
    }

    if(S_ISDIR(statbuf.st_mode)){ //si le fichier est un répertoire

        if((dirp=opendir(file))==NULL){ //si impossible de l'ouvrir
            printf("rm : impossible d'ouvrir '%s'\n", file);
        }
        else {
            if(strstr(options, "r") != NULL){ //si on a l'option -r on rentre dans la procédure pour supprmimer le dossier de manière récursive
                while((dptr=readdir(dirp))){

                    if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")){ //pour que l'on ne supprime pas le dossier ou le dossier parent
                        continue;
                    } 

                    if (file[strlen(file)-1]=='/'){ //si le dossier n'a pas de / dans son nom
                        sprintf(recur,"%s%s",file,dptr->d_name); 
                    } 
                    else { 
                        sprintf(recur,"%s/%s",file,dptr->d_name);
                    }
                    //récursion
                    suppression(recur, options);
                }
                if(strstr(options, "i")){ //si on a l'option -i
                    printf("Supprimer le repertoire '%s' (y/n) ? ", file); //on demande confirmation de suppression
                    c='\n';
                    while(c =='\n') c=getchar(); //petit tricks pour pas prendre le retour chariot
                    if((c == 'y')){
                        if(strstr(options, "v") != NULL){ //si option --verbose, on affiche ce que l'on fait
                            printf("Suppression du répertoire '%s'\n", file);
                        }

                        remove(file);
                    }
                }
                else { //si pas l'option -i, on ne demande pas confirmation
                    if(strstr(options, "v") != NULL){
                        printf("Suppression du répertoire '%s'\n", file);
                    }
                    remove(file);
                }


                closedir(dirp);
            }

            else{ //si on a pas l'option -r
                printf("rm: impossible de supprimer '%s': est un dossier\n", file);
            }
        }
    }
    else{
        if(strstr(options, "i")){
            printf("Supprimer '%s' (y/n) ? ", file);
            c='\n';
            while(c=='\n') c=getchar();
            if((c == 'y')){
                if(strstr(options, "v") != NULL){
                    printf("Suppression de '%s'\n", file);
                }
                remove(file);
            }
        }
        else {
            if(strstr(options, "v") != NULL){
                printf("Suppression de '%s'\n", file);
            }
            remove(file);
        }
    }  
}