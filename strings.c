#include "shell.h"

/**
 * split_string - splits a string into words
 * @str: string to split
 * @delim: delimiter to split words by
 * Return: pointer to array of strings
 */
char **split_string(char *str, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";

	numwords = count_words(str, delim, numwords);
	if (numwords == 0)
	{
		return (NULL);
	}
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delim) == 1)
			i++;

		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);

			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 * is_delim - checks if character is a delimiter
 * @i: character to check
 * @delim: delimiter to check against
 * Return: 1 if true, 0 if false
 */
int is_delim(char i, const char *delim)
{
	int j = 0;

	while (delim[j] != '\0')
	{
		if (i == delim[j])
			return (1);
		j++;
	}
	return (0);
}

/**
 * count_words - count words in a string
 * @str: string to count words in
 * @delim: delimiter to split words by
 * @numwords: number of words
 * Return: number of words
 */
int count_words(const char *str, const char *delim, int numwords)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], delim) &&
			(is_delim(str[i + 1], delim) || !str[i + 1]))
		{
			numwords++;
		}
	}
	return (numwords);
}

/**
 * strncmp_ - compares two strings up to n bytes
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 * Return: 0 if equal, negative if s1 < s2, positive if s1 > s2
 */
int strncmp_(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	for (; i < n && s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	return (0);
}
