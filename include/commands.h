#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


struct command{
	char* name[20];
	int (*cmd_ptr)(int, int);
};

int ls_lib(int argc, char* argv[]);

#endif