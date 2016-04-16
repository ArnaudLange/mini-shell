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
    

#define READ_END 0
#define WRITE_END 1

#include "../include/shell.h"

Shell* initShell(){
        Shell* shell = malloc(sizeof(Shell));
        (*shell).nbCmd = initCommands(shell->commands);
        return shell;
}

void freeShell(Shell* shell){
        int res = freeCommands((*shell).nbCmd, (*shell).commands);
        free(shell);
}

int findFunction(Shell* shell, ParsedCommand* command){
        int i=0;
        //printf("%d\n",shell->nbCmd);
        while(i<shell->nbCmd){
                //printf("%s\n", (shell->commands)[i]->name);
                //printf("%s\n", (*command).name);
                if(strcmp((shell->commands)[i]->name,(*command).name) == 0){
                        (*command).cmd_ptr = (shell->commands)[i]->cmd_ptr;
                        return 1;
                }    
                i++;
        }
        (*command).cmd_ptr = NULL;
        return 0;
}

int checkFunction(Shell* shell, char* name){
        int i=0;
        while(i<shell->nbCmd){
                if(strcmp((shell->commands)[i]->name, name) == 0){
                        printf("%s est reconnue\n", name);
                        return 1;
                }    
                i++;
        }
        printf("%s introuvable\n", name);
        return 0;
}

int testFunction(Shell* shell, char* name, int argc, char* argv[]){
        int i=0;
        while(i<shell->nbCmd){
                if(strcmp((shell->commands)[i]->name, name) == 0){
                        (shell->commands)[i]->cmd_ptr(argc, argv);
                        return 1;
                }    
                i++;
        }
        printf("%s introuvable\n", name);
        return 0;
}

int executeCommand(int fd_in, int fd_out, Shell* shell, ParsedCommand* cmd){
        if(findFunction(shell, cmd)){
                return executeInternalCommand(fd_in, fd_out, cmd);
        }
        else{
                // If command doesn't exist internally or as a library, we start it from PATH
                return executeExternalCommand(fd_in, fd_out, cmd);
        }
}

int executeInternalCommand(int fd_in, int fd_out, ParsedCommand* cmd){
        printf("internal\n");
        pid_t pid;
        // File descriptor du Pipe
           // pipefd[0] ---> Entrée (standard, fichier, ...)
           // pipefd[1] ---> Sortie (standard, fichier, ...)
           int pipefd[2];
           // pid utilisé pour le processus forké
           pid_t cpid;
           // Crée un Pipe, on spécifie le flag en deuxième paramètre
           if (pipe(pipefd) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }
           if (cpid == 0) {
               // Ici on est dans le fils
                pipefd[READ_END] = fd_in;
                pipefd[WRITE_END] = fd_out;

                dup2(pipefd[READ_END], STDIN_FILENO);
                dup2(pipefd[WRITE_END], STDOUT_FILENO);
                //printf("argSize=%d\n", *(cmd->cptarg));
                //char* test[10];
                //test[0] = malloc(10*sizeof(char));
                //test[1] = malloc(10*sizeof(char));

                //strcpy(test[1], "-h");

                cmd->cmd_ptr(cmd->cptarg, cmd->argv);
                
                //cmd->cmd_ptr(2, test);

                close(pipefd[READ_END]);
                _exit(EXIT_SUCCESS);
        }
        else{
                // Ici on est dans le parent
                wait(NULL);
                close(pipefd[WRITE_END]);
                //redirectFlow(pipefd[READ_END], STDOUT_FILENO);
                return pipefd[WRITE_END];
        }
}

int executeExternalCommand(int fd_in, int fd_out, ParsedCommand* cmd){
        printf("external\n");
        pid_t pid;
        // File descriptor du Pipe
           // pipefd[0] ---> Entrée (standard, fichier, ...)
           // pipefd[1] ---> Sortie (standard, fichier, ...)
           int pipefd[2];
           // pid utilisé pour le processus forké
           pid_t cpid;
           // Crée un Pipe, on spécifie le flag en deuxième paramètre
           if (pipe(pipefd) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }
           if (cpid == 0) {
               // Ici on est dans le fils
                // La programme lira maintenant dans le file descriptor
                dup2(pipefd[READ_END], STDIN_FILENO);
                // Le programme écrira maintenant dans le file descriptor
                dup2(pipefd[WRITE_END], STDOUT_FILENO);
                //execlp(commande,argv,NULL);
                //execlp(cmd->name, cmd->name, (char *)NULL);
                printf("name=%s\n", cmd->name);
                execv(cmd->name, cmd->argv);
                perror("lalala");
                close(pipefd[READ_END]);
                _exit(EXIT_SUCCESS);
           }
           else{
                // Ici on est dans le parent
                wait(NULL);
                close(pipefd[WRITE_END]);
                redirectFlow(pipefd[READ_END], STDOUT_FILENO);
                return 1;
           }
        return 1;
}