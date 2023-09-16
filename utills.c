#include "shell.h"

/**
 * parse_line - Parses a line in a shell_info_t struct.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 */
void parse_line(shell_info_t *info)
{
	char *token = strtok(info->line, " ");

	info->args = malloc(sizeof(char *) * 2);
	if (info->args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	info->args[0] = token;
	info->args[1] = NULL;
}
