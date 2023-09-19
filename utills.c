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

/**
 * atoi_ - Converts a string to an integer.
 * @str: The string.
 * Return: The integer.
 */
int atoi_(const char *str)
{
	int res = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; str[i] != '\0'; ++i)
	{
		res = res * 10 + str[i] - '0';
	}

	return (sign * res);
}

/**
 * trim - Trims a string.
 * @str: The string.
 * Return: Nothing.
 * Description: Trims a string.
 */
void trim(char *str)
{
	int i;
	int start = 0;
	int end = (int) strlen_(str) - 1;

	while (isspace_(str[start]))
		start++;

	while (end >= start && (isspace_(str[end]) || str[end] == '\n'))
		end--;

	for (i = start; i <= end; i++)
		str[i - start] = str[i];

	str[end - start + 1] = '\0';
}
