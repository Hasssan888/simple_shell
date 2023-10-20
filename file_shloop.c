#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_hsh - main shell loop
 * @arv: the argument vector from main()
 * @info: the parameter & return info struct
 *
 * Return: 0 on success, 1 on error, or error code
 */
int ft_hsh(inf_y *info, char **arv)
{
	ssize_t ret = 0;
	int builtin_r = 0;

	while (ret != -1 && builtin_r != -2)
	{
		ft_clear_info(info);
		if (ft_interactive(info))
			ft_puts("$ ");
		ft_errputchar(BUF_FLUSH);
		ret = ft_get_input(info);
		if (ret != -1)
		{
			ft_set_info(info, arv);
			builtin_r = ft_find_builtin(info);
			if (builtin_r == -1)
				ft_find_cmd(info);
		}
		else if (ft_interactive(info))
			ft_putchar('\n');
		ft_free_info(info, 0);
	}
	ft_write_history(info);
	ft_free_info(info, 1);
	if (!ft_interactive(info) && info->status)
		exit(info->status);
	if (builtin_r == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_r);
}

/**
 * ft_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int ft_find_builtin(inf_y *info)
{
	int j, built_in_r = -1;
	builtin_table builtintbl[] = {
		{"exit", ft_myexit},
		{"env", ft_myenv},
		{"help", ft_myhelp},
		{"history", ft_myhistory},
		{"setenv", ft_mysetenv},
		{"unsetenv", ft_myunsetenv},
		{"cd", ft_mycd},
		{"alias", ft_myalias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (ft_strcmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			built_in_r = builtintbl[j].func(info);
			break;
		}
	return (built_in_r);
}

/**
 * ft_find_cmd - this function is finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void ft_find_cmd(inf_y *info)
{
	char *path = NULL;
	int a, b;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!ft_is_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = ft_find_path(info, ft_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		ft_fork_cmd(info);
	}
	else
	{
		if ((ft_interactive(info) || ft_getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && ft_is_cmd(info, info->argv[0]))
			ft_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			ft_print_error(info, "not found\n");
		}
	}
}

/**
 * ft_fork_cmd - this function is forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void ft_fork_cmd(inf_y *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, ft_get_environ(info)) == -1)
		{
			ft_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				ft_print_error(info, "Permission denied\n");
		}
	}
}

