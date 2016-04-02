#include "../include/redirection.h"


void redirectFlow(int fd_in, int fd_out){
        char buffer;
        while (read(fd_in, &buffer, 1) > 0){
                write(fd_out, &buffer, 1);
        }
}