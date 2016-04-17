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

#include "../../include/commands/clear.h"




int clear_lib (int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int nbLigneScreen = w.ws_row;

    int k;
    for(k=0;k<nbLigneScreen;k++){
    	//printf("\033[A\33[2K");
        printf("\n");
    }

    return 0;  // make sure your main returns int
}
