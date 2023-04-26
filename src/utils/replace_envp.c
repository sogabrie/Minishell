/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:03:21 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:03:22 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lvl_check(char *envp, int *flag_z)
{
	int	lvl;
	int	i_atoi;

	i_atoi = ft_atoi(envp + 6);
	if (i_atoi < 0)
		return (0);
	lvl = i_atoi + 1;
	if (lvl == 1000)
	{
		lvl = 0;
		*flag_z = 1;
	}
	if (lvl > 1000)
	{
		printf("minishell: warning: shell level");
		printf("(%d) too high, resetting to 1\n", lvl);
		lvl = 1;
	}
	return (lvl);
}

char	*update_shlvl(char *envp, int lvl, int flag_z, int *flag_shlvl)
{
	char	*shlvl;
	char	*new_envp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	*flag_shlvl = 1;
	lvl = lvl_check(envp, &flag_z);
	shlvl = ft_itoa(lvl);
	if (shlvl == NULL)
		malloc_error();
	new_envp = malloc(sizeof(char) * (ft_strlen(shlvl) + 7));
	if (new_envp == NULL)
		malloc_error();
	while (envp[i] != '=')
		new_envp[j++] = envp[i++];
	i = 0;
	new_envp[j++] = '=';
	while (shlvl[i] != '\0' && flag_z != 1)
		new_envp[j++] = shlvl[i++];
	new_envp[j] = '\0';
	free(shlvl);
	return (new_envp);
}

void	new_fill_envp(int flag_shlvl, char **new_envp, char **envp, size_t i)
{
	char	buf[256];

	if (flag_shlvl == 0)
	{
		new_envp[i] = ft_strdup("SHLVL=1");
		if (new_envp[i++] == NULL)
			malloc_error();
	}
	if (!search_envp_in(envp, "PWD", 3))
	{
		new_envp[i] = ft_strjoin("PWD=", getcwd(buf, sizeof(buf)));
		if (new_envp[i++] == NULL)
			malloc_error();
	}
	new_envp[i] = ft_strdup("OLDPWD");
	if (new_envp[i++] == NULL)
		malloc_error();
	new_envp[i] = NULL;
}

char	**fill_envp(char **envp, char **new_envp, size_t j, size_t i)
{
	int		flag_shlvl;

	flag_shlvl = 0;
	while (envp[++j])
	{
		if (!ft_strncmp("SHLVL=", envp[j], 6))
			new_envp[i++] = update_shlvl(envp[j], 0, 0, &flag_shlvl);
		else
		{
			if (ft_strncmp("OLDPWD=", envp[j], 7)
				&& ft_strncmp("OLDPWD", envp[j], 6))
			{
				new_envp[i] = ft_strdup(envp[j]);
				if (new_envp[i++] == NULL)
					malloc_error();
			}
		}
	}
	new_fill_envp(flag_shlvl, new_envp, envp, i);
	return (new_envp);
}

char	**replace_envp(char **envp)
{
	char		**new_envp;
	size_t		count;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 4));
	if (new_envp == NULL)
		malloc_error();
	new_envp = fill_envp(envp, new_envp, -1, 0);
	return (new_envp);
}
