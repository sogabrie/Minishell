#include "minishell.h"

void	two_dimensional_mas(char ***str)
{
	size_t	i;

	i = 0;
	if (*str != NULL)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}

int	free_tmp_stars(char **stars, char **tmp_object_name, int exit)
{
	if (*tmp_object_name != NULL)
	{
		free(*tmp_object_name);
		*tmp_object_name = NULL;
	}
	two_dimensional_mas(&stars);
	return (exit);
}
