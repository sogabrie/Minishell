#include "minishell.h"

void	malloc_error(void)
{
	write(2, "Memory allocation error!!\n", 26);
	exit(1);
}

int	error_here_doc(void)
{
	write(2, "-minishell: syntax error: unexpected end of file\n", 49);
	return (-1);
}

void	cd_error(char *dir, int number)
{
	char	*error;

	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(dir, 2);
	error = strerror(number);
	write(2, ": ", 2);
	ft_putendl_fd(error, 2);
}
