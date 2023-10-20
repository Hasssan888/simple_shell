#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_get_environ - this function returns the string array copy of our environ
 * @info: this structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **ft_get_environ(inf_y *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = ft_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * ft_unsetenv - this function is remove an environment variable
 * @info: this structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int ft_unsetenv(inf_y *info, char *var)
{
	list_x *node = info->env;
	size_t a = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = ft_starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = ft_delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * ft_setenv - this function initialize a new environment variable,
 *             or modify an existing one
 * @info: this structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: this string env var property
 * @value: this string env var value
 *  Return: Always 0
 */
int ft_setenv(inf_y *info, char *var, char *value)
{
	char *buff = NULL;
	list_x *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buff = malloc(ft_strlen(var) + ft_strlen(value) + 2);
	if (!buff)
		return (1);
	ft_strcpy(buff, var);
	ft_strcat(buff, "=");
	ft_strcat(buff, value);
	node = info->env;
	while (node)
	{
		ptr = ft_starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	ft_add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

