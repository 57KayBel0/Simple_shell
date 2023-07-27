#include <stdlib.h>
#include <stdio.h>
/**
 *Set environment variable
 *Modify environment variable
 *Remove environment variable
 */
int main(void)
{
	char *var = "MYVAR";
	char *val = "MYVAL";
	char *new_val = "NEWVAL";

	if (setenv(var, val, 1) != 0)
	{
		perror("setenv");
		return (EXIT_FAILURE);
	}
	if (setenv(var, new_val, 1) != 0)
	{
		perror("setenv");
		return (EXIT_FAILURE);
	}
	if (unsetenv(var) != 0)
	{
		perror("unsetenv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
