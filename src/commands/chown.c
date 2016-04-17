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

#include "../../include/commands/chown.h"



int chown_lib(int argc, char *argv[]){

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
                printf("Usage: chown [OPTION]... [OWNER][:[GROUP]] FILE...\n");
                printf("Change FILE(s) OWNER and GROUP\n\n");
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
                printf("Try 'chown --help' for more information.\n");
                exit(1);
            }
        }
        //Boucle pour parcourir les arguments qui ne sont pas des options
        for (i=1; i<argc; i++){
            if(argv[i][0] != '-'){
                nbFiles++;
                files[nbFiles] = malloc(16*sizeof(char*));

                concatenateTables(files[nbFiles],argv[i]);


            }
        }
        // if nombre d'arguments valide
        if (nbFiles >= 2){
            for(j=2; j<=nbFiles; j++){
                changeOwn(files[j], files[1], options);
            }
        }
        else{
            printf("chown : invalid number of arguments\n");
            printf("Try 'chown --help' for more information.\n");
        }
        


    }
    //SI pas d'arguments => on affiche une erreur
    else{
        printf("chown : invalid number of arguments\n");
        printf("Try 'chown --help' for more information.\n");
    }
    for(k=1; k<=nbFiles; k++){
        free(files[k]);
    }
    free(files);
    free(options);
    return 0;
}

void changeOwn(char * file, char * ownGr, char * options){
    struct stat statbuf;

    char c;
    int i, j, etat;

    char* owner = NULL;
    owner = (char*) calloc(16, sizeof(*owner));
    if (owner == NULL)
    {
        perror("owner");
        exit(1);
    }

    char* group = NULL;
    group = (char*) calloc(16, sizeof(*group));
    if (group == NULL)
    {
        perror("options");
        exit(1);
    }


    DIR *dirp;
    struct dirent *dptr;

    char* recur = NULL;
    recur = malloc(PATH_MAX*sizeof(char));
    if (recur == NULL)
    {
        perror("recur");
        exit(1);
    }

    uid_t uid;
    gid_t gid;

    char *endptr, *endptr2;
    struct passwd *pwd;

    //-----------------------------
    //Parsing de ownGr pour en extraire l'owner et le groupe
    if(strstr(ownGr, ":") != NULL){ //si on donne le groupe en plus du nouveau propriétaire
        j = 0;
        etat = 0;
        for(i=0; i<=strlen(ownGr); i++){
            c = ownGr[i];
            if(etat == 0){
                if(c != ':'){
                    owner[i] = c;
                }
                else {
                    owner[i] = '\0';
                    etat++;
                }
            }
            else {
                group[j] = c;
                j++;
            }
            
        }
        group[j] = '\0';
    }
    else {
        owner = ownGr;
        gid = -1;
    }

    
    

    uid = strtol(owner, &endptr, 10);  // si l'id rentré est un nombre

    if (*endptr != '\0') {         // si non
        pwd = getpwnam(owner);   // on essaye d'obtenir l'uid de l'username spécifié
        if (pwd == NULL) {
            printf("chown : l'utilisateur '%s' n'existe pas\n", owner);
            exit(1);
        }

       uid = pwd->pw_uid;
    }

    if(strstr(ownGr, ":") != NULL){ //si on donne le groupe en plus du nouveau propriétaire
        gid = strtol(group, &endptr2, 10);
        if (*endptr2 != '\0') {         // si non
            pwd = getpwnam(group);   // on essaye d'obtenir le gid du groupe spécifié
            if (pwd == NULL) {
                printf("chown : le groupe '%s' n'existe pas\n", group);
                exit(1);
            }

            gid = pwd->pw_gid;
        }
    }
    
    //-----------------------------

    if (lstat(file,&statbuf)==-1) { //si le fichier n'existe pas
        printf("chown : '%s' n'existe pas\n", file);
        exit(1);
    }

    if(S_ISDIR(statbuf.st_mode)){ //si le fichier est un répertoire


        if((dirp=opendir(file))==NULL){ //si impossible de l'ouvrir
            printf("chown : impossible d'ouvrir '%s'\n", file);
        }
        else {
            if(strstr(options, "R") != NULL){ //si on a l'option -r on rentre dans la procédure pour changer le propriétaire du dossier de manière récursive
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
                    changeOwn(recur, ownGr, options);
                }
                if(strstr(options, "v") != NULL){
                    printf("Modification du propriétaire de '%s' en '%s'\n", file, owner);
                    if(gid != -1) printf("Modification du groupe propriétaire de '%s' en '%s'\n", file, group);
                }
                if (chown(file, uid, gid) == -1) { //on modifie le proprio/groupe
                    printf("chown : erreur de modification propriétaire '%s'\n", file);
                    exit(1);
                }

                closedir(dirp);
            }

            else{ //si on a pas l'option -r
                if(strstr(options, "v") != NULL){
                    printf("Modification du propriétaire de '%s' en '%s'\n", file, owner);
                    if(gid != -1) printf("Modification du groupe propriétaire de '%s' en '%s'\n", file, group);
                }
                if (chown(file, uid, gid) == -1) { //on modifie le proprio/groupe
                    printf("chown : erreur de modification propriétaire '%s'\n", file);
                    exit(1);
                }
            }
        }
    }
    else{
        if(strstr(options, "v") != NULL){
            printf("Modification du propriétaire de '%s' en '%s'\n", file, owner);
            if(gid != -1) printf("Modification du groupe propriétaire de '%s' en '%s'\n", file, group);
        }
        if (chown(file, uid, gid) == -1) { //on modifie le proprio/groupe
            printf("chown : erreur de modification propriétaire '%s'\n", file);
            exit(1);
        }
    }   
    
    if(strstr(ownGr, ":") != NULL){
        free(group);
        free(owner);
    }

    if(strstr(options, "R") != NULL){
        free(recur);
    }
}
