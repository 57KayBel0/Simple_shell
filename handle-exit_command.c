#include <stdlib.h>
#include <stdio.h>
/**
 *function is defined by the stdlib header file
 *@argc: int value passes to the operating
 *       system after successful termination
 *@argv: It’s a type of function with a
 *       return type without an argument 
 *Return: 1 & exit status
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s status\n", argv[0]);
		return (1);
	}
	int status = atoi(argv[1]);

	exit(status);
}
