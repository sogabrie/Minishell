/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:42:30 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:42:31 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_out_check(char *filename)
{
	DIR	*chek_dir;

	if (!access(filename, F_OK))
	{
		if (access(filename, W_OK))
		{
			write (2, "minishell: ", 11);
			write (2, filename, ft_strlen(filename));
			write (2, ": Permission denied\n", 20);
			return (1);
		}
		chek_dir = opendir(filename);
		if (chek_dir)
		{
			write (2, "minishell: ", 11);
			write (2, filename, ft_strlen(filename));
			write (2, ": Is a directory\n", 17);
			closedir(chek_dir);
			return (1);
		}
	}
	return (0);
}

int	red_out(char *filename)
{
	int	file;

	if (red_out_check(filename))
		return (-1);
	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (file < 0)
	{
		write (2, "Too many open files in system\n", 30);
		return (-1);
	}
	return (file);
}
