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
    
#include "../include/utils.h"

void concatenateTables(char *tab1, char *tab2){
        /**
         * Gets the size of each table
         *
         */
        int taille1=0, taille2=0;

        while(tab1[taille1] != '\0')
        {
                taille1++;
        }

        while(tab2[taille2] != '\0')
        {
                taille2++;
        }

        /**
         * Resets the memory of the table 
         * Sets it to the addition of both tables' size
         */
        tab1 = realloc(tab1, (taille1 + taille2)*sizeof(char));

        int i = taille1;
        int j = 0;

        while(tab2[j] != '\0')
        {
                tab1[i] = tab2[j];
                i++;
                j++;
        }

}



int openFile(char *filename){
    return open(filename, O_RDONLY);
}