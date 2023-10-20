#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strncpy - this function is copies a string
 * @dest: this destination string to be copied to
 * @src: this source string
 * @nbr: this amount of characters to be copied
 * Return: the concatenated string
 */
char *ft_strncpy(char *dest, char *src, int nbr)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < nbr - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < nbr)
	{
		b = a;
		while (b < nbr)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strncat - this function is concatenates two strings
 * @dest: this first string
 * @src: this second string
 * @nbr: this amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *ft_strncat(char *dest, char *src, int nbr)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < nbr)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < nbr)
		dest[a] = '\0';
	return (s);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strchr - this function is locates a character in a string
 * @str: the string to be parsed
 * @c: the character to look for
 * Return: (str) a pointer to the memory area s
 */
char *ft_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

