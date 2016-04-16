/*
    This file is part of Binsh.

    Binsh is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Binsh is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/
    
#include "../include/commands.h"
#include "../include/commands/cd.h"
#include "../include/utils.h"
#include "../include/shell.h"
#include "../include/parameters.def"

#define debugState 0


bool isLetter(char c){
      if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            return true;
      }
      return false;
}

int initCommands(Command* array[MAXCMD]){
        // Internal Shell commands are first added
        // char* name, char** parameters, char** options, int nameLength, int* parameterLength, int* optionLength, int (*cmd_ptr)(int, int)
        addCmdToArray(array, 0, "cd", &cd_internal);
        return 1;
}

int freeCommands(int nbCmd, Command** commands){
        int i=0;
        Command* curr = NULL;
        if(nbCmd>MAXCMD){return -1;}
        while(i<nbCmd){
                curr = commands[i];
                if(curr!=NULL){free(curr);}
                else{break;}
                i++;
        }
        return 1;
}

ParsedCommand* parseCommand(char* input){

        //etat initial
        State current = S0;
        // le caractère lu
        char c;
        // compteur pour chaque caractère lu
        int i=0;
        // compteur du ième caractère à ajouter dans nom/options/arguments 
        int cpt = 0;

        bool ajout=false;

        ParsedCommand* pc;
        pc = (ParsedCommand*)malloc(sizeof(ParsedCommand));
        pc->argv[0] = malloc(NAME_SIZE*sizeof(char));
        //strcpy(pc->argv[0], pc->name);
        pc->argv[0][0]='\0';
        pc->cptarg = 1;
        //Command* ret = allocateCommand();
        //(*ret).nameLength=0;
        // input[i]!=' ' && input[i]!='\0'
        while(input[i]!='\n'){
                c = input[i];
                switch(current){
                    // cas de départ 
                    case S0:
                        if(debugState){printf(" STATE S0\n");}
                        // on trouve le String de la fonction
                        if (isLetter(c) || c == '/' || c == '.'){
                        pc->name[cpt] = c;
                        current = Sfunction;
                        }
                        // un espace
                        else if ( c ==' '){
                            current = S0;	
                        } // cas incorrect
                        else {
                            return NULL;
                        }
                    break;
                    // cas où on a déjà trouvé la commande
                    case S1 : 
                    if(debugState){printf(" STATE S1\n");}
                        // on trouve le String de la fonction
                        if (isLetter(c) || c == '-' || c == '/' || c == '.' || c == '~'){
                            pc->argv[pc->cptarg] = (char*)malloc(NAME_SIZE*sizeof(char));
                            pc->argv[pc->cptarg][cpt] = c;
                            ajout=true;
                            //pc->cptarg =pc->cptarg+1;
                            current = Sargs;
                        }
                        // un espace
                        else if ( c ==' '){
                            current = S1;
                        } 
                        else {
                            return NULL;
                        }
                    break;

                    case Sfunction:
                        if(debugState){printf(" STATE Sfunction\n");}
                        if ((isLetter(c) || c == '/') && c != ' ' & c !='-'){
                        cpt ++;
                        pc->nameLength = cpt;
                        pc->name[cpt] = c;
                        current = Sfunction;
                        }
                        // un espace, on a la commande
                        else if (c ==' '){
                            pc->nameLength = cpt;
                            cpt = 0;
                            current = S1;
                        } // cas incorrect
                        else {
                            return NULL;
                        }
                    break;
                    case Sargs :
                    if(debugState){printf(" STATE Sargs\n");}	
                        if (isLetter(c) && c != ' '){
                        cpt ++;
                        pc->argv[pc->cptarg][cpt] = c;
                        current = Sargs;
                        }
                        // un espace
                        else if ( c ==' '){
                            pc->argc[pc->cptarg] = cpt;
                            pc->argv[pc->cptarg][cpt+1] = '\0';
                            cpt = 0;
                            pc->cptarg =pc->cptarg+1;
                            current = S1;
                        } // cas incorrect
                        else {
                            return NULL;
                        }
                        pc->argc[pc->cptarg] = cpt;
                    break;
            if(debugState){printf("\n");}
        }
        i++;
        //(*ret).nameLength = parameterIndex;
        }
        if(ajout){
                pc->cptarg =pc->cptarg+1;
                pc->argv[pc->cptarg-1][cpt+1] = '\0';
        }
        pc->argv[pc->cptarg]=NULL;
        pc->name[pc->nameLength+1]='\0';
        //printf("name=%s\n", pc->name);
        //printf("argv[1][0]=%c\n", pc->argv[1][0]);
        //printf("argv[1][1]=%c\n", pc->argv[1][1]);

        //printf("argv[1][2]=%c\n", pc->argv[1][2]);

        return pc;

    }

void printName(ParsedCommand* pc){
    printf("cmd = ");
    printf("%s\n", pc->name);
    for (int i = 0;i <= NAME_SIZE;i++){
        printf("%c", pc->name[i]);
    }
    printf("\n");
}


void printParameters(ParsedCommand* pc){
        printf("parameters = ");  
        for (int i =0; i <= pc->cptarg;i++){
            for (int j = 0; j < pc->argc[i]; j++){
                printf("%c", pc->argv[i][j]);
            }
            printf(" ");
        }
        printf("\n");
}


int addCmdToArray(Command** array, int index, char* name, int (*cmd_ptr)(int, char*[])){
        array[index] = (Command*) malloc(sizeof(Command));
        strncpy((*array)[index].name, name, NAME_SIZE);
        (*array[index]).cmd_ptr = cmd_ptr;
        return 1;
}
