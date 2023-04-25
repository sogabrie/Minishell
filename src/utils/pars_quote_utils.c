#include "minishell.h"

char	*heer_doc_echo(char *a)
{
	int	i;

	if (!a || !a[0])
		return (a);
	if (a[0] == '\"' || a[0] == '\'')
	{
		i = -1;
		while (a[++i])
			a[i] = a[i + 1];
		a[i - 2] = 0;
	}
	return (a);
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
	if (!resul)
		malloc_error();
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

int	size_trepl_list(char ***list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list[i])
		++i;
	return (i);
}
