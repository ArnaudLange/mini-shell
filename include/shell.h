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

/**
 * @brief      Initializes our Shell with all the functions
 *
 * @return     The dynamically allocated Shell
 */
Shell* initShell();

/**
 * @brief      Free the memory have allocation of the Shell
 *
 * @param      shell  The Shell to free
 */
void freeShell(Shell* shell);

int findFunction(Shell* shell, ParsedCommand* command);

#endif