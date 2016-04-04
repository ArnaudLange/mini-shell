#include "../../include/commands/cd.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
        char *param[1];
        param[0] = "~";
        cd_internal(0, param);
        char my_cwd[1024];
        getcwd(my_cwd, 1024);
        printf("%s\n", my_cwd);
}