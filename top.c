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

#include "top.h" //à virer une fois les tests effectués
 

void top(){

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int ligneScreen = w.ws_row;

    int sleeping=0,stopped=0,zombie=0,running=0,nb=0;

    while(1){    

    int nbLigne=0;

    struct passwd * user;
    struct processus *tableProcess=NULL;
    tableProcess=calloc(1,sizeof(struct processus));
    if(tableProcess==NULL){
        perror("Calloc");
        exit(1);
    }

    int emplacementTable=0;

    int p=0,t=0,tp=0;
    

    long int hr,min,sc, minBoot,hourBoot;

    char character;

    FILE *fichier=NULL;

    time_t rawtime;
    time(&rawtime);
    struct tm *tm_struct = localtime(&rawtime);

    hr = tm_struct->tm_hour;
    min = tm_struct->tm_min;
    sc = tm_struct->tm_sec;

    //getting uptime
    struct sysinfo info;
    sysinfo(&info);
    minBoot=info.uptime/60;
    if(minBoot>60){
        hourBoot=minBoot/60;
    }
    minBoot=minBoot-60*hourBoot;

    char perc='%';
    printf("top - %ld:%ld:%ld up %ldh%ldmin,\n", hr,min,sc,hourBoot,minBoot);
    printf("Tasks : %d total, %d running, %d sleeping, %d stopped, %d zombie\n",nb,running,sleeping,stopped,zombie);
    printf("\nPID\tUSER\tPR\tNI\tVIRT\tRES\tSHR\tS\t%cCPU\t%cMEM\tTIME+\tCOMMAND\n",perc,perc);
    nbLigne+=5;
    
    sleeping=0,stopped=0,zombie=0,running=0,nb=0;

    //dossier ou se trouvent tous les process
    char *directory = "/proc";

    //on va ouvrir le dossier proc, puis les sous dossier a l'interieur
    DIR *repertoire;
    DIR *sous_repertoire;


    //struct utiliser pour lire le dossier
    struct dirent *flux;

    //command
    char *command=NULL;
    command=calloc(1,sizeof(char));
    if(command==NULL){
        perror("calloc");
        exit(1);
    }


    char *uptime=NULL;
    uptime=calloc(1,sizeof(char));
    if(uptime==NULL){
        perror("calloc");
        exit(1);
    }
    char *utime=NULL;
    utime=calloc(1,sizeof(char));
    if(utime==NULL){
        perror("calloc");
        exit(1);
    }
    char *stime=NULL;
    stime=calloc(1,sizeof(char));
    if(stime==NULL){
        perror("calloc");
        exit(1);
    }
    char *cutime=NULL;
    cutime=calloc(1,sizeof(char));
    if(cutime==NULL){
        perror("calloc");
        exit(1);
    }
    char *cstime=NULL;
    cstime=calloc(1,sizeof(char));
    if(cstime==NULL){
        perror("calloc");
        exit(1);
    }
    char *starttime=NULL;
    starttime=calloc(1,sizeof(char));
    if(starttime==NULL){
        perror("calloc");
        exit(1);
    }

    //on initialise namefile qui contiendra le nom du fichier lu
    char *nameFile = NULL;
    nameFile = calloc(1,sizeof(char));
    if(nameFile==NULL){
        perror("Calloc");
        exit(1);
    }
    //strUid
    char *strUid=NULL;
    strUid=calloc(1,sizeof(char));
    if(strUid==NULL){
        perror("calloc");
        exit(1);
    }

    //on initialise namefile qui contiendra le nom du fichier lu
    char *sous_nameFile = NULL;
    sous_nameFile = calloc(1,sizeof(char));
    if(sous_nameFile==NULL){
        perror("Calloc");
        exit(1);
    }


    float flUptime;
    //ouverture du dossier
    if ((repertoire = opendir(directory)) == NULL){
        perror(directory);
        exit(1);
    }

    sous_nameFile=concatenateTables(sous_nameFile,directory);
    sous_nameFile=concatenateTables(sous_nameFile,"/");
    sous_nameFile=concatenateTables(sous_nameFile,"uptime");

    //On ouvre stat que l'on va parser pour recuperer ce qu'il nous manque (cf uptime & tty)
    fichier = fopen(sous_nameFile,"r");
    if(fichier == NULL){
        perror(sous_nameFile);
        exit(1);
    }

    while((character=fgetc(fichier)) != EOF && character!=' '){
        uptime=realloc(uptime,(strlen(uptime)+1)*sizeof(char));
        uptime[strlen(uptime)]=character;
        uptime[strlen(uptime)+1]='\0';
        
    }
    flUptime=atoi(uptime);
    free(uptime);
    uptime=calloc(1,sizeof(char));
    fclose(fichier);

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

        Process currentProcess;
        currentProcess.pid=0;
        currentProcess.userName=NULL;
        currentProcess.userName=calloc(1,sizeof(char));
        if(currentProcess.userName==NULL){
            perror("calloc");
            exit(1);
        }
        currentProcess.name=NULL;
        currentProcess.name=calloc(1,sizeof(char));
        if(currentProcess.name==NULL){
            perror("calloc");
            exit(1);
        }

        //A present on va chercher ce qui nous interesse dans uptime
        if (strlen(sous_nameFile)>1){
            free(sous_nameFile);
            sous_nameFile = NULL;
            sous_nameFile = calloc(1,sizeof(char));
            if(sous_nameFile==NULL){
                perror("Calloc");
                exit(1);
            }
        }


        if(atoi(flux->d_name)!=0){
            nb++;
            //on recupere le pid ici
            currentProcess.pid = atoi(flux->d_name);


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

            //On trouve les informations qui nous interessent dans stat
            if (strlen(sous_nameFile)>1){
                free(sous_nameFile);
                sous_nameFile = NULL;
                sous_nameFile = calloc(1,sizeof(char));
                if(sous_nameFile==NULL){
                    perror("Calloc");
                    exit(1);
                }
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
                    command=realloc(command,(strlen(command)+1)*sizeof(char));
                    command[strlen(command)]=character;
                    command[strlen(command)+1]='\0';
                }
                if (p==2){
                    if(character=='S'){
                        sleeping++;
                    }
                    else if(character=='R'){
                        running++;
                    }
                    else if(character=='Z'){
                        zombie++;
                    }
                    else if(character=='T'){
                        stopped++;
                    }
                }
                if (p==13){
                    utime=realloc(utime,(strlen(utime)+1)*sizeof(char));
                    utime[strlen(utime)]=character;
                    utime[strlen(utime)+1]='\0';
                }
                if (p==14){
                    stime=realloc(stime,(strlen(stime)+1)*sizeof(char));
                    stime[strlen(stime)]=character;
                    stime[strlen(stime)+1]='\0';
                }
                if (p==15){
                    cutime=realloc(cutime,(strlen(cutime)+1)*sizeof(char));
                    cutime[strlen(cutime)]=character;
                    cutime[strlen(cutime)+1]='\0';
                }
                if (p==16){
                    cstime=realloc(cstime,(strlen(cstime)+1)*sizeof(char));
                    cstime[strlen(cstime)]=character;
                    cstime[strlen(cstime)+1]='\0';
                }
                if (p==21){
                    starttime=realloc(starttime,(strlen(starttime)+1)*sizeof(char));
                    starttime[strlen(starttime)]=character;
                    starttime[strlen(starttime)+1]='\0';
                }
            }
            p=0;
            fclose(fichier);
            //A present on va chercher ce qui nous interesse dans status
            if (strlen(sous_nameFile)>1){
                free(sous_nameFile);
                sous_nameFile = NULL;
                sous_nameFile = calloc(1,sizeof(char));
                if(sous_nameFile==NULL){
                    perror("Calloc");
                    exit(1);
                }
            }
            
            sous_nameFile=concatenateTables(sous_nameFile,nameFile);
            sous_nameFile=concatenateTables(sous_nameFile,"/");
            sous_nameFile=concatenateTables(sous_nameFile,"status");

            //On ouvre stat que l'on va parser pour recuperer ce qu'il nous manque (cf uptime & tty)
            fichier = fopen(sous_nameFile,"r");
            if(fichier == NULL){
                perror(sous_nameFile);
                exit(1);
            }
            while((character=fgetc(fichier)) != EOF){
                if (character== 10){ //on incremente une variables pour savoir a quel espace on est rendu
                    t++;
                }
                if (t==7){//quand on est a uid
                    tp++;
                    if(tp>6 && character!=' ' && strcmp(strUid,"0") && strlen(strUid)<4){
                        strUid=realloc(strUid,(strlen(strUid)+1)*sizeof(char));
                        strUid[strlen(strUid)]=character;
                        strUid[strlen(strUid)+1]='\0';
                    }
                }
            }
            fclose(fichier);

            if (! (user = getpwuid(atoi(strUid)) )){
                currentProcess.userName = "?";
            } else {
                currentProcess.userName = concatenateTables(currentProcess.userName,user->pw_name);
            }
            currentProcess.name = concatenateTables(currentProcess.name,command);

            float cpu_usage=0;
            long int hertz = sysconf(_SC_CLK_TCK);
            long int total_time = atoi(utime)+atoi(stime)+atoi(cutime)+atoi(cstime);
            float seconds = flUptime - (atoi(starttime) / hertz);
            if(seconds > 0){
                cpu_usage = 100 * ((total_time / hertz) / seconds);
            }
            currentProcess.percCPU=cpu_usage;

            //determination pourcentage d'utilisation du CPU

            //t sert a comptabiliser le nombre de lignes
            t=0;
            tp=0;
            
            

            tableProcess[emplacementTable]=currentProcess;
            emplacementTable++;
            tableProcess=realloc(tableProcess,(emplacementTable+1)*sizeof(struct processus));
            
            free(command);
            command=calloc(1,sizeof(char));
            free(utime);
            utime=calloc(1,sizeof(char));
            free(stime);
            stime=calloc(1,sizeof(char));
            free(cutime);
            cutime=calloc(1,sizeof(char));
            free(cstime);
            cstime=calloc(1,sizeof(char));
            free(starttime);
            starttime=calloc(1,sizeof(char));
            free(strUid);
            strUid=calloc(1,sizeof(char));

            closedir(sous_repertoire);
        }

    }

    closedir(repertoire);
    
    int g;
    for(g=0;g<emplacementTable;g++){
        if (ligneScreen>nbLigne){
            printf("%d\t",tableProcess[g].pid);
            printf("%s",tableProcess[g].userName);
            printf("\t\t\t\t\t\t\t%ld",tableProcess[g].percCPU);
            printf("\t\t\t%s",tableProcess[g].name);
            printf("\n");
            nbLigne++;
        }
    }


    //pour repeter l'execution chaque seconde
    sleep(1);
    int k;
    for(k=0; k<ligneScreen;k++){
        printf("\b");
    }
    }
}


int main(int argc, char *argv[]){

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
            {"help",     no_argument ,       0, 'h'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "h", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: top\n");
           printf("\nDisplay Linux processes.\n");
           printf("\n-----------------------------------------------------------\n");
           exit(0);
           break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'fonction --help' for more information.\n");
            exit(1);
        }
    
    
        }
    }
    else {
        top();
    }
    return 0;
}
