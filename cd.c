#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#define MAX_PATH 260

/**
 *current directory might be unreachable: not an error
 *this should be done on all words during the parse phase
 */
int exec_cd(char *arg)
{
	char curdir[MAX_PATH];
	char path[MAX_PATH];

	if (getcwd(curdir, sizeof(curdir)))
	{
		*curdir = '\0';
	}
	if (arg == NULL)
	{
		arg = getenv("HOME");
	}
	if (!strcmp(arg, "-"))
	{
	if (*lastdir == '\0')
	{
		fprintf(stderr, "no previous directory\n");
		return (1);
	}
		arg = lastdir;
	}
	else
	{
	if (*arg == '~')
	{
	if (arg[1] == '/' || arg[1] == '\0')
	{
		snprintf(path, sizeof(path), "%s%s", getenv("HOME"), arg + 1);
			arg = path;
	}
	else
	{
		fprintf(stderr, "syntax not supported: %s\n", arg);
		return (1);
	}
	}
	}
	if (chdir(arg))
	{
		fprintf(stderr, "chdir: %s: %s\n", strerror(errno), path);
		return (1);
	}
	strcpy(lastdir, curdir);
	return (0);
}
