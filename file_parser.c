#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_is_cmd - this function is determines if a file is an executable command
 * @info: this info struct
 * @path: this path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int ft_is_cmd(inf_y *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * ft_dup_chars - this function is duplicates characters
 * @path_str: this PATH string
 * @star: this starting index
 * @end: this stopping index
 *
 * Return: pointer to new buffer
 */
char *ft_dup_chars(char *path_str, int star, int end)
{
	static char buff[1024];
	int a = 0, b = 0;

	for (b = 0, a = star; a < end; a++)
		if (path_str[a] != ':')
			buff[b++] = path_str[a];
	buff[b] = 0;
	return (buff);
}

/**
 * ft_find_path - this function is finds this cmd in the PATH string
 * @info: this info struct
 * @path_str: this PATH string
 * @cmd: this cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *ft_find_path(inf_y *info, char *path_str, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((ft_strlen(cmd) > 2) && ft_starts_with(cmd, "./"))
	{
		if (ft_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[a] || path_str[a] == ':')
		{
			path = ft_dup_chars(path_str, curr_pos, a);
			if (!*path)
				ft_strcat(path, cmd);
			else
			{
				ft_strcat(path, "/");
				ft_strcat(path, cmd);
			}
			if (ft_is_cmd(info, path))
				return (path);
			if (!path_str[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}

