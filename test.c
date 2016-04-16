#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	printf("%ld\n",sysconf(_SC_CLK_TCK));
	return 0;
}