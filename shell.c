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
	int i;
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
	info->fp = NULL;


	for (i = 0; env[i] != NULL; i++)
	{
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
		do {
			if (waitpid(pid, &info->status, WUNTRACED) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(info->status) && !WIFSIGNALED(info->status));
		info->status = WEXITSTATUS(info->status);
	}
}

/**
 * shell_loop - The shell loop.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 */
void shell_loop(shell_info_t *info)
{
	int built_in;

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


		built_in = handle_inbuilt(info);

		if (built_in == 1)
		{
			free_last_command(info);
			continue;
		}
		else if (built_in == 2)
		{
			free_last_command(info);
			break;
		}

		get_path(info);

		handle_cmd(info);
	}
}

/**
 * handle_cmd - Handles a command in a shell_info_t struct.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 * Description: Handles a command in a shell_info_t struct.
 */
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

