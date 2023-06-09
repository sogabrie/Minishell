/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:04:31 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delete_variable(char **envp, char *str, char **new_envp, size_t j)
{
	size_t	i;

	i = 0;
	if (check_exists(envp, str))
		return (envp);
	while (envp[i])
		i++;
	new_envp = ft_calloc(i, sizeof(char *));
	if (new_envp == NULL)
		malloc_error();
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], ft_strlen(str))
			&& ft_strlen(str) == ft_strlen(envp[i]))
			i++;
		else
		{
			new_envp[j] = ft_strdup(envp[i++]);
			if (new_envp[j++] == NULL)
				malloc_error();
		}
	}
	two_dimensional_mas(&envp);
	return (new_envp);
}

int	ft_unset(char **args, char ***envp)
{
	int		i;
	int		error_code;

	error_code = 0;
	i = -1;
	if (args == NULL || args[0] == NULL
		|| envp == NULL || envp[0] == NULL)
		return (error_code);
	while (args[++i])
	{
		if (args[i][0] == '#')
			break ;
		if (valid_unset(args[i], &error_code, *envp, 1))
		{
			error_code = 1;
			continue ;
		}
		*envp = delete_variable(*envp, args[i], NULL, 0);
		error_code = 0;
	}
	return (error_code);
}
