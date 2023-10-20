#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strcpy - this function is copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *ft_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_strdup - fubction is duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *ft_strdup(const char *str)
{
	int len = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--str;
	return (r);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_puts - this function is prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void ft_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_putchar - this function writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int ft_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

