#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "commands/ls.h"
#include "redirection.h"
#include "commands.h"

int test_execute(char *commande,char *argv);
int test_internal_ls(int fd_in, int fd_out);
int executeInternalCommand(int fd_in, int fd_out, ParsedCommand* cmd);
int executeExternalCommand(char *commande,char *argv);

#endif