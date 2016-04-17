/*
    This file is part of Binsh.

    Binsh is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Binsh is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/
    
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