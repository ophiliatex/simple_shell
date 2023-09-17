#include "shell.h"

/**
 * get_env_var - Gets an environment variable.
 * @info: The shell_info_t struct.
 * @var: The name of the environment variable.
 * Return: A pointer to a char.
 */
char *get_env_var(shell_info_t *info, char *var)
{
	node_t *node = info->env->head;
	while (node != NULL)
	{
		if (strncmp(node->data, var, strlen_(var)) == 0)
		{
			return node->data + strlen_(var) + 1;
		}
		node = node->next;
	}
	return NULL;
}

/**
 * set_env_var - Sets an environment variable.
 * @info: The shell_info_t struct.
 * @var: The name of the environment variable.
 * @value: The value of the environment variable.
 * Return: Nothing.
 */
void set_env(shell_info_t *info, char *var, char *value)
{
	node_t *node = info->env->head;

	while (node != NULL)
	{
		if (strncmp(node->data, var, strlen_(var)) == 0)
		{
			free(node->data);
			node->data =
					malloc(sizeof(char) * (strlen_(var) + strlen_(value) + 2));
			strcpy(node->data, var);
			strcat(node->data, "=");
			strcat(node->data, value);
			return;
		}
		node = node->next;
	}
	add_node(info->env, var);
	node = info->env->tail;
	free(node->data);
	node->data = NULL;
	node->data = malloc(sizeof(char) * (strlen_(var) + strlen_(value) + 2));
	strcpy(node->data, var);
	strcat(node->data, "=");
	strcat(node->data, value);
}

/**
 * unset_env_var - Unsets an environment variable.
 * @info: The shell_info_t struct.
 * @var: The name of the environment variable.
 * Return: Nothing.
 */
void unset_env(shell_info_t *info, char *var)
{
	node_t *node = info->env->head;
	node_t *tmp;

	while (node != NULL)
	{
		if (strncmp(node->data, var, strlen_(var)) == 0)
		{
			if (node == info->env->head)
			{
				info->env->head = node->next;
			}
			else
			{
				tmp->next = node->next;
			}
			free(node->data);
			free(node);
			return;
		}
		tmp = node;
		node = node->next;
	}
}

/**
 * print_env - Prints the environment variables.
 * @info: The shell_info_t struct.
 * Return: Nothing.
 */
void print_env(shell_info_t *info)
{
	node_t *node = info->env->head;

	while (node != NULL)
	{
		printf(node->data, STDOUT_FILENO);
		printf_("\n", STDOUT_FILENO);
		node = node->next;
	}
}

/**
 * handle_env - Handles the env built-in.
 * @info: The shell_info_t struct.
 * Return: 1 if handled, 0 if not.
 */
int handle_env(shell_info_t *info)
{
	int handled = 0;

	if (strcmp(info->args[0], "env") == 0)
	{
		print_env(info);
		if (isatty(STDIN_FILENO))
		{
			printf_("$ ", STDOUT_FILENO);
		}
		free(info->args);
		info->args = NULL;
		return 1;
	}

	if (strcmp(info->args[0], "setenv") == 0)
	{
		if (info->args[1] == NULL)
		{
			printf_("setenv: Too few arguments.\n", STDERR_FILENO);
			free(info->args);
			info->args = NULL;
			return 1;
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
		return 1;
	}

	if (strcmp(info->args[0], "unsetenv") == 0)
	{
		if (info->args[1] == NULL)
		{
			printf_("unsetenv: Too few arguments.\n", STDERR_FILENO);
			free(info->args);
			info->args = NULL;
			return 1;
		}
		unset_env(info, info->args[1]);
		if (isatty(STDIN_FILENO))
		{
			printf_("$ ", STDOUT_FILENO);
		}
		free(info->args);
		info->args = NULL;
		return 1;
	}

	return handled;
}
