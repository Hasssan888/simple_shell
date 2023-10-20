#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * ft_input_buf - this functin buffers chained commands
 * @info: this parameter struct
 * @buff: this address of buffer
 * @l: this address of len var
 *
 * Return: bytes read
 */
ssize_t ft_input_buf(inf_y *info, char **buff, size_t *l)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*l)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, ft_sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = ft_getline(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			ft_remove_comments(*buff);
			ft_build_history_list(info, *buff, info->histcount++);
			{
				*l = r;
				info->cmd_buf = buff;
			}
		}
	}
	return (r);
}

/**
 * ft_get_input - this function is gets a line minus the newline
 * @info: this parameter struct
 *
 * Return: bytes read
 */
ssize_t ft_get_input(inf_y *info)
{
	static char *buff;
	static size_t a, b, l;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	ft_putchar(BUF_FLUSH);
	r = ft_input_buf(info, &buff, &l);
	if (r == -1)
		return (-1);
	if (l)
	{
		b = a;
		p = buff + a;

		ft_check_chain(info, buff, &b, a, l);
		while (b < l)
		{
			if (ft_is_chain(info, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= l)
		{
			a = l = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (ft_strlen(p));
	}

	*buf_p = buff;
	return (r);
}

/**
 * ft_read_buf - this function is reads a buffer
 * @info: this parameter struct
 * @buf: this buffer
 * @size: this size
 * Return: r
 */
ssize_t ft_read_buf(inf_y *info, char *buf, size_t *size)
{
	ssize_t g = 0;

	if (*size)
		return (0);
	g = read(info->readfd, buf, READ_BUF_SIZE);
	if (g >= 0)
		*size = g;
	return (g);
}

/**
 * ft_getline - this function gets the next line of input from STDIN
 * @info: this parameter struct
 * @ptr: this address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int ft_getline(inf_y *info, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, l;
	size_t b;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && len)
		s = *len;
	if (a == l)
		a = l = 0;

	r = ft_read_buf(info, buf, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = ft_strchr(buf + a, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : l;
	new_p = ft_realloc(p, s, s ? s + b : b + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		ft_strncat(new_p, buf + a, b - a);
	else
		ft_strncpy(new_p, buf + a, b - a + 1);

	s += b - a;
	a = b;
	p = new_p;

	if (len)
		*len = s;
	*ptr = p;
	return (s);
}

/**
 * ft_sigintHandler - this function is blocks ctrl-C
 * @sig_num: this signal number
 *
 * Return: void
 */
void ft_sigintHandler(__attribute__((unused))int sig_num)
{
	ft_puts("\n");
	ft_puts("$ ");
	ft_putchar(BUF_FLUSH);
}

