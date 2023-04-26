/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:44:15 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:44:16 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

void	creat_delimiter_cont(t_shell *my_shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (my_shell->double_list[i])
	{
		if (!ft_strcmp(my_shell->double_list[i], "&&") || \
		!ft_strcmp(my_shell->double_list[i], "||") || \
		!ft_strcmp(my_shell->double_list[i], "|"))
		{
			my_shell->delimiter[j] = i;
			++j;
		}
		++i;
	}
}

int	creat_delimiter(t_shell	*my_shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (my_shell->double_list[i])
	{
		if (!ft_strcmp(my_shell->double_list[i], "&&") || \
		!ft_strcmp(my_shell->double_list[i], "||") || \
		!ft_strcmp(my_shell->double_list[i], "|"))
			++j;
		++i;
	}
	my_shell->delimiter = ft_calloc(j, sizeof(int));
	if (!my_shell->delimiter)
		return (7);
	my_shell->delimiter_count = j;
	creat_delimiter_cont(my_shell);
	return (0);
}
