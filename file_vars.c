#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_is_chain - this function istest
 *  if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ft_is_chain(inf_y *info, char *buff, size_t *ptr)
{
	size_t i = *ptr;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[i] == ';')
	{
		buff[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_check_chain - this functio checks
 *   we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @a: starting position in buf
 * @l: length of buf
 *
 * Return: Void
 */
void ft_check_chain(inf_y *info, char *buff, size_t *ptr, size_t a, size_t l)
{
	size_t b = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[a] = 0;
			b = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[a] = 0;
			b = l;
		}
	}

	*ptr = b;
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_replace_alias - this functin is
 *   replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ft_replace_alias(inf_y *info)
{
	int a;
	list_x *node;
	char *ptr;

	for (a = 0; a < 10; a++)
	{
		node = ft_node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = ft_strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = ft_strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_replace_vars - this function is replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ft_replace_vars(inf_y *info)
{
	int a = 0;
	list_x *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!ft_strcmp(info->argv[a], "$?"))
		{
			ft_replace_string(&(info->argv[a]),
					ft_strdup(ft_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!ft_strcmp(info->argv[a], "$$"))
		{
			ft_replace_string(&(info->argv[a]),
					ft_strdup(ft_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = ft_node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			ft_replace_string(&(info->argv[a]),
					ft_strdup(ft_strchr(node->str, '=') + 1));
			continue;
		}
		ft_replace_string(&info->argv[a], ft_strdup(""));

	}
	return (0);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_replace_string - this function is replaces string
 * @old_str: this  address of old string
 * @new_str: this new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ft_replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

