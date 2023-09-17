#include "shell.h"

/**
 * printf_ - prints a string to a file descriptor
 * @str: string to print
 * @fd: file descriptor to print to
 * Return: void
 */
void printf_(char *str, int fd)
{
	fflush(stdout);
	fflush(stderr);
	write(fd, str, strlen_(str));
	fflush(stdout);
	fflush(stderr);
}
