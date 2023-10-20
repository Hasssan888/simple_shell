#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_get_history_file - this function is gets the history file
 * @info: this parameter struct
 *
 * Return: allocated string containg history file
 */

char *ft_get_history_file(inf_y *info)
{
	char *buff, *dir;

	dir = ft_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	ft_strcpy(buff, dir);
	ft_strcat(buff, "/");
	ft_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_write_history - this function creates a file,
 *   or appends to an existing file
 * @info: this parameter struct
 *
 * Return: 1 on success, else -1
 */
int ft_write_history(inf_y *info)
{
	ssize_t fd;
	char *file_name = ft_get_history_file(info);
	list_x *node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		ft_putsfd(node->str, fd);
		ft_putfd('\n', fd);
	}
	ft_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_read_history - this function is reads history from file
 * @info: this parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int ft_read_history(inf_y *info)
{
	int a, last = 0, count_len = 0;
	ssize_t fd, rd_len, f_size = 0;
	struct stat st;
	char *buff = NULL, *file_name = ft_get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	rd_len = read(fd, buff, f_size);
	buff[f_size] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(fd);
	for (a = 0; a < f_size; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			ft_build_history_list(info, buff + last, count_len++);
			last = a + 1;
		}
	if (last != a)
		ft_build_history_list(info, buff + last, count_len++);
	free(buff);
	info->histcount = count_len;
	while (info->histcount-- >= HIST_MAX)
		ft_delete_node_at_index(&(info->history), 0);
	ft_renumber_history(info);
	return (info->histcount);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_build_history_list - this function adds entry to a history linked list
 * @info: this structure containing potential arguments. Used to maintain
 * @buff: this buffer
 * @count_len: the history linecount, histcount
 *
 * Return: Always 0
 */
int ft_build_history_list(inf_y *info, char *buff, int count_len)
{
	list_x *node = NULL;

	if (info->history)
		node = info->history;
	ft_add_node_end(&node, buff, count_len);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * ft_renumber_history - this function renumbers
 * the history linked list after changes
 * @info: this structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int ft_renumber_history(inf_y *info)
{
	list_x *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
