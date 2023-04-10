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

void	free_object_cd(char *new_dir, char *home, char *old_pwd, char *pwd)
{
	if (new_dir != NULL)
		free(new_dir);
	free(home);
	free(old_pwd);
	free(pwd);
}

void	free_dir(char **envp, char *dir, char *old_pwd)
{
	if(dir != NULL && dir != old_pwd)
		free(dir);
	two_dimensional_mas(&envp);
}
