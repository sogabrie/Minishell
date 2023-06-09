/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:02:47 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:02:48 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (str == NULL)
				malloc_error();
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
		if (new_dir == NULL && home != NULL)
			malloc_error();
		return (new_dir);
	}
	new_dir = ft_strdup(dir);
	if (new_dir == NULL)
		malloc_error();
	return (new_dir);
}

int	check_dir(char *dir)
{
	struct stat	filestat;

	if (stat(dir, &filestat) == 0)
	{
		if (!S_ISDIR(filestat.st_mode))
		{
			exe_error(dir, 20, " cd: ");
			return (1);
		}
		return (0);
	}
	return (0);
}
