#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


struct command{
	char name[100];
        char parameters[100];
	int (*cmd_ptr)(int, int);
};


typedef struct command Command;

Command* parseCommand(char* input);

int ls_lib(int argc, char* argv[]);

#endif