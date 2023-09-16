#include "shell.h"

/**
 * get_path_dirs - Gets the directories in the PATH environment variable.
 * @info: The shell_info_t struct.
 * Return: A pointer to a pointer to a char.
 */
char **get_path_dirs(shell_info_t *info)
{
	char *path = get_env_var(info, "PATH");

	if (path == NULL)
	{
		return (NULL);
	}
	char **path_dirs = split_string(path, ":");

	return (path_dirs);
}

/**
 * get_env_var - Gets an environment variable.
 * @pInfo: The shell_info_t struct.
 * @string: The environment variable to get.
 * Return: A pointer to a char.
 */
char *get_env_var(shell_info_t *pInfo, const char *string)
{
	if (pInfo == NULL || string == NULL)
	{
		return (NULL);
	}

	for (int i = 0; pInfo->env[i] != NULL; i++)
	{
		if (strncmp(pInfo->env[i], string, strlen_(string)) == 0)
		{
			return (pInfo->env[i]);
		}
	}

	return (NULL);
}
