#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strlen - this function is returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int ft_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (str[length])
		length++;
	return (length);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strcmp - this function performs lexicogarphic comparison of two strangs.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2,
 *  positive if str1 > str2, zero if str1 == str2
 */
int ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_starts_with - this function is checks if needle starts with haystack
 * @hstack: string to search
 * @need: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *ft_starts_with(const char *hstack, const char *need)
{
	while (*need)
		if (*need++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strcat - this function concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *ft_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}

