
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>

int main(int argc, char *argv[])
{
	char buf;
	int pipefd[2];

	if (pipe(pipefd) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
        }

	while (read(pipefd[1], &buf, 1) > 0){
		write(STDOUT_FILENO, &buf, 1);
	}
	write(STDOUT_FILENO, "\n", 1);
        close(pipefd[1]);
	_exit(EXIT_SUCCESS);
}


