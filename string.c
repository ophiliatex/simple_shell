#include "shell.h"

/**
 * strlen_ - Gets the length of a string.
 * @str: The string.
 * Return: The length of the string.
 */
int strlen_(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * strcmp_ - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: The difference between the strings.
 */
int strcmp_(const char *s1, const char *s2)
{
	int i = 0;

	for (; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else if (s1[i] == '\0')
		return (-1);
	else
		return (1);
}

/**
 * strcat_ - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 * Return: The destination string.
 */
char *strcat_(char *dest, const char *src)
{
	char *ptr = dest + strlen_(dest);

	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}

/**
 * strcpy_ - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 * Return: The destination string.
 */
char *strcpy_(char *dest, const char *src)
{
	int i = 0;

	for (; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * strdup_ - Duplicates a string.
 * @s: The string.
 * Return: The duplicated string.
 */
char *strdup_(const char *s)
{
	char *d = malloc(strlen_(s) + 1);

	if (d == NULL)
		return (NULL);
	strcpy_(d, s);
	return (d);
}

/*
 * char *itoa_(int num)
{
	int temp = num;
	int numDigits = 1;
	int isNegative = 0;

	if (num < 0)
	{
		isNegative = 1;
		temp = -temp;
	}

	while (temp >= 10)
	{
		temp /= 10;
		numDigits++;
	}

	int totalDigits =
			numDigits + isNegative + 1;
	char *str = (char *) malloc(totalDigits * sizeof(char));

	if (str == NULL)
	{
		return (NULL);
	}
	temp = num;
	if (isNegative)
	{
		str[0] = '-';
		temp = -temp;
	}

	int i = numDigits + isNegative - 1;

	while (temp >= 10)
	{
		int digit = temp % 10;

		str[i] = digit + '0';
		temp /= 10;
		i--;
	}

	str[i] = temp + '0';
	str[numDigits + isNegative] = '\0';

	return (str);
}
 */
