#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1000
#define MAX_ARGUMENTS 100
/**
 *Tokenize the command into individual arguments
 *Fork a child process to execute the command
 *Child process
 *execvp only returns if an error occurs
 *Parent process
 *Read input from the user
 *Split input into individual commands using ;
 *Execute each command sequentially
 *
 */
void execute_command(char *command)
{
	char *arguments[MAX_ARGUMENTS];
	int arg_count = 0;
	char *token = strtok(command, " \t\n");

	while (token != NULL && arg_count < MAX_ARGUMENTS - 1)
	{
		arguments[arg_count++] = token;
		token = strtok(NULL, " \t\n");
	}
	arguments[arg_count] = NULL;
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
	}
	else if (pid == 0)
	{
	execvp(arguments[0], arguments);
	perror("execvp failed");
	exit(EXIT_FAILURE);
	}
	else
	{
	int status;

	waitpid(pid, &status, 0);
	}
}
int main(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("Shell> ");
		fflush(stdout);

	if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
	{
		break;
	}
	char *token = strtok(input, ";");

	while (token != NULL)
	{
		execute_command(token);
		token = strtok(NULL, ";");
	}
	}
	return (0);
}
