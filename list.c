#include "shell.h"

list_t *init_list(void)
{
	list_t *list;

	list = malloc(sizeof(list_t));
	if (list == NULL)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

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

void add_node(list_t *list, char *data)
{
	node_t *node = malloc(sizeof(node_t));

	if (node == NULL)
		return;
	node->data = strdup(data);
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


char **list_to_array(list_t *list)
{
	char **array = malloc(sizeof(char *) * (list->size + 1));
	node_t *node = list->head;
	int i = 0;

	while (node != NULL)
	{
		array[i] = strdup(node->data);
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return array;
}
