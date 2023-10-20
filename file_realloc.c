#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_memset - this function is fills memory with a constant byte
 * @p: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (p) a pointer to the memory area s
 */
char *ft_memset(char *p, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		p[a] = b;
	return (p);
}

/**
 * ft_ffree - this function is frees a string of strings
 * @pp_str: string of strings
 */
void ft_ffree(char **pp_str)
{
	char **strs = pp_str;

	if (!pp_str)
		return;
	while (*pp_str)
		free(*pp_str++);
	free(strs);
}

/**
 * ft_realloc - this function reallocates a block of memory
 * @ptr1: this pointer to previous malloc'ated block
 * @old_size: this byte size of previous block
 * @new_size: this byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *ft_realloc(void *ptr1, unsigned int old_size, unsigned int new_size)
{
	char *ptr2;

	if (!ptr1)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr1), NULL);
	if (new_size == old_size)
		return (ptr1);

	ptr2 = malloc(new_size);
	if (!ptr2)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		ptr2[old_size] = ((char *)ptr1)[old_size];
	free(ptr1);
	return (ptr2);
}

