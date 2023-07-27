#include "simple_shell.h"
/**
 * handle_env_builtin - Handle the env built-in command
 *
 * Return: 0 on success, 1 on failure
 */
int handle_env_builtin(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
