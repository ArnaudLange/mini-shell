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

int execute(char *commande,char *argv){
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