#include "struct.h"
#include "minishell.h"

int	free_mas(char **mas)
{
	free(*mas);
	*mas = 0;
	return (0);
}

char	**get_path(char **avp)
{
	char	**new_path;
	char	*path;
	int		i;

	i = 0;
	while (avp[i])
	{
		if (!ft_strncmp("PATH", avp[i], 4))
			break ;
		else
			++i;
	}
	path = ft_strdup(avp[i]);
	path[3] = '.';
	path[4] = ':';
	new_path = ft_split(path + 3, ':');
	free_mas(&path);
	if (new_path)
		return (new_path);
	return ((void *)0);
}

long	check_valid_procces(char **mas, char **pro, int i)
{
	if (!access(*mas, 1))
	{
		if (!i)
			return (0);
		free(*pro);
		*pro = *mas;
		return (0);
	}
	return (1);
}

long	check_procces(char **pro, char **path, int size, int size_p)
{
	int		i;
	char	*mas;

	i = 0;
	mas = *pro;
	while (path[i])
	{
		if (!check_valid_procces(&mas, pro, i))
			return (0);
		if (mas != *pro)
			free(mas);
		size_p = ft_strlen(*pro);
		size = ft_strlen(path[i]);
		mas = ft_calloc(size + size_p + 2, sizeof(char));
		if (!mas)
			return (1);
		ft_strlcat(mas, path[i], size + 1);
		ft_strlcat(mas, "/", size + 2);
		ft_strlcat(mas, *pro, size + size_p + 2);
		++i;
	}
	free_mas(&mas);
	return (1);
}