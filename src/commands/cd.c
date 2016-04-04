#include "../../include/commands/cd.h"

int cd_internal(int argc, char* argv[]){
        if(argc>0){
                chdir(argv[0]);
        }
        else{
                chdir("~");
        }
        return 1;
}