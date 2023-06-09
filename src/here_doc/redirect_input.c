/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:42:19 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:42:20 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_input(char *filename)
{
	int	file;

	if (access(filename, F_OK))
	{
		write (2, "minishell: ", 11);
		write (2, filename, ft_strlen(filename));
		write (2, ": No such file or directory\n", 29);
	}
	else
	{
		if (access(filename, R_OK))
		{
			write (2, "minishell: ", 11);
			write (2, filename, ft_strlen(filename));
			write (2, ": Permission denied\n", 20);
		}
		else
		{
			file = open(filename, O_RDONLY);
			if (file >= 0)
				return (file);
			write (2, "Too many open files in system\n", 30);
		}
	}
	return (-1);
}
