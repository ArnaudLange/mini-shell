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

#include "../../include/commands/chgrp.h"

int chgrp_lib(int argc, char *argv[]){

    // -----------------------------------
    // Declaration tableau pour les options


        char* options = NULL;
        options = calloc(1, sizeof(char));
        if (options == NULL)
        {
            perror("options");
            exit(1);
        }


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

        char** files = NULL;
        files = calloc(1,sizeof(char*));
        if (files == NULL)
        {
            perror("files");
            exit(1);
        }
        files[0] = calloc(1,sizeof(char));
        if (files[0] == NULL)
        {
            perror("files[x]");
            exit(1);
        }


    // -----------------------------------

    int nbOptions = 0;
    int nbFiles = 0;
    int i, j, k, c;

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
                {"recursive",   no_argument,       0, 'R'},
                {"verbose",     no_argument,       0, 'v'}
            };

            //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
                //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
            c = getopt_long(argc, argv, "hvR", long_options, &option_index);

            if (c == -1) break;

            //switch en fonction des options rentrées par l'user
            switch (c) {

                case 'h': 
                printf("\n-----------------------------------------------------------\n");
                printf("Usage: chgrp [OPTION]... GROUP FILE...\n");
                printf("Change the group of each FILE to GROUP.\n\n");
                printf("    -v, --verbose        explain what is being done\n");
                printf("    -R, --recursive      operate on files and directories recursively\n");
                printf("\n-----------------------------------------------------------\n\n");
                exit(0);
                break;

                case 'v':
                options[nbOptions] = c; 
                nbOptions++;
                break;

                case 'R':
                options[nbOptions] = c; 
                nbOptions++;
                break;

                //message par défaut quand l'option rentrée n'est pas gérée par la commande
                default:
                printf("Try 'chgrp --help' for more information.\n");
                exit(1);
            }
        }
        //Boucle pour parcourir les arguments qui ne sont pas des options
        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files=realloc(files, (nbFiles)*sizeof(char*));
                if (files == NULL)
                {
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
        // if nombre d'arguments valide
        if (nbFiles >= 2){
            for(j=1; j<nbFiles; j++){
                changeGrp(files[j], files[0], options);
            }
        }
        else{
            printf("chgrp : invalid number of arguments\n");
            printf("Try 'chgrp --help' for more information.\n");
        }
        


    }
    //SI pas d'arguments => on affiche une erreur
    else{
        printf("chgrp : invalid number of arguments\n");
        printf("Try 'chgrp --help' for more information.\n");
    }
    for(k=1; k<=nbFiles; k++){
        free(files[k]);
    }
    free(files);
    free(options);
    return 0;
}

void changeGrp(char * file, char * group, char * options){
    struct stat statbuf;

    DIR *dirp;
    struct dirent *dptr;

    char* recur = NULL;
    recur = malloc(PATH_MAX*sizeof(char));
    if (recur == NULL)
    {
        perror("recur");
        exit(1);
    }

    gid_t gid;

    char *endptr;
    struct passwd *pwd;


    gid = strtol(group, &endptr, 10); //si un nombre est rentré en tant que groupe 
    if (*endptr != '\0') {         // si non
        pwd = getpwnam(group);   // on essaye d'obtenir le gid du groupe spécifié
        if (pwd == NULL) {
            printf("chgrp: le groupe '%s' n'existe pas\n", group);
            exit(1);
        }

        gid = pwd->pw_gid;
    }

    
    //-----------------------------

    if (lstat(file,&statbuf)==-1) { //si le fichier n'existe pas
        printf("chgrp : '%s' n'existe pas\n", file);
        exit(1);
    }

    if(S_ISDIR(statbuf.st_mode)){ //si le fichier est un répertoire


        if((dirp=opendir(file))==NULL){ //si impossible de l'ouvrir
            printf("chgrp : impossible d'ouvrir '%s'\n", file);
        }
        else {
            if(strstr(options, "R") != NULL){ //si on a l'option -r on rentre dans la procédure pour changer le groupe du dossier de manière récursive
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
                    changeGrp(recur, group, options);
                }
                if(strstr(options, "v") != NULL){
                    printf("Modification du groupe propriétaire de '%s' en '%s'\n", file, group);
                }
                if (chown(file, -1, gid) == -1) { //on modifie le groupe
                    printf("chgrp : erreur de modification groupe propriétaire '%s'\n", file);
                    exit(1);
                }

                closedir(dirp);
            }

            else{ //si on a pas l'option -r
                if(strstr(options, "v") != NULL){
                    printf("Modification du groupe propriétaire de '%s' en '%s'\n", file, group);
                }
                if (chown(file, -1, gid) == -1) { //on modifie le groupe
                    printf("chgrp : erreur de modification groupe propriétaire '%s'\n", file);
                    exit(1);
                }
            }
        }
    }
    else{
        if(strstr(options, "v") != NULL){
            printf("Modification du groupe propriétaire de '%s' en '%s'\n", file, group);
        }
        if (chown(file, -1, gid) == -1) { //on modifie le proprio/groupe
            printf("chgrp : erreur de modification groupe propriétaire '%s'\n", file);
            exit(1);
        }
    }   
    

    if(strstr(options, "R") != NULL){
        free(recur);
    }
}