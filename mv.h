#pragma once

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void readOptions(char *options);
void concatenateTables(char *tab1, const char *tab2);
void myMv(char* arg1, char* arg2, char**options, int iOptions);