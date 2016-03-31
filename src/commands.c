#include <stdlib.h>
#include "../include/commands.h"

#define debugState 1

 int initCommands(Command** array){
        //Command** ret = (Command**)malloc(100*sizeof(Command));

        // Internal Shell commands are first added
        //ret[0] = allocateCommand();
        return 1;
}

Command* allocateCommand(char* name, char** parameters, char** options, int nameLength, int* parameterLength, int* optionLength, int (*cmd_ptr)(int, int)){
        return (Command*)malloc(sizeof(Command));
}

Command** allocateCommands(int amount){
        return (Command**)malloc(amount*sizeof(struct command));
}

int freeCommands(int nbCmd, Command** commands){
        int i=0;
        Command* curr = NULL;
        if(nbCmd>MAX_COMMANDS){return -1;}
        //printf("nbCmd=%d\n", nbCmd);
        while(i<nbCmd){
                curr = commands[i];
                if(curr!=NULL){free(curr);}
                else{break;}
                i++;
        }
        return 1;
}

Command* parseCommand(char* input){

        State current = S0;

        char c;
        int i=0;
        int parameterIndex=0;   // Used to set the name in the command
        int countParameters=0;

        //Command* ret = allocateCommand();
        //(*ret).nameLength=0;

        // input[i]!=' ' && input[i]!='\0'
        while(input[i]!='\n'){
                c = input[i];
                switch(current){
                    case S0:
                          if(debugState){printf(" STATE S0");}
                    break;
                    case S1:
                          if(debugState){printf(" STATE S1");}
                    break;
            }
            if(debugState){printf("\n");}
            i++;
        }
        //(*ret).nameLength = parameterIndex;
        return NULL;
}

void printName(Command* cmd){
        printf("cmd=\"");
        for(int i=0;i<(*cmd).nameLength;i++){
                printf("%c", (*cmd).name[i]);
        }     
        printf("\"\n");  
}

void printParameters(Command* cmd){
        printf("parameters=\"");  
        printf("\"\n");  
}

void printOptions(Command* cmd){
        printf("options=\"");  
        printf("\"\n");  
}