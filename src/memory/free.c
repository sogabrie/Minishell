/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:41 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 01:18:31 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_error(void)
{
	write (2, "minishell: pipe: Resource ", 27);
	write (2, "temporarily unavailable\n", 25);
	return (1);
}

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

int	free_object_cd(char *new_dir, char *home, char *old_pwd, char *pwd)
{
	free(new_dir);
	free(home);
	free(old_pwd);
	free(pwd);
	return (0);
}

char	*free_return(char *str, char *new_line)
{
	free(str);
	return (new_line);
}
