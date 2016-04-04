#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * @brief       Concatenates two tables
 *
 *
 */

void concatenateTables(char *tab1, char *tab2);

/**
 * @brief       Opens a file with the read only mode
 * 
 * @return      The file in Integer
 */

int openFile(char *filename);



#endif