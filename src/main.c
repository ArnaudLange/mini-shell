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
#include "../include/typedef.h"

#define LIB_PATH "lib/"

typedef cmdPtr (*init)(char name[NAME_SIZE]);
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
                                shell->library_commands[shell->nbLibraryCmd] = (Command*) malloc(sizeof(Command));
                                Command* cmd = shell->library_commands[shell->nbLibraryCmd];
                                cmd->cmd_ptr = Init(cmd->name);
                                shell->nbLibraryCmd++;
                                printf("successfully loaded %s at index[%d] with name \'%s\'\n", dp->d_name, shell->nbLibraryCmd, cmd->name);
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
        checkFunction(shell, "cd");
        checkFunction(shell, "ls");
        checkFunction(shell, "cat");
        checkFunction(shell, "echo");
        checkFunction(shell, "mv");
        checkFunction(shell, "pwd");
        checkFunction(shell, "mkdir");
    	checkFunction(shell, "du");
    	checkFunction(shell, "cp");
    	checkFunction(shell, "chmod");
        checkFunction(shell, "chown");
        checkFunction(shell, "chgrp");
        checkFunction(shell, "more");
	checkFunction(shell, "ps");
        checkFunction(shell, "top");

        /*
        testFunction(shell, "cd", argc, argv);
        testFunction(shell, "ls", argc, argv);
        testFunction(shell, "cat", argc, argv);
        testFunction(shell, "echo", argc, argv);
        testFunction(shell, "mv", argc, argv);
        testFunction(shell, "pwd", argc, argv);
        testFunction(shell, "mkdir", argc, argv);
        testFunction(shell, "du", argc, argv);
        testFunction(shell, "cp", argc, argv);
        testFunction(shell, "chmod", argc, argv);
        testFunction(shell, "chown", argc, argv);
        testFunction(shell, "chgrp", argc, argv);
        */


        pthread_t sniffer_thread;
        if( pthread_create( &sniffer_thread , NULL ,  start , (void*) shell) < 0)
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
                        //si la ligne est vide
                        if (!strcmp(line,"")){
                                // on passe a la prochaine   
                                return EXIT_SUCCESS;                                                                                                
                        }
                        else{
                                /* on créer un tableau de pointeur vers des ParsedCommand 
                                pour pouvoir en stocker plusieurs et ainsi permettre la redirection */
                                ParsedCommand* tab = NULL;
                                tab = (ParsedCommand*)malloc(sizeof(ParsedCommand));
                                ParsedCommand* c = parseCommand(line);
                        



                                /*if ( c->typeredirec == tuyau){
                                            printf("mourg\n");
                                        }   
                                ParsedCommand* d = parseCommand(&line[c->cptglobal]);
                                if ( d->typeredirec == tuyau){
                                            printf("mourg\n");
                                        }
                                    printName(c);
                                    printName(d);
                                    */
                                // si on a une première commande
                                if (c!=NULL){
                                    int i = 0;
                                    tab[0] = *c;
                                    //printf("%i\n", c->fin);
                                    // la fin n'est pas atteinte -> il y a eu une redirection, on ajoute la nouvelle commande au tableau
                                    while(tab[i].typeredirec != vide ){
                                        i++;
                                        tab = realloc(tab, (i+1)*sizeof(ParsedCommand));
                                        //printf("%i\n", (tab[i-1]).cptglobal);
                                        tab[i] = *parseCommand(&line[(tab[i-1]).cptglobal]);
                                        //tab[i] = *c;
                                        //tab[i] = parseCommand(line[tab[i-1]->cptglobal]);
                                    }

                                    // on parcourt le tableau de parsedcommand
                                    for (int z = 0; z<=i; z++){
                                        // si on a un pipe
                                        printf("%i\n", i);
                                        executeCommand(STDIN_FILENO,STDOUT_FILENO,shell,&tab[z]);
                                        if (tab[z].typeredirec == tuyau){
                        
                                        }// si on a <<
                                        else if (tab[z].typeredirec == lefta){

                                        }//si on a <
                                        else if (tab[z].typeredirec == leftw){

                                        }//si on a >>
                                        else if (tab[z].typeredirec == righta){

                                        }//si on a >
                                        else if (tab[z].typeredirec == rightw){

                                        }// si on a <<
                                        else if (tab[z].typeredirec == lefta){

                                        }//si on a &
                                        else if (tab[z].typeredirec == detach){

                                        }//si on a &&
                                        else if (tab[z].typeredirec == andd){
                                            printf("bonjour");
                                            if (executeCommand(STDIN_FILENO,STDOUT_FILENO,shell,&tab[z]) == 1){
                                                printf("lalala\n");
                                                executeCommand(STDIN_FILENO,STDOUT_FILENO,shell,&tab[z+1]);
                                            }

                                        }//si on a ||
                                        else if (tab[z].typeredirec == orr){
                                        }
                                    }
                                    
                                    
                                    //ParsedCommand* d = parseCommand(&line[c->cptglobal]);
                                    //tab[1] = *d;
                                    
                                    //printName(&tab[0]);
                                    //printParameters(&tab[0]);
                                    //printName(&tab[1]);
                                    //printParameters(&tab[1]);
                                    //printName(&tab[2]);

                                    //executeCommand(STDIN_FILENO,STDOUT_FILENO,shell,c);
                                    free(tab);
                                    //execute(line,line);
                                    
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
                                    //test_internal_ls(STDIN_FILENO, STDOUT_FILENO);
                                    //test_internal_ls(STDIN_FILENO, fd);
                                    //fclose(file_out);
                                    /*ParsedCommand* c = malloc(sizeof(ParsedCommand));
                                    strncpy(c->name, "cd", NAME_SIZE);
                                    printf("res=%d\n", findFunction(shell, c));
                                    printf("function=%d\n", c->cmd_ptr);*/
                                }
                                break;  
                        }                                                  
                }
        }
        freeShell(shell); 
        return EXIT_SUCCESS;   
}

