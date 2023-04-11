#include "minishell.h"

char	*search_podh(char **envp, char *name, size_t count)
{
	size_t	i;
	char	*str;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(name, envp[i], count))
		{
			str = ft_strdup(envp[i] + count);
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	adding_dir(char **old_pwd, char **home, char **pwd, char ***envp)
{
	*old_pwd = search_podh(*envp, "OLDPWD=", 7);
	*home = search_podh(*envp, "HOME=", 5);
	*pwd = search_podh(*envp, "PWD=", 4);
}

char	*valid_dir(char *dir, char *home)
{
	char	*new_dir;

	if (dir[0] == '~')
	{
		new_dir = ft_strjoin(home, dir + 1);
		return (new_dir);
	}
	new_dir = ft_strdup(dir);
	return (new_dir);
}

int	check_dir(char *dir)
{
	DIR		*file;

	if (access(dir, F_OK) == 0)
	{
		file = opendir(dir);
		if (file == NULL)
		{
			cd_error(dir, 20);
			return (1);
		}
		closedir(file);
		return (0);
	}
	return (0);
}
