#include "minishell.h"

void	malloc_error(void)
{
	write(2, "Memory allocation error!!\n", 26);
	exit(1);
}

char	*error_here_doc(int fd_write)
{
	write(2, "-minishell: syntax error: unexpected end of file\n", 49);
	return (NULL);
}
