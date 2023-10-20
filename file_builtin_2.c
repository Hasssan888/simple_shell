#include "shell.h"

/**
 * ft_myhistory - this function displays the history list,
 * one command by line, precededwith line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int ft_myhistory(inf_y *info)
{
	ft_print_list(info->history);
	return (0);
}

/**
 * ft_unset_alias - this function is sets alias to string
 * @info: this parameter struct
 * @str: this string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int ft_unset_alias(inf_y *info, char *str)
{
	char *ptr, c;
	int r;

	ptr = ft_strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	r = ft_delete_node_at_index(&(info->alias),
			ft_get_node_index(info->alias, ft_node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (r);
}

/**
 * ft_set_alias - this function is sets alias to string
 * @info: this parameter struct
 * @str: this string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int ft_set_alias(inf_y *info, char *str)
{
	char *ptr;

	ptr = ft_strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (ft_unset_alias(info, str));
	ft_unset_alias(info, str);
	return (ft_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * ft_print_alias - this function prints an alias string
 * @node: this alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int ft_print_alias(list_x *node)
{
	char *pt = NULL, *a = NULL;

	if (node)
	{
		pt = ft_strchr(node->str, '=');
		for (a = node->str; a <= pt; a++)
			ft_putchar(*a);
		ft_putchar('\'');
		ft_puts(pt + 1);
		ft_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * ft_myalias - this function is mimics the alias builtin (man alias)
 * @info: this structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int ft_myalias(inf_y *info)
{
	int a = 0;
	char *pt = NULL;
	list_x *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			ft_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		pt = ft_strchr(info->argv[a], '=');
		if (pt)
			ft_set_alias(info, info->argv[a]);
		else
			ft_print_alias(ft_node_starts_with(info->alias, info->argv[a], '='));
	}
	return (0);
}
