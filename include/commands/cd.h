#ifndef CD_H
#define CD_H

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int cd_internal(int argc, char* argv[]);

#endif