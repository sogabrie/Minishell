#include "minishell.h"

void	malloc_error(void)
{
	write(1, "Memory allocation error!!\n", 26);
	exit(1);
}

int	error_here_doc(int fd_write)
{
	write(1, "-minishell: syntax error: unexpected end of file\n", 49);
	return (fd_write);
}
