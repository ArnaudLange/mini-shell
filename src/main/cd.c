#include "../../include/commands/cd.h"

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
        char *param[1];
        param[0] = "~";
        cd_internal(0, param);
        printf("%s\n", get_current_dir_name());
}