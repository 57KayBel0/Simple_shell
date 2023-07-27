#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

void execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error:");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error:");
	}
		else
	{
			do
		{
			waitpid(pid, &status, WUNTRACED);
		}
	while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
