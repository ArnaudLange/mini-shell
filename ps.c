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

#include "ps.h" //à virer une fois les tests effectués

void ps(char *option, char* param){

    // BALEK
    /*
    if (option == NULL){
        printf("  PID TTY          TIME CMD\n");
        printf("%d\n",getpid());
        printf("%d                   Bash\n",getppid());

    }
    else if (strcmp(option,"u")){
        printf("  PID TTY          TIME CMD\n");
    }
    else if (strcmp(option,"C")){
        printf("  PID TTY          TIME CMD\n");
    }
    */
    char character;
    int i,j=0;

    FILE *fichier=NULL;

    //dossier ou se trouvent tous les process
    char *directory = "/proc";

    //on va ouvrir le dossier proc, puis les sous dossier a l'interieur
    DIR *repertoire;
    DIR *sous_repertoire;

    char nomCommande[15];
    for(i=0;i<15;i++){
        nomCommande[i]=' ';
    }
    nomCommande[15]='\0';

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
            printf("%s  ",flux->d_name);
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
            sous_nameFile=concatenateTables(sous_nameFile,"cmdline");

            fichier = fopen(sous_nameFile,"r");
            if(fichier == NULL){
                perror(sous_nameFile);
                exit(1);
            }

            while((character=fgetc(fichier)) != EOF){
                //printf("%c",character);
                if(character == '/' || character == 10){
                    for(i=0;i<15;i++){
                        nomCommande[i]=' ';
                        j=0;
                    }
                }
                else{
                    nomCommande[j]=character;
                    j++;
                }
            }
            printf("%s\n",nomCommande);
            //printf("\n");

            /*
            while((sous_flux = readdir(sous_repertoire))){
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
                sous_nameFile=concatenateTables(sous_nameFile,sous_flux->d_name);

                printf("%s\n",sous_nameFile);
            }*/
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
            {"help",     no_argument ,       0, 'h'},
            {"u",     required_argument,       0, 'u'},
            {"C",     required_argument,       0, 'C'},
            {0, 0, 0, 0}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "u:C:h", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: ps [OPTION]\n\n");
           printf("\n  -u [USER]             \tfilter processes by user.\n");
            printf("\n  -C [COMMAND]              \tfilter processes by its name.\n");
           printf("\n-----------------------------------------------------------\n");
           exit(0);
           break;

         case 'u':
            optind--;
            for( ;optind < argc && *argv[optind] != '-'; optind++){
                  //On appelle ps avec l'option u et chaque argument
                  ps("u",argv[optind]);        
            }
            break;

         case 'C':
            optind--;
            for( ;optind < argc && *argv[optind] != '-'; optind++){
                  //On appelle ps avec l'option C et chaque argument
                  ps("C",argv[optind]);       
            }
            break;


        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'fonction --help' for more information.\n");
            exit(1);
        }
    
    
        }
    }
    else {
        ps(NULL,"");
    }
    return 0;
}
