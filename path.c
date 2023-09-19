#include "shell.h"

/**
 * path_exists - Checks if a path exists.
 * @path: The path to check.
 * Return: 1 if the path exists, 0 otherwise.
 */
int path_exists(char *path)
{
	if (access(path, F_OK) == 0)
		return (1);

	return (0);
}

/**
 * get_path_dirs - Gets the directories in the PATH environment variable.
 * @info: The shell_info_t struct.
 * Return: A pointer to a pointer to a char.
 */
char **get_path_dirs(shell_info_t *info)
{
	char *path = get_env_var(info, "PATH");
	char **path_dirs;


	if (path == NULL)
	{
		return (NULL);
	}
	path_dirs = split_string(path, ":");

	return (path_dirs);
}


/**
 * check_current_dir - Checks if the command is in the current directory.
 * @info: The shell_info_t struct.
 * Return: 1 if the command is in the current directory, 0 otherwise.
 */
int check_current_dir(shell_info_t *info)
{
	if (info->args[0][0] == '.' || info->args[0][0] == '/')
	{
		if (path_exists(info->args[0]))
		{
			info->fp = malloc(sizeof(char) * (strlen_(info->args[0]) + 1));
			strcpy_(info->fp, info->args[0]);
			return (1);
		}
	}
	return (0);
}

/**
 * get_path - Gets the path of a command.
 * @info: The shell_info_t struct.
 * Return: A pointer to a char.
 */
void get_path(shell_info_t *info)
{
	char **path_dirs;

	info->fp = NULL;

	if (info == NULL)
		return;

	if (check_current_dir(info) == 1)
		return;

	path_dirs = get_path_dirs(info);

	if (path_dirs == NULL)
	{
		return;
	}

	check_env_dirs(info, path_dirs);

	free_char_ptr(path_dirs);
}

/**
 * check_env_dirs - Checks if the command is in the PATH environment variable.
 * @info: The shell_info_t struct.
 * @path_dirs: The directories in the PATH environment variable.
 * Return: Nothing.
 */
void check_env_dirs(shell_info_t *info, char **path_dirs)
{
	int i;

	for (i = 0; path_dirs[i] != NULL; i++)
	{
		info->fp = malloc(sizeof(char) *
						  (strlen_(path_dirs[i]) + strlen_(info->args[0]) + 2));
		strcpy_(info->fp, path_dirs[i]);
		strcat_(info->fp, "/");
		strcat_(info->fp, info->args[0]);
		if (path_exists(info->fp))
			return;
		free(info->fp);
		info->fp = NULL;
	}
}
