#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_add_node - this function is adds a node to the start of the list
 * @head: this address of pointer to head node
 * @str: this string field of node
 * @nbr: this node index used by history
 *
 * Return: size of list
 */
list_x *ft_add_node(list_x **head, const char *str, int nbr)
{
	list_x *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_x));
	if (!new_head)
		return (NULL);
	ft_memset((void *)new_head, 0, sizeof(list_x));
	new_head->num = nbr;
	if (str)
	{
		new_head->str = ft_strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * ft_add_node_end - this function is adds a node to the end of the list
 * @head: this address of pointer to head node
 * @str: this string field of node
 * @nbr: this node index used by history
 *
 * Return: size of list
 */
list_x *ft_add_node_end(list_x **head, const char *str, int nbr)
{
	list_x *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_x));
	if (!new_node)
		return (NULL);
	ft_memset((void *)new_node, 0, sizeof(list_x));
	new_node->num = nbr;
	if (str)
	{
		new_node->str = ft_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * ft_print_list_str - this function display
 *   only the str element of a list_t linked list
 * @head: this pointer to first node
 *
 * Return: size of list
 */
size_t ft_print_list_str(const list_x *head)
{
	size_t a = 0;

	while (head)
	{
		ft_puts(head->str ? head->str : "(nil)");
		ft_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * ft_delete_node_at_index - this function deletes node at given index
 * @head: this address of pointer to first node
 * @index: this index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int ft_delete_node_at_index(list_x **head, unsigned int index)
{
	list_x *node, *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * ft_free_list - this function frees all nodes of a list
 * @head_ptr: this address of pointer to head node
 *
 * Return: void
 */
void ft_free_list(list_x **head_ptr)
{
	list_x *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

