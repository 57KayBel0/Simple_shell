#include <stdio.h>
#include <stdlib.h>
/**
 *interactive - returns true if shell is interactive mode
 *Check if the conversion was successful
 *@info: struct address
 *Return: 1 if interactive mode, 0 otherwise
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <integer>\n", argv[0]);
		return (1);
	}
	int status = atoi(argv[1]);

	if (status == 0 && argv[1][0] != '0')
	{
		printf("Invalid input: %s is not a valid integer.\n", argv[1]);
		return (0);
	}
	printf("Integer value: %d\n", status);
	return (0);
}
