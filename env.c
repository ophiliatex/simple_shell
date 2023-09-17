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
		if (strncmp_(node->data, var, strlen_(var)) == 0)
		{
			return (node->data + strlen_(var) + 1);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Sets an environment variable.
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
		if (strncmp_(node->data, var, strlen_(var)) == 0)
		{
			free(node->data);
			node->data =
					malloc(sizeof(char) * (strlen_(var) + strlen_(value) + 2));
			strcpy_(node->data, var);
			strcat_(node->data, "=");
			strcat_(node->data, value);
			return;
		}
		node = node->next;
	}
	add_node(info->env, var);
	node = info->env->tail;
	free(node->data);
	node->data = NULL;
	node->data = malloc(sizeof(char) * (strlen_(var) + strlen_(value) + 2));
	strcpy_(node->data, var);
	strcat_(node->data, "=");
	strcat_(node->data, value);
}

/**
 * unset_env - Unsets an environment variable.
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
		if (strncmp_(node->data, var, strlen_(var)) == 0)
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
		printf_(node->data, STDOUT_FILENO);
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

	if (handle_print_env(info) == 1)
		return (1);

	if (handle_set_env(info) == 1)
		return (1);

	if (handle_unset_env(info) == 1)
		return (1);

	return (handled);
}
