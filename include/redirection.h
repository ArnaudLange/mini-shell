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
 * @file redirection.h
 * @author Antoine Sauray
 * @date 14 April 2016
 * @brief output redirection
 */
    
#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <string.h>
#include <unistd.h>

// STDOUT_FILENO;
// STDIN_FILENO;
// STDERR_FILENO;
                
// int fd = open("exemple.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

/**
 * @brief      Redirect from one file descriptor to another. Can be used to write in a file.
 *
 * @param      fd_in   File descriptor which provides the input
 * @param      fd_out  File descriptor which provides the output
 */
void redirectFlow(int fd_in, int fd_out);

/**
 * @brief      Redirect string to output
 *
 * @param      fd   File descriptor of output
 * @param      input  The string to output
 */
void output(int fd, char* input);

#endif