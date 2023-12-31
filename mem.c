#include "shell.h"

/**
 * memcpy_ - Copies n bytes from memory area src to memory area dest.
 * @dest: The destination memory area.
 * @src: The source memory area.
 * @n: The number of bytes to copy.
 * Return: A pointer to dest.
 */
void *memcpy_(void *dest, const void *src, size_t n)
{
	char *csrc = (char *) src;
	char *cdest = (char *) dest;
	size_t i;

	for (i = 0; i < n; i++)
	{
		cdest[i] = csrc[i];
	}
	return (dest);
}

/**
 * realloc_char_ptr - Reallocates a pointer to a pointer to a char.
 * @ptr: The pointer to a pointer to a char.
 * @newSize: The new size of the pointer.
 * Return: A pointer to the new pointer.
 */
char **realloc_char_ptr(char **ptr, size_t newSize)
{
	if (ptr == NULL)
	{
		return ((char **) malloc(newSize));
	}
	else
	{
		char **newPtr = (char **) malloc(newSize);
		size_t copySize = newSize - (1 * sizeof(char *));

		if (newPtr == NULL)
		{
			return (NULL);
		}

		if (copySize > newSize)
		{
			copySize = newSize;
		}
		memcpy_(newPtr, ptr, copySize);
		free(ptr);
		return (newPtr);
	}
}

/**
 * realloc_ - Reallocates a pointer.
 * @ptr: The pointer.
 * @newSize: The new size of the pointer.
 * @oldSize: The old size of the pointer.
 * Return: A pointer to the new pointer.
 */
char *realloc_(char *ptr, size_t newSize, size_t oldSize)
{
	char *p;

	if (ptr == NULL)
		return (malloc(newSize));
	if (newSize <= 0)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	p = malloc(newSize);

	if (!p)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;

	while (oldSize--)
		p[oldSize] = ((char *) ptr)[oldSize];
	free(ptr);
	return (p);
}

/**
 * free_char_ptr - Frees a pointer to a pointer to a char.
 * @ptr: The pointer to a pointer to a char.
 * Return: Nothing.
 */
void free_char_ptr(char **ptr)
{
	char **a = ptr;

	if (!ptr)
		return;
	while (*ptr)
	{
		char *tmp = *ptr;

		free(tmp);
		ptr++;
	}

	free(a);
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
