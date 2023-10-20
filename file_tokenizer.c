#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_strtow - this function is splits a string into words.
 *  Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **ft_strtow(char *str, char *del)
{
	int a, b, c, d, count_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!ft_is_delim(str[a], del) &&
				(ft_is_delim(str[a + 1], del) || !str[a + 1]))
			count_words++;

	if (count_words == 0)
		return (NULL);
	s = malloc((1 + count_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < count_words; b++)
	{
		while (ft_is_delim(str[a], del))
			a++;
		c = 0;
		while (!ft_is_delim(str[a + c], del) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * ft_strtow2 - this function is splits a string into words
 * @str: the input string
 * @del: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **ft_strtow2(char *str, char del)
{
	int a, b, c, d, count_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != del && str[a + 1] == del) ||
				(str[a] != del && !str[a + 1]) || str[a + 1] == del)
			count_words++;
	if (count_words == 0)
		return (NULL);
	s = malloc((1 + count_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < count_words; b++)
	{
		while (str[a] == del && str[a] != del)
			a++;
		c = 0;
		while (str[a + c] != del && str[a + c] && str[a + c] != del)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

