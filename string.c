#include "shell.h"

/**
 * trim - Trims a string.
 * @str: The string.
 * Return: Nothing.
 * Description: Trims a string.
 */
void trim(char *str)
{
	int start = 0;
	int end = (int) strlen_(str) - 1;

	while (isspace_(str[start]))
		start++;

	while (end >= start && (isspace_(str[end]) || str[end] == '\n'))
		end--;

	for (int i = start; i <= end; i++)
		str[i - start] = str[i];

	str[end - start + 1] = '\0';
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
		else if (c == '\n')
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

/**
 * split_string - Splits a string into tokens.
 * @str: The string.
 * @delim: The delimiter.
 * Return: The tokens.
 */
char **split_string(char *str, char *delim)
{
	char **tokens = NULL;
	char *token;
	int idx = 0;

	token = strtok(str, delim);
	while (token != NULL)
	{
		tokens = realloc_char_ptr(tokens, (idx + 1) * sizeof(char *));
		if (tokens == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		tokens[idx] = token;
		idx++;
		token = strtok(NULL, delim);
	}
	tokens = realloc_char_ptr(tokens, (idx + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	tokens[idx] = NULL;
	return (tokens);
}

/**
 * strlen_ - Gets the length of a string.
 * @str: The string.
 * Return: The length of the string.
 */
int strlen_(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}
