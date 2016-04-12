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
//#include "../../include/commands/cp.h"

#include "cp.h" //à virer une fois les tests effectués

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

        int nbOptions = 0;
        int nbFiles = 0;
        int i, c;

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
                    {"recursive",            no_argument,           0, 'r'},
                    {"target-directory",     required_argument,     0, 't'},
                    {"verbose",              no_argument,           0, 'v'}
                };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
                c = getopt_long(argc, argv, "hvrt:", long_options, &option_index);

                if (c == -1) break;

        //switch en fonction des options rentrées par l'user
                switch (c) {

                    case 'h': 
                    printf("\n-----------------------------------------------------------\n");
                    printf("Usage: cp [OPTION]... SOURCE DEST\n");
                    printf("       cp [OPTION]... SOURCE... DIRECTORY\n");
                    printf("       cp [OPTION]... -t DIRECTORY SOURCE...\n");
                    printf("Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.\n\n");
                    printf("    -v, --verbose                 explain what is being done\n");
                    printf("    -r, --recursive               copy directories recursively\n");
                    printf("    -t, --target-directory        copy all SOURCE arguments into DIRECTORY\n");
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

                    case 't':
                    options[nbOptions] = c; 
                    nbOptions++;
                    break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
                    default:
                    printf("Try 'fonction --help' for more information.\n");
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

                    files[nbFiles] = concatenateTables(files[nbFiles],argv[i]);


                }
            }
        // if nombre d'arguments invalide
            if (nbFiles == 2)
            {
                copy(files[1],files[2], options, nbOptions);   
            }
            else
            {
                printf("cp : invalid number of arguments\n");
                printf("Try 'cp --help' for more information.\n");
            }
            free(files);
            free(options);


        }
    //** A changer **//
    //SI pas d'arguments => on affiche une erreur
        else
        {
            printf("cp : invalid number of arguments\n");
        }

        return 0;
    }

void copy(char* src, char* dst, char* options, int nbOptions){

    struct stat st1,st2;
    char path[PATH_MAX],path2[PATH_MAX],*srcFile;
    DIR *dirp;
    struct dirent *dptr;
    int fd1,fd2,i;
    int BUFLEN = 65535;
    char buf[BUFLEN];
    struct utimbuf times;

    if(strcmp(options, "v")==0){
        printf("Copie de \"%s\" vers \"%s\"\n",src,dst);
    }
    

    if (lstat(src,&st1)==-1)
    {
        fprintf(stderr,"Impossible d'ouvrir le fichier \"%s\" (%d) %s\n",src,errno,strerror(errno));
        return;
    }
    if (!S_ISDIR(st1.st_mode))
    {
        // On ne copie que les fichiers réguliers
        if ((st1.st_mode & S_IFREG)==S_IFREG)
        {
            fd1=open(src,O_RDONLY);
            if (fd1==-1)
            {
                printf("Impossible d'ouvrir le fichier source \"%s\" (%d: %s)\n",src,errno,strerror(errno));
                return;
            }

            // Si la destination est un répertoire, on crée un nouveau fichier dans ce répertoire
            if ((lstat(dst,&st2)!=-1) && (S_ISDIR(st2.st_mode)))
            {
                // Extraction du nom de fichier à copier
                i=strlen(src);
                while ((i>0) && (src[i]!='/')) i--;
                if (src[i]=='/') srcFile=&src[i+1];
                else srcFile=&src[i];

                if (dst[strlen(dst)-1]=='/') sprintf(path,"%s%s",dst,srcFile);
                else sprintf(path,"%s/%s",dst,srcFile);
            }
            else strcpy(path,dst);

            // Création du nouveau fichier
            fd2=open(path,O_WRONLY | O_CREAT | O_EXCL);
            if (fd2==-1)
            {
                fprintf(stderr,"Erreur d'accès au fichier \"%s\" (%d: %s) -> copie impossible\n",path,errno,strerror(errno));
                close(fd1);
                return;
            }

            // Copie du fichier
            while((i=read(fd1,buf,BUFLEN))!=0)
            {
                if (write(fd2,buf,i)==-1)
                {
                    close(fd1);
                    close(fd2);
                    return;
                }
            }

            close(fd1);

            // Préservation des propriétaires (user/group) -> pas de contrôle d'erreur, ne marche que si root !
            fchown(fd2,st1.st_uid,st1.st_gid);

            // Préservation des droits
            if (fchmod(fd2,st1.st_mode)==-1)
            {
                fprintf(stderr,"Erreur de changement de droits sur \"%s\" (%d: %s)\n",path,errno,strerror(errno));
            }
            close(fd2);

            // Préservation des horodatages
            times.actime=st1.st_atime;
            times.modtime=st1.st_mtime;
            if (utime(path,&times)==-1)
            {
                fprintf(stderr,"Erreur de changement de temps sur \"%s\" (%d: %s)\n",path,errno,strerror(errno));
            }
        }
    }
    else
    {
        // Si la destination n'existe pas, on crée un nouveau répertoire
        if (lstat(dst,&st2)==-1)
        {
            if (mkdir(dst,st1.st_mode)==-1)
            {
                fprintf(stderr,"Erreur de création du répertoire \"%s\" (%d: %s) -> copie impossible\n",dst,errno,strerror(errno));
                return;
            }
            chown(dst,st1.st_uid,st1.st_gid);
        }
        else if (!S_ISDIR(st2.st_mode))
        {
            fprintf(stderr,"La destination \"%s\" existe et n'est pas un répertoire -> copie impossible\n",dst);
            return;
        }

        if((dirp=opendir(src))==NULL)
        {
            fprintf(stderr,"Erreur d'ouverture du répertoire \"%s\" (%d: %s)\n",src,errno,strerror(errno));
            return;
        }

        while((dptr=readdir(dirp)))
        {
            if (!strcmp(dptr->d_name,".") || !strcmp(dptr->d_name,"..")) continue;

            if (src[strlen(src)-1]=='/') sprintf(path,"%s%s",src,dptr->d_name);
            else sprintf(path,"%s/%s",src,dptr->d_name);
            if (dst[strlen(dst)-1]=='/') sprintf(path2,"%s%s",dst,dptr->d_name);
            else sprintf(path2,"%s/%s",dst,dptr->d_name);

            copy(path,path2, options, nbOptions);
        }
        closedir(dirp);
    }
}
