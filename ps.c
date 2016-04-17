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
#include "../../include/commands/ps.h"


void ps(char *option, char* param){

    printf("PID\tTTY\t   TIME\t\t CMD\n");
    char character;
    int p=0;
    long int hr,min,sc,t;

    FILE *fichier=NULL;

    //dossier ou se trouvent tous les process
    char *directory = "/proc";

    //on va ouvrir le dossier proc, puis les sous dossier a l'interieur
    DIR *repertoire;
    DIR *sous_repertoire;

    //CMD
    char *nomCommande=NULL;
    nomCommande=calloc(1,sizeof(char));
    if(nomCommande==NULL){
        perror("calloc");
        exit(1);
    }
    //TTY
    char *TTY=NULL;
    TTY=calloc(1,sizeof(char));
    if(TTY==NULL){
        perror("calloc");
        exit(1);
    }
    //nom
    char *nom=NULL;
    nom=calloc(1,sizeof(char));
    if(nom==NULL){
        perror("calloc");
        exit(1);
    }
    //Uptime
    char *uptime=NULL;
    uptime=calloc(1,sizeof(char));
    if(uptime==NULL){
        perror("calloc");
        exit(1);
    }

    //stime
    char *stime=NULL;
    stime=calloc(1,sizeof(char));
    if(stime==NULL){
        perror("calloc");
        exit(1);
    }

    //struct utiliser pour lire le dossier
    struct dirent *flux;

    //on initialise namefile qui contiendra le nom du fichier lu
    char *nameFile = NULL;
    nameFile = calloc(1,sizeof(char));
    if(nameFile==NULL){
        perror("Calloc");
        exit(1);
    }

    //on initialise namefile qui contiendra le nom du fichier lu
    char *sous_nameFile = NULL;
    sous_nameFile = calloc(1,sizeof(char));
    if(sous_nameFile==NULL){
        perror("Calloc");
        exit(1);
    }

    //ouverture du dossier
    if ((repertoire = opendir(directory)) == NULL){
        perror(directory);
        exit(1);
    }

    //on parcourt le dossier a present pour trouver tous les sous dossiers qui nous interessent
    while((flux = readdir(repertoire))){
        if (strlen(nameFile)>1){
            free(nameFile);
            nameFile = NULL;
            nameFile = calloc(1,sizeof(char));
            if(nameFile==NULL){
                perror("Calloc");
                exit(1);
            }
        }

        if(atoi(flux->d_name)!=0){
            nameFile=concatenateTables(nameFile,directory);
            nameFile=concatenateTables(nameFile,"/");
            nameFile=concatenateTables(nameFile,flux->d_name);

            if ((sous_repertoire = opendir(nameFile)) == NULL){
                perror(nameFile);
                exit(1);
            }
            
            if (strlen(sous_nameFile)>1){
                free(sous_nameFile);
                sous_nameFile = NULL;
                sous_nameFile = calloc(1,sizeof(char));
                if(sous_nameFile==NULL){
                    perror("Calloc");
                    exit(1);
                }
            }
            
                


                // RECUPERATION DONNEES DANS LE FICHIER stat (le total_time d'activite et le tty)
                free(sous_nameFile);
                sous_nameFile = NULL;
                sous_nameFile = calloc(1,sizeof(char));
                if(sous_nameFile==NULL){
                    perror("Calloc");
                    exit(1);
                }
                sous_nameFile=concatenateTables(sous_nameFile,nameFile);
                sous_nameFile=concatenateTables(sous_nameFile,"/");
                sous_nameFile=concatenateTables(sous_nameFile,"stat");

                //On ouvre stat que l'on va parser pour recuperer ce qu'il nous manque (cf uptime & tty)
                fichier = fopen(sous_nameFile,"r");
                if(fichier == NULL){
                    perror(sous_nameFile);
                    exit(1);
                }
                while((character=fgetc(fichier)) != EOF){
                    if (character== ' '){ //on incremente une variables pour savoir a quel espace on est rendu
                        p++;
                    }
                    if (p==1 && character!='(' && character != ')'){
                        nom=realloc(nom,(strlen(nom)+1)*sizeof(char));
                        nom[strlen(nom)]=character;
                        nom[strlen(nom)+1]='\0';
                    }
                    if (p == 6){
                        TTY=realloc(TTY,(strlen(TTY)+1)*sizeof(char));
                        TTY[strlen(TTY)]=character;
                        TTY[strlen(TTY)+1]='\0';
                    }
                    if (p==13){
                        uptime=realloc(uptime,(strlen(uptime)+1)*sizeof(char));
                        uptime[strlen(uptime)]=character;
                        uptime[strlen(uptime)+1]='\0';
                    }
                    if (p==14){
                        stime=realloc(stime,(strlen(stime)+1)*sizeof(char));
                        stime[strlen(stime)]=character;
                        stime[strlen(stime)+1]='\0';
                    }
                }

                // /!\ a noter
                // uptime n'est pas affiche comme sur le "vrai" ps car je n'ai trouve le time que en int, et pas en format adapté comme m_time
                // meme chose pour tty, je peux determiner quand il est '?' mais sinon il est sous format int

                long int hz = sysconf(_SC_CLK_TCK);
                long int total_time = (atoi(stime)+atoi(uptime))/hz;

                hr=total_time/3600;
                t=total_time%3600;
                min=t/60;
                sc=min%60;

                
                //Si option e, on affiche tout
                if (!strcmp(option,"e")){

                    printf("%s\t",flux->d_name);
                    if(strlen(TTY)==2){
                        printf(" ?\t");
                    }
                    else{
                        printf("%s\t",TTY);
                    }
                    printf("%2ld:%2ld:%2ld\t",hr,min,sc);
                    printf("%s",nom);
                    printf("\n");
                }
                //sinon on affiche que les options pour lesquelles le pid correspond a getpid() et getppid()
                else{
                    //On recupere le pid et le ppid
                    char pid[15],ppid[15];
                    //On les passe en char
                    sprintf(pid, "%d", getpid());
                    sprintf(ppid, "%d", getppid());
                    //puis si le pid qui est passé en revu actuellement correspond a l'un ou l'autr
                    //on affiche
                    if (!strcmp(flux->d_name,pid) || !strcmp(flux->d_name,ppid)){
                        printf("%s\t",flux->d_name);
                        if(strlen(TTY)==2){
                            printf("?\t");
                        }
                        else{
                            printf("'%s'\t",TTY);
                        }
                        printf("%2ld:%2ld:%2ld\t",hr,min,sc);
                        printf("%s",nom);
                        printf("\n");
                    }
                }
                p=0;
                free(TTY);
                TTY=calloc(1,sizeof(char));
                free(uptime);
                uptime=calloc(1,sizeof(char));
                free(stime);
                stime=calloc(1,sizeof(char));
                free(nom);
                nom=calloc(1,sizeof(char));
            // pid (filename) state ppid pgrp session tty_nr
        }
    }
    free(nomCommande);
    free(TTY);
    free(uptime);
}


int ps_lib(int argc, char *argv[]){

    // -----------------------------------
    int c;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"help",     no_argument ,       0, 'h'},
            {"e",     no_argument,       0, 'e'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "eh", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: ps [OPTION]\n");
           printf("\n  -e             \tall processes.\n");
           printf("\n-----------------------------------------------------------\n");
           exit(0);
           break;
         //option e : qui fait ps pour tous les processus
         case 'e':
            ps("e","");
            break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'fonction --help' for more information.\n");
            exit(1);
        }
    
    
        }
    }
    else {
        ps(" ","");
    }
    return 0;
}
