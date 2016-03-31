#ifndef SHELL_H
#define SHELL_H

#define MAXSIZE 200

#include <stdlib.h>
#include <string.h>

#include "commands.h"

/**
 * @brief      Shell structure
 * Manages the internal commands and the current directory
 */
struct shell{
        int nbCmd;
        Command** commands;
        char currDir[MAXSIZE];
};

typedef struct shell Shell;

Shell* initShell();
void freeShell(Shell* shell);
#endif