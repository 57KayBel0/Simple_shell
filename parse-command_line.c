#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 
/**
  * The maximum length command 
  * command line arguments
  * flag to determine when to exit program
  * remove trailing newline
  */

int main(void)
{
	char *args[MAX_LINE / 2 + 1];
	int should_run = 1;

	while (should_run)
	{
		printf("osh>");
		fflush(stdout);
	char input[MAX_LINE];

	fgets(input, MAX_LINE, stdin);
	input[strcspn(input, "\n")] = '\0';	
	char *token = strtok(input, " ");
	int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args);
		 printf("Error: Command not found\n");
		exit(1);
	}
	else if (pid < 0)
	{
		printf("Error: Fork failed\n");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
	}
	return (0);
}
