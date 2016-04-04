#include "../include/commands.h"

#include "../include/commands/cd.h"
#include "../include/commands/ls.h"

#define debugState 1

 int initCommands(Command** array){
        // Internal Shell commands are first added
        // char* name, char** parameters, char** options, int nameLength, int* parameterLength, int* optionLength, int (*cmd_ptr)(int, int)
        
        int (*cmd_ptr)(int,char*[]);
        cmd_ptr = &test;

        int (*ls_ptr)(int,char*[]);
        ls_ptr = &ls_lib;

        addCmdToArray(array, 0, "cd", cmd_ptr);
        addCmdToArray(array, 0, "ls", ls_ptr);
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

void printName(ParsedCommand* cmd){
        printf("cmd=\"");
        for(int i=0;i<(*cmd).nameLength;i++){
                printf("%c", (*cmd).name[i]);
        }     
        printf("\"\n");  
}

void printParameters(ParsedCommand* cmd){
        printf("parameters=\"");  
        printf("\"\n");  
}

void printOptions(ParsedCommand* cmd){
        printf("options=\"");  
        printf("\"\n");  
}

int addCmdToArray(Command** array, int index, char* name, int (*cmd_ptr)(int, char*[])){
        array[index] = (Command*) malloc(sizeof(Command));
        strncpy((*array)[index].name, name, NAME_SIZE);
        (*array[index]).cmd_ptr = cmd_ptr;
        return 1;
}
