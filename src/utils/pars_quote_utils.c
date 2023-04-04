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

void	cp_free(char ***list, char ***cp)
{
	int	i;

	i = 0;
	while ((*list) && (*list)[i])
	{
		(*cp)[i] = (*list)[i];
		++i;
	}
	free(*list);
	*list = *cp;
	*cp = 0;
}

char	*my_cat(char *list, int start, int end)
{
	char	*resul;
	int		i;

	i = 0;
	resul = malloc((end - start + 1) * sizeof(char));
	while (start < end)
	{
		resul[i] = list[start];
		++i;
		++start;
	}
	resul[i] = 0;
	return (resul);
}

int	size_list(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list[i])
		++i;
	return (i);
}