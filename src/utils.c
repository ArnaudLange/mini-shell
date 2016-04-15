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
    
#include "../include/utils.h"

char * concatenateTables(char *tab1, char *tab2){
        /**
         * Gets the size of each table
         *
         */

        int taille1=0, taille2=0;
        taille1 = strlen(tab1);
        taille2 = strlen(tab2);
        /**
         * Resets the memory of the table 
         * Sets it to the addition of both tables' size
         */
        tab1 = realloc(tab1, (taille1 + taille2 + 1)*sizeof(char));
        if (tab1 == NULL){
            perror("realloc");
            exit(1);
        }
        /**
         * Concatenate both tables
         * Using de function strcat()
         */
        strcat(tab1,tab2);

        return tab1;

}



int openFile(char *filename){
    return open(filename, O_RDONLY);
}