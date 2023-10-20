#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
*/


/**
 * ft_interactive - this function returns true if shell is interactive mode
 * @info: this struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int ft_interactive(inf_y *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * ft_is_delim - this function checks if character is a delimeter
 * @c: this char to check
 * @delim: this delimeter string
 * Return: 1 if true, 0 if false
 */
int ft_is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * ft_isalpha - this function is checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * ft_atoi - this function converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int ft_atoi(char *str)
{
	int a, sign = 1, flag = 0, out;
	unsigned int r = 0;

	for (a = 0; str[a] != '\0' && flag != 2; a++)
	{
		if (str[a] == '-')
			sign *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			flag = 1;
			r *= 10;
			r += (str[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out = -r;
	else
		out = r;

	return (out);
}

