#include "shell.h"

/**
 * init_list - initializes a list
 * Return: the list
 */
list_t *init_list(void)
{
	list_t *list;

	list = malloc(sizeof(list_t));
	if (list == NULL)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

/**
 * free_list - frees a list
 * @list: the list to free
 * Return: nothing
 */
void free_list(list_t *list)
{
	node_t *node = list->head;
	node_t *tmp;

	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp->data);
		free(tmp);
	}
	free(list);
}

/**
 * add_node - adds a node to a list
 * @list: the list to add to
 * @data: the data to add
 * Return: nothing
 */
void add_node(list_t *list, char *data)
{
	node_t *node = malloc(sizeof(node_t));

	if (node == NULL)
		return;
	node->data = strdup_(data);
	node->next = NULL;
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

/**
 * list_to_array - converts a list to an array
 * @list: the list to convert
 * Return: the array
 */
char **list_to_array(list_t *list)
{
	char **array = malloc(sizeof(char *) * (list->size + 1));
	node_t *node = list->head;
	int i = 0;

	while (node != NULL)
	{
		array[i] = strdup_(node->data);
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
