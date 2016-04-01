#ifndef CD_H
#define CD_H

#include "../shell.h"

int cd_lib(int argc, char* argv[], Shell* shell){
        printf("cd");
        if(argc > 1){
                
                strncpy(shell->currDir, argv[2], NAME_SIZE);
        }
        return 0;
}

int test(int argc, char* argv[]){
        printf("test");
        return 1;
}

#endif