#include "../../include/commands/cd.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int cd_internal(int argc, char* argv[]){
        if(argc>0){
                return chdir(argv[0]);
        }
        else{
                return chdir(getpwuid(getuid())->pw_dir);
        }
}