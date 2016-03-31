#include "../include/shell.h"

Shell* initShell(){
        Shell* shell = malloc(sizeof(Shell));
        Command* commands[100];
        (*shell).nbCmd = initCommands(commands);
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