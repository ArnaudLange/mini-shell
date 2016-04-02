#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <unistd.h>

/**
 * @brief      Redirect from one file descriptor to another. Can be used to write in a file.
 *
 * @param[in]  fd_in   File descriptor which provides the input
 * @param[in]  fd_out  File descriptor which provides the output
 */
void redirectFlow(int fd_in, int fd_out);

#endif