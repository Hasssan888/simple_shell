#include "shell.h"

/*
 * Code by - HASSAN BAKRIM, SOUFAIN CHANDAD
 */

/**
 * Code by - HASSAN BAKRIM, SOUFAIN HANDAD
 * main - this entry point
 * @arc: this argument count
 * @arv: this argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arc, char **arv)
{
	inf_y info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (arc == 2)
	{
		fd = open(arv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ft_errputs(arv[0]);
				ft_errputs(": 0: Can't open ");
				ft_errputs(arv[1]);
				ft_errputchar('\n');
				ft_errputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	ft_populate_env_list(info);
	ft_read_history(info);
	ft_hsh(info, arv);
	return (EXIT_SUCCESS);
}
