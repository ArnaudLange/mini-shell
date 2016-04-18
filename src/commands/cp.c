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

#include "../../include/commands/cp.h"

int cp_lib(int argc, char *argv[]){

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
    int i, c, j, k;
    struct stat statbuf;

// -----------------------------------
// parcourt des arguments de la fonction

    if (argc >1) {

    //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
            int option_index = 0;

    //structure donnant les options gérées par la commande
        //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
            static struct option long_options[] = {
                {"help",                 no_argument,           0, 'h'},
                {"verbose",              no_argument,           0, 'v'}
            };

    //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
        //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
            c = getopt_long(argc, argv, "hv", long_options, &option_index);

            if (c == -1) break;

    //switch en fonction des options rentrées par l'user
            switch (c) {

                case 'h': 
                printf("\n-----------------------------------------------------------\n");
                printf("Usage: cp [OPTION]... SOURCE DEST\n");
                printf("       cp [OPTION]... SOURCE... DIRECTORY\n");
                printf("       cp [OPTION]... DIRECTORY1 DIRECTORY2\n");
                printf("Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY, or recursively DIRECTORY1 to DIRECTORY2.\n\n");
                printf("    -v, --verbose                 explain what is being done\n");
                printf("\n-----------------------------------------------------------\n\n");
                exit(0);
                break;

                case 'v':
                options[nbOptions] = c; 
                nbOptions++;
                break;

    //message par défaut quand l'option rentrée n'est pas gérée par la commande
                default:
                printf("Try 'cp --help' for more information.\n");
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

        if (nbFiles == 2)
        {
            copy(files[0],files[1], options, nbOptions);   
        }

        else if (nbFiles > 2) //si plus de deux fichiers en argument
        {
            if (lstat(files[nbFiles],&statbuf)==-1){ //si le dernier fichier n'existe pas

                if (mkdir(files[nbFiles],0777)){ //on le crée 
                    printf("cp : erreur de création du répertoire '%s', copie impossible\n",files[nbFiles]);
                    exit(1);
                }
                for(j=0; j<nbFiles; j++){ //on copie chaque fichier dedans
                    copy(files[j],files[nbFiles], options, nbOptions);
                }
            }
            else{ //si il existe
                if(S_ISDIR(statbuf.st_mode)){ //si c'est un dossier
                    for(j=0; j<nbFiles; j++){//on copie chaque fichier dedans
                        copy(files[j],files[nbFiles], options, nbOptions);
                    }
                }
                else {
                    printf("cp : erreur le fichier '%s' existe mais n'est pas un répertoire,  copie impossible\n",files[nbFiles]);
                }
            }
        }


        else {

            printf("cp : invalid number of arguments\n");
            printf("Try 'cp --help' for more information.\n");
        }
        


    }
//SI pas d'arguments => on affiche une erreur
    else
    {
        printf("cp : invalid number of arguments\n");
    }
    for(k=1; k<nbFiles; k++){
        free(files[nbFiles]);
    }
    free(files);
    free(options);
    return 0;
}

void copy(char* src, char* dst, char* options, int nbOptions){

    struct stat statbuf1,statbuf2;
    char *srcFile;
    //--------------------------------------
    char* recur = NULL;
    recur = malloc(PATH_MAX*sizeof(char));
    if (recur == NULL)
    {
        perror("recur");
        exit(1);
    }

    char* recur2 = NULL;
    recur2 = malloc(PATH_MAX*sizeof(char));
    if (recur2 == NULL)
    {
        perror("recur");
        exit(1);
    }
    //-------------------------------------
    DIR *dirp;
    struct dirent *dptr;
    int fileDest1,fileDest2,i;
    int BUFLEN = 32768;
    char buf[BUFLEN];

    struct utimbuf times;

    if(strcmp(options, "v")==0){
        printf("Copie de '%s' vers '%s'\n",src,dst);
    }


    if (lstat(src,&statbuf1)==-1) //si le fichier source n'existe pas
    {
        printf("cp : impossible d'ouvrir le fichier \"%s\"\n",src);
        return;
    }

    if (!S_ISDIR(statbuf1.st_mode)) //si le fichier source n'est pas un dossier
    {
        // On ne copie que les fichiers réguliers
        if ((statbuf1.st_mode & S_IFREG)==S_IFREG)
        {
            fileDest1=open(src,O_RDONLY);
            if (fileDest1==-1) //si l'on ne peut pas ouvrir le fichier source
            {
                printf("cp : impossible d'ouvrir le fichier source '%s'\n",src);
                return;
            }

            // Si la destination existe et est un répertoire, on crée un nouveau fichier dans ce répertoire
            if ((lstat(dst,&statbuf2)!=-1) && (S_ISDIR(statbuf2.st_mode)))
            {
                // Extraction du nom de fichier à copier
                i=strlen(src);
                while ((i>0) && (src[i]!='/')){
                    i--;
                }
                if (src[i]=='/'){
                    srcFile=&src[i+1];
                }
                else srcFile=&src[i];

                if (dst[strlen(dst)-1]=='/'){
                    sprintf(recur,"%s%s",dst,srcFile);
                } 
                else sprintf(recur,"%s/%s",dst,srcFile);
            }
            else strcpy(recur,dst);

            // Création du nouveau fichier
            fileDest2=open(recur,O_WRONLY | O_CREAT | O_EXCL);
            if (fileDest2==-1)
            {
                printf("cp : erreur d'accès au fichier '%s', copie impossible\n",recur);
                close(fileDest1);
                return;
            }

            // Copie du fichier
            while((i=read(fileDest1,buf,BUFLEN))!=0)
            {
                if (write(fileDest2,buf,i)==-1)
                {
                    close(fileDest1);
                    close(fileDest2);
                    return;
                }
            }

            close(fileDest1);

            // Préservation des propriétaires (user/group) -> pas de contrôle d'erreur, ne marche que si root !
            fchown(fileDest2,statbuf1.st_uid,statbuf1.st_gid);

            // Préservation des droits
            if (fchmod(fileDest2,statbuf1.st_mode)==-1)
            {
                printf("cp : erreur de changement de droits sur '%s'\n",recur);
            }
            close(fileDest2);

            // Préservation des horodatages
            times.actime=statbuf1.st_atime;
            times.modtime=statbuf1.st_mtime;
            if (utime(recur,&times)==-1)
            {
                printf("cp : erreur de changement de l'horodatage de '%s'\n",recur);
            }
        }
    }
    else
    {
    // Si la destination n'existe pas, on crée un nouveau répertoire
        if (lstat(dst,&statbuf2)==-1)
        {
            if (mkdir(dst,statbuf1.st_mode)==-1)
            {
                printf("cp : erreur de création du répertoire '%s', copie impossible\n",dst);
                return;
            }
            chown(dst,statbuf1.st_uid,statbuf1.st_gid);
        }
        else if (!S_ISDIR(statbuf2.st_mode))
        {
            printf("cp : la destination '%s' existe et n'est pas un répertoire -> copie impossible\n",dst);
            return;
        }

        if((dirp=opendir(src))==NULL)
        {
            printf("cp : erreur d'ouverture du répertoire '%s'\n",src);
            return;
        }

        while((dptr=readdir(dirp)))
        {
            if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")){
                continue;
            } 

            if (src[strlen(src)-1]=='/'){
                sprintf(recur,"%s%s",src,dptr->d_name);
            } 
            else sprintf(recur,"%s/%s",src,dptr->d_name);

            if (dst[strlen(dst)-1]=='/'){
                sprintf(recur2,"%s%s",dst,dptr->d_name);
            } 
            else sprintf(recur2,"%s/%s",dst,dptr->d_name);

            copy(recur,recur2, options, nbOptions);
        }
        closedir(dirp);
    }
    free(recur);
    free(recur2);
}
