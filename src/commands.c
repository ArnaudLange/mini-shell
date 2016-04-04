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
    
#include "../include/commands.h"

#include "../include/commands/cd.h"
#include "../include/commands/ls.h"

#include "../include/shell.h"

#define debugState 1

 int initCommands(Command** array){
        // Internal Shell commands are first added
        // char* name, char** parameters, char** options, int nameLength, int* parameterLength, int* optionLength, int (*cmd_ptr)(int, int)
        
        int (*cmd_ptr)(int,char*[]);
        cmd_ptr = &cd_internal;

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
