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

/**
 * print_error - prints an error message
 * @info: shell info struct
 * @fd: file descriptor to print to
 * @message: error message
 * @index: index of the command
 * Return: void
 */
void print_error(shell_info_t *info, int fd, char *message, char *index)
{
	printf_(info->argv[0], fd);
	printf_(": ", fd);
	printf_(index, fd);
	printf_(": ", fd);
	printf_(info->args[0], fd);
	printf_(": ", fd);
	printf_(message, fd);
	printf_("\n", fd);
}


/**
 * getline_ - Gets a line from stdin.
 * @info: The shell_info_t struct.
 * Return: The number of bytes read.
 */
size_t getline_(shell_info_t *info)
{
	ssize_t maxLength = sizeof(info->line);
	ssize_t bytesRead = 0;
	char c;
	int iseof = 0;

	for (ssize_t i = 0; i < maxLength; i++)
	{
		bytesRead = read(STDIN_FILENO, &c, 1);
		if (bytesRead == -1)
		{
			iseof = 1;
		}
		else if (bytesRead == 0)
		{
			iseof = 1;
			break;
		}
		else if (c == '\n' || c == ';')
		{
			info->line[i] = '\0';
			break;
		}
		else
			info->line[i] = c;
	}

	if (iseof)
		return ((size_t) -1);
	return (strlen_(info->line));
}
