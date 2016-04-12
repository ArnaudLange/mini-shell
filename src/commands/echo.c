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
#include "../../include/commands/echo.h" //à virer une fois les tests effectués

int echo_lib(int argc, char *argv[]){

    int i;
    int etatN=0;

    for(i=1; i<argc; i++){
        if (!strcmp(argv[i],"-n")){
            etatN=1;
        }
        else{
            printf("%s ",argv[i]);
        }
    }
    if(!etatN){
        printf("\n");
    }
    return 0;
}

