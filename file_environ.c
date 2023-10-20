#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_myenv - this function is prints the current environment
 * @info: this structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int ft_myenv(inf_y *info)
{
	ft_print_list_str(info->env);
	return (0);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_getenv - this function is gets the value of an environ variable
 * @info: this structure containing potential arguments. Used to maintain
 * @name: this env var name
 *
 * Return: the value
 */
char *ft_getenv(inf_y *info, const char *name)
{
	list_x *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = ft_starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_mysetenv - this funnction initialize a new environment variable,
 *             or modify an existing one
 * @info: this structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int ft_mysetenv(inf_y *info)
{
	if (info->argc != 3)
	{
		ft_errputs("Incorrect number of arguements\n");
		return (1);
	}
	if (ft_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_myunsetenv - this function remove an environment variable
 * @info: this structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int ft_myunsetenv(inf_y *info)
{
	int a;

	if (info->argc == 1)
	{
		ft_errputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		ft_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_populate_env_list - this function ia populates env linked list
 * @info: this structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int ft_populate_env_list(inf_y *info)
{
	list_x *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		ft_add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}

