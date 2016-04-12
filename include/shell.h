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
    
#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <string.h>

#include "commands.h"

#include "parameters.def"

/**
 * @brief      Shell structure
 * Manages the internal commands and the current directory
 */
struct shell{
        int nbCmd;
        Command* commands[MAXCMD];
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