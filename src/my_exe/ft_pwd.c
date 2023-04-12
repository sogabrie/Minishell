#include "minishell.h"

int	ft_pwd(void)
{
	char	buf[256];

	if ((getcwd(buf, sizeof(buf)) != NULL))
	{
		ft_putendl_fd(buf, 1);
		return (0);
	}
	write(2, "minishell: pwd: syntax error: expected ')'\n", 43);
	return (-1);
}
