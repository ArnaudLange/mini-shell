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
    
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <pthread.h>

#include <dirent.h>

#include "../include/shell.h"
#include "../include/process.h"

#include "../include/server.h"

#include "../include/parameters.def"

#define LIB_PATH "lib/"

typedef void (*init)(char name[NAME_SIZE], int (*cmd_ptr)(int, char*[]));
init Init;


void welcomeMessage(){
        printf("Binsh 0.1\n");
        printf("     |__  __  __|\n");
        printf(" .---|  ::  ::  |\n");
        printf("|  __|__;:__;:__|\n");
        printf("| |  |  __  __  |\n");
        printf("| |  |::  ::  ::|\n");
        printf("| |  |::__;:__;:|\n");
        printf("| |  |__  __  __|\n");
        printf(" . `.|  ::  ::  |\n");
        printf("  `..|  ::  ::  |\n");
        printf("      \\ ::  :: /\n");
        printf("       \\;:  ;:/\n");
        printf("        \"\"\"\"\"\"\n");
}

void printPrompt(){
        printf(">");
}

int loadLibraries(Shell* shell){
        DIR* dirp = opendir(LIB_PATH);
        struct dirent* dp;
        void *lib;
        while ((dp = readdir(dirp)) ){
                char *path = malloc(strlen(LIB_PATH)+strlen(dp->d_name)+1);//+1 for the zero-terminator
                //in real code you would check for errors in malloc here
                strcpy(path, LIB_PATH);
                strcat(path, dp->d_name);

                if ((lib = dlopen(path, RTLD_LAZY)) != NULL) {
                        if ((Init = (init) dlsym(lib, "init")) == NULL) {
                                printf("Error loading %s\n", dp->d_name);
                        }
                        else{
                                shell->commands[shell->nbCmd] = (Command*) malloc(sizeof(Command));
                                Command* cmd = shell->commands[shell->nbCmd];
                                Init(cmd->name, cmd->cmd_ptr);
                                shell->nbCmd++;
                                printf("successfully loaded %s at index[%d] with name \'%s\'\n", dp->d_name, shell->nbCmd, cmd->name);
                        }
                }
        }
   (void)closedir(dirp);
}

int main(int argc, char* argv[]){

        char *line=NULL;
        size_t size;
        char *chariot;
        ssize_t read;

        Shell* shell = initShell();
        
        loadLibraries(shell);
        printf("\n");
        testFunction(shell, "cd");
        testFunction(shell, "ls");
        testFunction(shell, "cat");
        testFunction(shell, "echo");
        testFunction(shell, "mv");
        testFunction(shell, "pwd");
        testFunction(shell, "mkdir");

        pthread_t sniffer_thread;
        
        if( pthread_create( &sniffer_thread , NULL ,  start , (void*) 1) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        //pthread_cancel(sniffer_thread);

        welcomeMessage();
        while(1){
                printPrompt();
                // lecture ligne par ligne jusqu'à fin du message entré dans stdin
                while ((read = getline(&line, &size, stdin)) != -1) {                   
                        // suppression des retour chariot
                        if (chariot = strchr(line,'\n')){                                                     
                                chariot = NULL;
                                //le pointeur de \n devient pointeur null
                        }                                                                                       
                        //si la ligne est vide
                        if (!strcmp(line,"")){
                                // on passe a la prochaine   
                                return EXIT_SUCCESS;                                                                                                
                        }
                        else{
                                /*
                                ParsedCommand* c = parseCommand(line);
                                printName(c);
                                printParameters(c);
                                printOptions(c);
                                free(c);
                                execute(line,line);
                                */
                                //test_execute(line,line);
                                //FILE* file_out = fopen("exemple.txt", "a");
                                /*
                                ParsedCommand* c = parseCommand(line);
                                if(findFunction(line, c)){
                                        printf("found function\n");
                                }
                                else{
                                        printf("didn't find function\n");
                                }
                                free(c);
                                */
                                //int fd = open("exemple.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                                test_internal_ls(STDIN_FILENO, STDOUT_FILENO);
                                //test_internal_ls(STDIN_FILENO, fd);
                                //fclose(file_out);
                                /*ParsedCommand* c = malloc(sizeof(ParsedCommand));
                                strncpy(c->name, "cd", NAME_SIZE);
                                printf("res=%d\n", findFunction(shell, c));
                                printf("function=%d\n", c->cmd_ptr);*/
                                   
                                break;  
                        }                                                      
                }
        }
        freeShell(shell); 
        return EXIT_SUCCESS;   
}

