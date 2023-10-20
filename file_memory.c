#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_bfree - this function frees a pointer and NULLs the address
 * @p: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int ft_bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

