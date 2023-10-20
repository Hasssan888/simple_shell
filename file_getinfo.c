#include "shell.h"

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_clear_info - this function is initializes info_t struct
 * @info: this struct address
 */
void ft_clear_info(inf_y *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_set_info - this is initializes info_t struct
 * @info: this struct address
 * @av: this argument vector
 */
void ft_set_info(inf_y *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = ft_strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = ft_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		ft_replace_alias(info);
		ft_replace_vars(info);
	}
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_free_info - this function is frees info_t struct fields
 * @info: this struct address
 * @all: this true if freeing all fields
 */
void ft_free_info(inf_y *info, int all)
{
	ft_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			ft_free_list(&(info->env));
		if (info->history)
			ft_free_list(&(info->history));
		if (info->alias)
			ft_free_list(&(info->alias));
		ft_ffree(info->environ);
		info->environ = NULL;
		ft_bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		ft_putchar(BUF_FLUSH);
	}
}

