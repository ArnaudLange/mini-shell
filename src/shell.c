#include "../include/shell.h"

Shell* initShell(){
        Shell* shell = malloc(sizeof(Shell));
        (*shell).nbCmd = initCommands(shell->commands);
        strncpy((*shell).currDir, "~", MAXSIZE);
        return shell;
}

void freeShell(Shell* shell){
        //printf("nbCmd=%d\n", (*shell).nbCmd);
        int res = freeCommands((*shell).nbCmd, (*shell).commands);
        if(res==1){printf("Commands have been freed\n");}
        free(shell);
        printf("Shell has been freed\n");
}

int findFunction(Shell* shell, ParsedCommand* command){
        int i=0;
        while(i<shell->nbCmd){
            if(strcmp((*shell->commands)[i].name,(*command).name) == 0){
                printf("found the function !\n");
                (*command).cmd_ptr = (*shell->commands)[i].cmd_ptr;
                return 1;
            }    
            i++;
        }
        (*command).cmd_ptr = NULL;
        return 0;
}
