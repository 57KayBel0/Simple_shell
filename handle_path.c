#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 200

/**
 *Function to check if the given command exists 
 *               in one of the PATH directories
 *Copy the current directory to msg and 
 *          concatenate the command name
 *The command exists in the current directory
 *move to the next directory
 *The command was not found in any of the PATH directories
 *Check if a custom PATH is provided,
 *     otherwise use the default PATH
 */
int command_exists(const char *command, const char *path)
{
	char msg[MAX_PATH_LENGTH];
	const char *dir = path;

	while (*dir != '\0')
	{
		snprintf(msg, sizeof(msg), "%s/%s", dir, command);
		if (access(msg, X_OK) == 0)
		{
			return (1);
		}
		dir += strlen(dir) + 1;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [PATH]\n", argv[0]);
		return (1);
	}

	const char *path = (argc >= 3) ? argv[2] : "/bin:/usr/bin";
	const char *command = argv[1];

	if (!command_exists(command, path))
	{
		fprintf(stderr, "Command not found: %s\n", command);
		return (1);
	}
	printf("Command exists: %s\n", command);
	return (0);
}
