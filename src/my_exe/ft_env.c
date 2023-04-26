/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:11 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:04:12 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp, int i, int j, int f_h)
{
	while (envp[++i])
	{
		j = 0;
		printf("declare -x ");
		while (envp[i][j] && envp[i][j] != '=')
			printf("%c", envp[i][j++]);
		if (!envp[i][j])
		{
			printf("\n");
			continue ;
		}
		printf("=\"");
		while (envp[i][++j])
			printf("%c", envp[i][j]);
		printf("\"\n");
	}
}

int	ft_env(char **envp, int f_export)
{
	size_t	i;

	i = 0;
	if (f_export == 0)
	{
		while (envp[i])
		{
			if (ft_strchr(envp[i], '='))
				printf("%s\n", envp[i]);
			i++;
		}
		return (0);
	}
	print_export(envp, -1, -1, 0);
	return (0);
}
