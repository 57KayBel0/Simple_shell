#include "simple_shell.h"
/**
 * init_buitin - Init built-in functions
 * @args: user input array arguments
 * @buffer: getline malloc'd user input
 * @loops: times that loop has been executed
 * Return: 0 on exit, 1 to continue with the program
 */
int init_builtin(char **args, char *buffer, int loops)
{
	if (_strcmp(args[0], "env") == 0)
	{
		shb_env();
		free_function(1, buffer), free_function(2, args);
		return (1);
	}
	else if (_strcmp(buffer, "exit") == 0)
		shb_exit(args, buffer, loops);
	else if (_strcmp(args[0], "cd") == 0)
	{
		shb_cd(args);
		free_function(1, buffer), free_function(2, args);
		return (1);
	}
	return (0);
}

/**
 * shb_exit -  Function that exits the Simple shell
 * @args: user input array arguments
 * args[1] is the number to exit
 * @buffer: getline malloc'd user input
 * Return: Nothing
 */
int shb_exit(char **args, char *buffer, int loops)
{
	int status = 0;
	char err[100];

	if (args[1] != NULL)
	{
		if (_isdigit(args[1]))
		{
			status = atoi(args[1]);
		if (status > 255)
			status = status % 256;
		if (status < 0)
			{
				sprintf(err, "./hsh: %d: %s: Unfined number %s\n"
					, loops, args[0], args[1]);
				write(STDERR_FILENO, &err, _strlen(err));
				status = 2;
			}
		}
		else
		{
			sprintf(err, "./hsh: %d: %s: Unfined number: %s\n",
				loops, args[0], args[1]);
			write(STDERR_FILENO, &err, _strlen(err));
			status = 2;
		}
	}
	free_function(1, buffer), free_function(2, args);
	exit(status);
}

/**
 * shb_env - Prints the global environment variable
 * Return: Nothing
 */
void shb_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", i);
	}
}
/**
 * shb_cd - change directory according argument
 * @args: user input array arguments *SOLVE ERRORS*
 * Return: Nothing
 */

void shb_cd(char **args)
{
	char *home = getenv("HOME");
	char *previous = getenv("OLDPWD");

	if ((args[1] == NULL && home) || (args[1][0] == '~' && home))
	{
		chdir(home);
	}
	else if (args[1][0] == '-' && previous)
	{
		chdir(previous);
	}
	else if (chdir(args[1]) != 0)
	{
		perror("hsh");
	}
}
/**
 * sighandle - This program allows ctrl+C to be
 * printed and new line with enter is pressed
 * @sign: int
 */
void sighandle(int sign)
{
	if (sign == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 3);
}
