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
	int end = (int) strlen(str) - 1;

	while (isspace(str[start]))
	{
		start++;
	}

	while (end >= start && (isspace(str[end]) || str[end] == '\n'))
	{
		end--;
	}

	for (int i = start; i <= end; i++)
	{
		str[i - start] = str[i];
	}

	str[end - start + 1] = '\0';
}


/**
 * getline_ - Gets a line from stdin.
 * @info: The shell_info_t struct.
 * Return: The number of bytes read.
 */
size_t getline_(shell_info_t *info)
{
	while (1)
	{
		if (fgets(info->line, sizeof(info->line), stdin) == NULL)
		{
			return (-1);
		}

		size_t len = strlen(info->line);

		if (len > 0 && info->line[len - 1] == '\n')
		{
			info->line[len - 1] = '\0';
			return (len);
		}

		if (info->line[0] == '\0')
		{
			return (0);
		}

		printf("Read line: %s\n", info->line);
	}

}
