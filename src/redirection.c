#include "../include/redirection.h"


void redirectFlow(int fd_in, int fd_out){
        char buffer;
        while (read(fd_in, &buffer, 1) > 0){
                write(fd_out, &buffer, 1);
        }
}

void output(int fd, char* input){
        write(fd, input, strlen(input));
}