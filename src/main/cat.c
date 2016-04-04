#include "../../include/commands/cat.h"

int main(int argc, char* argv[]){
        char *param[1];
        param[0] = "~";
        cat_lib(0, param);
}