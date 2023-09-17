#include "shell.h"

/**
 * handle_print_env - handles the env command
 * @info: the shell info
 * Return: 1 if handled, 0 otherwise
 */
int handle_print_env(shell_info_t *info)
{
	if (strcmp(info->args[0], "env") == 0)
	{
		print_env(info);
		if (isatty(STDIN_FILENO))
		{
			printf_("$ ", STDOUT_FILENO);
		}
		free(info->args);
		info->args = NULL;
		return (1);
	}
	return (0);
}


/**
 * handle_set_env - handles the setenv command
 * @info: the shell info
 * Return: 1 if handled, 0 otherwise
 */
int handle_set_env(shell_info_t *info)
{
	if (strcmp(info->args[0], "setenv") == 0)
	{
		if (info->args[1] == NULL)
		{
			printf_("setenv: Too few arguments.\n", STDERR_FILENO);
			free(info->args);
			info->args = NULL;
			return (1);
		}
		if (info->args[2] != NULL)
		{
			set_env(info, info->args[1], info->args[2]);
		}
		if (isatty(STDIN_FILENO))
		{
			printf_("$ ", STDOUT_FILENO);
		}
		free(info->args);
		info->args = NULL;
		return (1);
	}
	return (0);
}

/**
 * handle_unset_env - handles the unsetenv command
 * @info: the shell info
 * Return: 1 if handled, 0 otherwise
 */
int handle_unset_env(shell_info_t *info)
{
	if (strcmp(info->args[0], "unsetenv") == 0)
	{
		if (info->args[1] == NULL)
		{
			printf_("unsetenv: Too few arguments.\n", STDERR_FILENO);
			free(info->args);
			info->args = NULL;
			return (1);
		}
		unset_env(info, info->args[1]);
		if (isatty(STDIN_FILENO))
		{
			printf_("$ ", STDOUT_FILENO);
		}
		free(info->args);
		info->args = NULL;
		return (1);
	}
	return (0);
}
