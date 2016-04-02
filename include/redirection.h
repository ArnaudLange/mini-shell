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
 * @param[in]  fd_in   File descriptor which provides the input
 * @param[in]  fd_out  File descriptor which provides the output
 */
void redirectFlow(int fd_in, int fd_out);

void output(int fd, char* input);

#endif