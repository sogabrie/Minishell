/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_exe_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:43:04 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 16:14:12 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_exe_2_1_input(t_shell *my_shell, int *i, char **a, int *fd)
{
	(*fd) = red_input((*a));
	if ((*fd) >= 0)
	{
		my_shell->control[(*i)]->exe->flag_input = 0;
		my_shell->control[(*i)]->exe->fd_input = (*fd);
	}
	else
		my_shell->control[(*i)]->exe->error = 127;
}

void	make_exe_2_1_out(t_shell *my_shell, int *i, char **a, int *fd)
{
	(*fd) = red_out((*a));
	if ((*fd) >= 0)
	{
		my_shell->control[(*i)]->exe->flag_output = 0;
		my_shell->control[(*i)]->exe->fd_output = (*fd);
	}
	else
		my_shell->control[(*i)]->exe->error = 127;
}

void	make_exe_2_1_here_doc(t_shell *my_shell, int *i, char **a, int *fd)
{
	(*fd) = red_input((*a));
	if ((*fd) >= 0)
	{
		my_shell->control[(*i)]->exe->flag_input = 0;
		my_shell->control[(*i)]->exe->fd_input = (*fd);
	}
	else
		my_shell->control[(*i)]->exe->error = 127;
}

void	make_exe_2_1_out_append(t_shell *my_shell, int *i, char **a, int *fd)
{
	(*fd) = red_out_append((*a));
	if ((*fd) >= 0)
	{
		my_shell->control[(*i)]->exe->flag_output = 0;
		my_shell->control[(*i)]->exe->fd_output = (*fd);
	}
	else
		my_shell->control[(*i)]->exe->error = 127;
}

void	make_exe_2_2(t_shell *my_shell, char **a, int *i, int *re_co)
{
	(*a) = 0;
	if (my_shell->control[(*i)]->redirect[(*re_co)]->error == NO_ERROR)
	{
		(*a) = parse_line(my_shell->control[(*i)]->redirect[(*re_co)]->\
		filename, my_shell->my_envp, my_shell->error_status, 0);
		if (!(*a))
			(*a) = \
			ft_strdup(my_shell->control[(*i)]->redirect[(*re_co)]->filename);
	}
}
