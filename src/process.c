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
    
#include "../include/process.h"

#define READ_END 0
#define WRITE_END 1

int test_execute(char *commande,char *argv){
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
                execlp("ls", "ls", (char *)NULL);
                close(pipefd[READ_END]);
                _exit(EXIT_SUCCESS);
           }
           else{
                // Ici on est dans le parent
                printf("parent\n");
                wait(NULL);
                close(pipefd[WRITE_END]);
                redirectFlow(pipefd[READ_END], STDOUT_FILENO);
                printf("parent\n");
                
                return 1;
           }
        return 1;
}

int test_internal_ls(int fd_in, int fd_out){
        
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

                char *param[1];
                param[0] = "-l";
                //printf("%s\n", param[0]);
                ls_lib(1, param);

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

int executeShellCommand(int fd_in, int fd_out, Shell* shell, ParsedCommand* cmd){
        if(findFunction(shell, cmd)){
                return executeInternalCommand(fd_in, fd_out, cmd);
        }
        else{
                // If command doesn't exist internally or as a library, we start it from PATH
                return executeInternalCommand(fd_in, fd_out, cmd);
        }
}

int executeInternalCommand(int fd_in, int fd_out, ParsedCommand* cmd){
        
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

int executeExternalCommand(char *commande,char *argv){
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
                execlp(commande, argv, (char *)NULL);
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