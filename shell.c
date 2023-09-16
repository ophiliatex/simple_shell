#include "shell.h"

/**
 * init_shell_info - Initializes a shell_info_t struct.
 * @env: The environment.
 * @path: The path.
 * @argc: The number of arguments.
 * @argv: The arguments.
 * Return: The initialized shell_info_t struct.
 * Description: Initializes a shell_info_t struct.
 */
shell_info_t *init_shell_info(char **env, const char *path, int argc,
							  char **argv)
{
	shell_info_t *info = malloc(sizeof(shell_info_t));

	if (info == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	info->args = NULL;
	info->argc = argc;
	info->argv = argv;
	info->line[0] = '\0';
	info->lines = NULL;
	info->env = env;

	(void) path;

	return (info);
}

/**
 * free_shell_info - Frees a shell_info_t struct.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 * Description: Frees a shell_info_t struct.
 */
void free_shell_info(shell_info_t *info)
{
	if (info == NULL)
	{
		return;
	}

	if (info->args != NULL)
	{
		free(info->args);
	}
	info->args = NULL;
	free(info);
}

/**
 * execute_command - Executes a command in a shell_info_t struct.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 */
void execute_command(shell_info_t *info)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(info->args[0], info->args, info->env) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * shell_loop - The shell loop.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 * Description: The shell loop.
 */
void shell_loop(shell_info_t *info)
{
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		if (getline_(info) == (size_t) -1)
		{
			break;
		}

		trim(info->line);
		if (strlen_(info->line) == 0)
		{
			continue;
		}

		parse_line(info);

		execute_command(info);

		free_last_command(info);
	}
}

/**
 * free_last_command - Frees the last command in a shell_info_t struct.
 * @pInfo: The shell_info_t struct.
 * Return: Nothing.
 */
void free_last_command(shell_info_t *pInfo)
{
	free(pInfo->args);
	pInfo->args = NULL;
}
