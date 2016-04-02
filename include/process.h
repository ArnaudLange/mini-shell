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

#include "redirection.h"

int test_execute(char *commande,char *argv);
int execute(char *commande,char *argv);

#endif