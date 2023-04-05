#include "minishell.h"

int	check_my_exe(char *name)
{
	if (!ft_strcmp(name, "echo") \
		|| !ft_strcmp(name, "cd") \
		|| !ft_strcmp(name, "pwd") \
		|| !ft_strcmp(name, "export") \
		|| !ft_strcmp(name, "unset") \
		|| !ft_strcmp(name, "env") \
		|| !ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

int	check_redirect(char *name)
{
	if (!ft_strcmp(name, "<") \
		|| !ft_strcmp(name, ">") \
		|| !ft_strcmp(name, "<<") \
		|| !ft_strcmp(name, ">>"))
		return (1);
	return (0);
}

int	check_end(char *name)
{
	if (!ft_strcmp(name, "&&") \
		|| !ft_strcmp(name, "||") \
		|| !ft_strcmp(name, "|"))
		return (1);
	return (0);
}