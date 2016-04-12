/*
    This file is part of Binsh.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/
    
#define NAME "echo"
#include "../../include/commands/echo.h"

void init(char name[NAME_SIZE], int (*cmd_ptr)(int, char*[])){
        strncpy(name, NAME, NAME_SIZE);
        cmd_ptr = &echo_lib;
}

int main(int argc, char* argv[]){
        echo_lib(argc, argv);
}