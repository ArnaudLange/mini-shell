#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "../include/shell.h"
#include "../include/process.h"


void welcomeMessage(){
        printf("Binsh 0.1\n");
}

void printPrompt(){
        printf(">");
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
                                //test_internal_ls(STDIN_FILENO, STDOUT_FILENO);
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

