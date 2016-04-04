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