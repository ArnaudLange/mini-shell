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
   
#define NAME "cat" 
#include "../../include/commands/cat.h"

cmdPtr init(char name[NAME_SIZE]){
        strncpy(name, NAME, NAME_SIZE);
        return &cat_lib;
}

int main(int argc, char* argv[]){
        cat_lib(argc, argv);
}