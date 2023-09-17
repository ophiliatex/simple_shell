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
	info->env = init_list();
	info->status = 0;

	for (int i = 0; env[i] != NULL; i++) {
		add_node(info->env, env[i]);
	}

	info->envp = list_to_array(info->env);

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

	free_char_ptr(info->envp);
	free_list(info->env);
	info->env = NULL;
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
		if (execve(info->args[0], info->args, info->envp) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do
		{
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

		get_path(info);

		handle_cmd(info);

	}
}

void print_error(shell_info_t *info,int fd, char *message, char *index){
	printf_(info->argv[0], fd);
	printf_(": ", fd);
	printf_(index, fd);
	printf_(": ", fd);
	printf_(info->args[0], fd);
	printf_(": ", fd);
	printf_(message, fd);
	printf_("\n", fd);
}

void handle_cmd(shell_info_t *info)
{
	if (info->fp == NULL)
	{
		print_error(info, STDERR_FILENO, "not found", "1");
		info->status = 127;
		free_last_command(info);
	}
	else
	{
		info->args[0] = info->fp;
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
	if (pInfo->args != NULL)
	{
		free(pInfo->args);
		pInfo->args = NULL;
	}

	if (pInfo->fp != NULL)
	{
		free(pInfo->fp);
		pInfo->fp = NULL;
	}
}
