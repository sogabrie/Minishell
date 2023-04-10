#include "minishell.h"

void	malloc_error(void)
{
	write(2, "Memory allocation error!!\n", 26);
	exit(1);
}

int	error_here_doc(void)
{
	write(1, "-minishell: syntax error: unexpected end of file\n", 49);
	return (-1);
}
