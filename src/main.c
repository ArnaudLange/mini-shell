#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "../include/shell.h"


void welcomeMessage(){
        printf("Bienvenue dans notre Mini-shell Linux\n");
}

void printPrompt(){
        printf(">");
}



void execute(char *commande,char *argv){
        pid_t pid;

        pid = fork();
        if (pid == -1){
                printf("le fork a échoué");
        }

        if (pid == 0){ //processus enfant
                execlp(commande,argv,NULL);
        }
}

int main(int argc, char* argv[]){

        char *line=NULL;
        size_t size;
        char *chariot;
        ssize_t read;


        Shell* shell = initShell();
        

        welcomeMessage();
        while(1){
                printPrompt();
                // lecture ligne par ligne jusqu'à fin du message entré dans stdin
                while ((read = getline(&line, &size, stdin)) != -1) {                   
                        // suppression des retour chariot
                        if (chariot = strchr(line,'\n')){  
                                printf("1\n");                                                     
                                chariot = NULL;
                                //le pointeur de \n devient pointeur null
                        }                                                                                       
                        //si la ligne est vide
                        if (!strcmp(line,"")){
                                // on passe a la prochaine   
                                printf("2\n"); 
                                return EXIT_SUCCESS;                                                                                                
                        }
                        else{
                                printf("3\n"); 
                                /*
                                ParsedCommand* c = parseCommand(line);
                                printName(c);
                                printParameters(c);
                                printOptions(c);
                                free(c);
                                execute(line,line);
                                */
                                ParsedCommand* c = malloc(sizeof(ParsedCommand));
                                strncpy(c->name, "cd", NAME_SIZE);
                                printf("res=%d\n", findFunction(shell, c));
                                printf("function=%d\n", c->cmd_ptr);
                                   
                                break;  
                        }                                                      
                }
        }
        freeShell(shell); 
        return EXIT_SUCCESS;   
}

