#include <stdio.h>
#include "test.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int m = 15;

	uid_t uid=getuid();
	printf("%d\n",uid);

	Process currentProcess;
	currentProcess.pid=m;

	printf("%d\n",currentProcess.pid);
	return 0;
}