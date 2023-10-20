#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_list_len - this function calcule length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t ft_list_len(const list_x *head)
{
	size_t len = 0;

	while (head)
	{
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * ft_list_to_strings - this function returns
 *  an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **ft_list_to_strings(list_x *head)
{
	list_x *node = head;
	size_t a = ft_list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(ft_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = ft_strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * ft_print_list - this function disply all elements of a list_x linked list
 * @head: this pointer to first node
 *
 * Return: size of list
 */
size_t ft_print_list(const list_x *head)
{
	size_t a = 0;

	while (head)
	{
		ft_puts(ft_convert_number(head->num, 10, 0));
		ft_putchar(':');
		ft_putchar(' ');
		ft_puts(head->str ? head->str : "(nil)");
		ft_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * ft_node_starts_with - this function is
 *  returns node whose string starts with prefix
 * @node: this pointer to list head
 * @prefix: this string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_x *ft_node_starts_with(list_x *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = ft_starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * ft_get_node_index - this function is gets the index of a node
 * @head: this pointer to list head
 * @node: this pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t ft_get_node_index(list_x *head, list_x *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}

