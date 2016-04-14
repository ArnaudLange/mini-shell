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

int readAndExecute (int filedes, Shell* shell);
void *start(void *loadedShell);
int makeSocket (uint16_t port);

#endif