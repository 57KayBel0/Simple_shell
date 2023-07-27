#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_PATH_LENGTH 200
/**
 *Function to split the command line into individual arguments
 *Skip leading whitespaces
 *Check for end of command line
 *Store the starting position of the argument
 *Find the end of the argument
 *Allocate memory and copy the argument to the arguments array
*Set the last argument to NULL for execv 
 *Return: arg_count
 */

int parse_arguments(const char *command_line, char *arguments[])
{
	int arg_count = 0;
	const char *start = command_line;

	while (*command_line != '\0' && arg_count < MAX_ARGUMENTS)
	{
	while (*command_line == ' ' || *command_line == '\t')
	{
		command_line++;
	}
	if (*command_line == '\0')
	{
		break;
	}
	start = command_line;
	while (*command_line != ' ' && *command_line != '\t' && *command_line != '\0')
	{
		command_line++;
	}
	arguments[arg_count] = (char *)malloc(command_line - start + 1);
	strncpy(arguments[arg_count], start, command_line - start);
	arguments[arg_count][command_line - start] = '\0';
	arg_count++;
	}

	arguments[arg_count] = NULL;
	return (arg_count);
}

/**
 *Function to free memory allocated for arguments
 *Function to check if the given command exists 
 *               in one of the PATH directories
 *The command exists in the current directory
 *The command was not found in any of the PATH directories
 */
void free_arguments(char *arguments[])
{
	for (int i = 0; arguments[i] != NULL; i++)
	{
		free(arguments[i]);
	}
}
int command_exists(const char *command, const char *path)
{
	char cmd[MAX_PATH_LENGTH];
	const char *dir = path;

	while (*dir != '\0')
	{
		snprintf(cmd, sizeof(cmd), "%s/%s", dir, command);
	if (access(cmd, X_OK) == 0)
	{
		return (1);
	}

		dir += strlen(dir) + 1;
	}
	return (0);
}
/**
 *+1 for NULL at the end
 *Sample PATH with two directories
 *Remove the trailing newline
 *Empty command, prompt again
 *Command exists, execute it
 *Child process
 *This will only be printed if execvp fails
 *Parent process
 *Wait for the child process to complete
 *Fork failed
 *Free memory allocated for arguments after each iteration
 */
int main(void)
{
	char command_line[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS + 1];
	char *path = "/bin:/usr/bin";

	while (1)
	{
		printf("SimpleShell> ");
		fgets(command_line, sizeof(command_line), stdin);
		command_line[strcspn(command_line, "\n")] = '\0';
		int arg_count = parse_arguments(command_line, arguments);

		if (arg_count == 0)
		{
			continue;
		}
		char *command = arguments[0];

		if (!command_exists(command, path))
		{
			printf("Command not found: %s\n", command);
			free_arguments(arguments);
			continue;
		}
		pid_t pid = fork();

		if (pid == 0)
		{
			execvp(command, arguments);
			perror("execvp");
			free_arguments(arguments);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
			free_arguments(arguments);
			exit(EXIT_FAILURE);
		}
		free_arguments(arguments);
	}
	return (0);
}
