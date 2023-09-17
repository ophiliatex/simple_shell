#include "shell.h"

/**
 * handle_cd_home - handles the cd builtin with no arguments
 * @info: the shell info
 * Return: 1 if cd was called, 0 otherwise
 */
int handle_cd_home(shell_info_t *info)
{
	if (info->args[1] == NULL)
	{
		char *home2 = get_env_var(info, "HOME");

		if (home2 == NULL)
		{
			home2 = get_env_var(info, "PWD");
		}
		char *home = strdup_(home2);

		if (chdir(home) == -1)
		{
			int fd = STDERR_FILENO;

			if (isatty(STDIN_FILENO))
			{
				fd = STDOUT_FILENO;
			}
			printf_("cd: ", fd);
			printf_("HOME not set\n", fd);
			free_last_command(info);
			return (1);
		}
		set_env(info, "OLDPWD", get_env_var(info, "PWD"));
		set_env(info, "PWD", home);
		free(home);
		return (1);
	}
	return (0);
}

/**
 * handle_cd_back - handles the cd builtin with -
 * @info: the shell info
 * Return: 1 if cd was called, 0 otherwise
 */
int handle_cd_back(shell_info_t *info)
{
	if (strcmp_(info->args[1], "-") == 0)
	{
		char *ch = get_env_var(info, "OLDPWD");

		if (ch == NULL)
		{
			ch = get_env_var(info, "PWD");
		}
		char *oldpwd = strdup_(ch);

		if (chdir(oldpwd) == -1)
		{
			printf_("cd: ", STDERR_FILENO);
			return (check_error(info));
		}
		printf_(oldpwd, STDOUT_FILENO);
		printf_("\n", STDOUT_FILENO);
		set_env(info, "OLDPWD", get_env_var(info, "PWD"));
		set_env(info, "PWD", oldpwd);
		free(oldpwd);
		free_last_command(info);
		return (1);
	}
	return (0);
}

/**
 * check_error - checks for errors in cd
 * @info: the shell info
 * Return: 1 if error, 0 otherwise
 */
int check_error(shell_info_t *info)
{
	if (errno == EACCES)
	{
		printf_("Permission denied\n", STDERR_FILENO);
		free_last_command(info);
	}
	else if (errno == ENOENT)
	{
		print_cd_error(info, "No such file or directory");
		free_last_command(info);
	}
	else if (errno == ENOTDIR)
	{
		printf_("Not a directory\n", STDERR_FILENO);
		free_last_command(info);
	}
	else
	{
		printf_("OLDPWD not set\n", STDERR_FILENO);
		free_last_command(info);
	}
	return (1);
}

/**
 * print_cd_error - prints the cd error
 * @info: the shell info
 * @msg: the message to print
 * Return: 1 if error, 0 otherwise
 */
void print_cd_error(const shell_info_t *info, char *msg)
{
	int fd = STDERR_FILENO;

	if (isatty(STDIN_FILENO))
	{
		fd = STDOUT_FILENO;
	}
	printf_(info->args[0], fd);
	printf_(": ", fd);
	printf_(info->args[1], fd);
	printf_(": ", fd);
	printf_(msg, fd);
	printf_("\n", fd);
}

/**
 * handle_cd - handles the cd builtin
 * @info: the shell info
 * Return: 1 if cd was called, 0 otherwise
 */
int handle_cd(shell_info_t *info)
{
	if (info == NULL)
	{
		return (0);
	}

	if (strcmp_(info->args[0], "cd") == 0)
	{
		if (handle_cd_home(info) == 1)
		{
			return (1);
		}
		if (handle_cd_back(info) == 1)
		{
			return (1);
		}
		if (chdir(info->args[1]) == -1)
		{
			int fd = STDERR_FILENO;

			if (isatty(STDIN_FILENO))
			{
				fd = STDOUT_FILENO;
			}
			char *msg = malloc(sizeof(char) * (strlen_("can't cd to ") +
											   strlen_(info->args[1]) + 1));

			msg = strcpy_(msg, "can't cd to ");
			msg = strcat_(msg, info->args[1]);
			print_error(info, fd, msg, "1");
			free(msg);
		}
		else
		{
			set_env(info, "OLDPWD", get_env_var(info, "PWD"));
			set_env(info, "PWD", info->args[1]);
		}
		free_last_command(info);
		return (1);
	}
	return (0);
}
