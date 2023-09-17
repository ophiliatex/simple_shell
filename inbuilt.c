#include "shell.h"

/**
 * handle_exit - handles the exit builtin
 * @info: the shell info
 *
 * Return: 1 if exit was called, 0 otherwise
 */
int handle_exit(shell_info_t *info)
{
	if (strcmp_(info->line, "exit") == 0)
	{
		if (info->args[1] != NULL)
		{
			info->status = atoi_(info->args[1]);
			if (info->status < 0 || isint(info->args[1]) == 0)
			{
				int fd = STDERR_FILENO;

				if (isatty(STDIN_FILENO))
				{
					fd = STDOUT_FILENO;
				}
				char *msg = malloc(sizeof(char) * (strlen_("Illegal number: ") +
												   strlen_(info->args[1]) + 1));
				msg = strcpy_(msg, "Illegal number: ");
				msg = strcat_(msg, info->args[1]);
				print_error(info, fd, msg, "1");
				free(msg);
				info->status = 2;
			}
		}
		return (1);
	}
	return (0);
}

/**
 * handle_inbuilt - handles the inbuilt commands
 * @info: the shell info
 *
 * Return: 2 if exit was called, 0 otherwise
 */
int handle_inbuilt(shell_info_t *info)
{
	if (handle_exit(info) == 1)
	{
		return (2);
	}

	if (handle_env(info) == 1)
	{
		return (1);
	}

	if (handle_cd(info) == 1)
	{
		return (1);
	}

	return (0);
}

/**
 * isint - checks if a string is an int
 * @string: the string to check
 * Return: 1 if string is an int, 0 otherwise
 */
int isint(const char *string)
{
	if (string == NULL)
	{
		return (0);
	}

	int isneg = 0;

	if (string[0] == '-')
	{
		isneg = 1;
	}

	for (int i = isneg; string[i] != '\0'; i++)
	{
		if (string[i] < '0' || string[i] > '9')
		{
			return (0);
		}
	}
	return (1);
}
