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

/**
 * @file shell.h
 * @author Antoine Sauray
 * @date 14 April 2016
 * @brief shell modelisation
 */

    
#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "commands.h"
#include "redirection.h"

#include "parameters.def"

/**
 * @brief      Shell structure
 * Manages the internal commands and the current directory
 */
struct shell{
        int nbInternalCmd;
        int nbLibraryCmd;
        Command* internal_commands[MAXCMD];
        Command* library_commands[MAXCMD];
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

/**
 * @brief      Execute a commands and redirects the flow to the right file descriptor
 *
 * @param      fd_in the input file descriptor
 * @param      fd_out the ouput file descriptor
 * @param      shell the shell context
 * @param      cmd the command to execute           
 */
int executeCommand(int fd_in, int fd_out, Shell* shell, ParsedCommand* cmd);

int executeInternalCommand(ParsedCommand* cmd);
/**
 * @brief      Execute an internal command and redirects the flow to the right file descriptor
 *
 * @param      fd_in the input file descriptor
 * @param      fd_out the ouput file descriptor
 * @param      cmd the command to execute           
 */
int executeLibraryCommand(int fd_in, int fd_out, ParsedCommand* cmd);
/**
 * @brief      Execute an external command
 *
 * @param      commande the command string
 * @param      argv the arguments     
 */
int executeExternalCommand(int fd_in, int fd_out, ParsedCommand* cmd);

/**
 * @brief      Find a function within a Shell based on its name
 *
 * @param      shell  The Shell in which to look
 * @param      command the command to look for
 */
int findFunction(Shell* shell, ParsedCommand* command);
/**
 * @brief      Check if a function exists in a shell
 *
 * @param      shell  The Shell in which to look
 * @param      name the name of the function to look for
 */
int checkFunction(Shell* shell, char* name);
/**
 * @brief      Check and a function if it exists in a shell
 *
 * @param      shell  The Shell in which to look
 * @param      name the name of the function to look for
 * @param      argc the number of parameters
 * @param      argv the parameters
 */
int testFunction(Shell* shell, char* name, int argc, char* argv[]);

#endif