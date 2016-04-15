
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
 * @file server.h
 * @author Antoine Sauray
 * @date 14 April 2016
 * @brief background server for remote access
 */

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include <sys/select.h>
#include <arpa/inet.h>

#include "shell.h"

/**
 * @brief      Read input from socket and execute the associated command
 *
 * @param[in]  filedes  input socket
 * @param      shell    the shell context
 *
 * @return     1 if no error, 0 otherwise
 */
int readAndExecute (int filedes, Shell* shell);
/**
 * @brief      start the background server
 *
 * @param      loadedShell  parameter for the fonction. Can be anything. In this case, we provide the shell context.
 *
 * @return     void
 */
void *start(void *loadedShell);
/**
 * @brief      Opens a socket. If port is not free, it will increment up to 10000 until it finds one.
 *
 * @param[in]  port  the starting port
 *
 * @return     the opened port
 */
int makeSocket (uint16_t port);

#endif