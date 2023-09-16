#include "shell.h"

/**
 * parse_line - Parses a line in a shell_info_t struct.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 */
void parse_line(shell_info_t *info)
{
	char *token = strtok(info->line, " ");
	size_t size = 0;

	while (token != NULL)
	{
		info->args = realloc_char_ptr(info->args, (size + 1) * sizeof(char *));

		if (info->args == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		info->args[size] = token;
		size++;
		token = strtok(NULL, " ");
	}

	info->args = realloc_char_ptr(info->args, (size + 1) * sizeof(char *));
	if (info->args == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	info->args[size] = NULL;
}

/**
 * isspace_ - Checks if a character is a space.
 * @c: The character.
 * Return: 1 if the character is a space, 0 otherwise.
 */
int isspace_(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
		c == '\r')
	{
		return (1);
	}
	return (0);
}
