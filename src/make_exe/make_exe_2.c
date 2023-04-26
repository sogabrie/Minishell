/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_exe_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:42:59 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:43:00 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_exe_1_1(t_shell *my_shell, t_mas_pid	*my_pid, int *i)
{
	if ((*i) > 0 && my_shell->control[(*i) - 1]->command_type == PIPE)
	{
		my_shell->cpy_fd_input = dup(my_shell->fd_input);
		dup2(my_shell->control[(*i) - 1]->pip[0], my_shell->fd_input);
	}
	if (my_shell->control[(*i)]->prioritet_start->end + 1 < my_shell->count && \
	my_shell->control[my_shell->control[(*i)]->prioritet_start->end \
	+ 1]->command_type == PIPE)
	{
		my_shell->cpy_fd_output = dup(my_shell->fd_output);
		dup2(my_shell->control[my_shell->control[(*i)]->prioritet_start->end \
		+ 1]->pip[1], my_shell->fd_output);
	}
	add_pid(my_pid);
}

void	make_exe_1_2_2(t_shell *my_shell, t_mas_pid	*my_pid, int *i)
{
	if (my_shell->control[(*i)]->prioritet_start->end + 1 < my_shell->count && \
	my_shell->control[my_shell->control[(*i)]->prioritet_start->end + \
	1]->command_type == PIPE)
		close(my_shell->control[my_shell->control[(*i)]->prioritet_start->end \
		+ 1]->pip[1]);
	if ((*i) > 0 && my_shell->control[(*i) - 1]->command_type == PIPE)
	{
		dup2(my_shell->cpy_fd_input, my_shell->fd_input);
		close(my_shell->cpy_fd_input);
	}
	if (my_shell->control[(*i)]->prioritet_start->end + 1 < my_shell->count && \
	my_shell->control[my_shell->control[(*i)]->prioritet_start->end + \
	1]->command_type == PIPE)
	{
		dup2(my_shell->cpy_fd_output, my_shell->fd_output);
		close(my_shell->cpy_fd_output);
	}
}

void	make_exe_1_2(t_shell *my_shell, t_mas_pid	*my_pid, int *i, int i2)
{
	i2 = (*i);
	while (i2 < my_shell->control[(*i)]->prioritet_start->end)
	{
		if (my_shell->control[i2]->command_type == PIPE)
		{
			close(my_shell->control[i2]->pip[0]);
			close(my_shell->control[i2]->pip[1]);
		}
		++i2;
	}
	make_exe_1_2_2(my_shell, my_pid, i);
}

void	make_exe_1(t_shell *my_shell, t_mas_pid	*my_pid, int *i)
{
	if (chek_and_or(my_shell, my_pid, i, \
	my_shell->control[(*i)]->prioritet_start->end + 1))
		return ;
	make_exe_1_1(my_shell, my_pid, i);
	my_pid->pid[my_pid->count - 1] = fork();
	if (my_pid->pid[my_pid->count - 1])
	{
		make_exe_1_2(my_shell, my_pid, i, 0);
		(*i) = my_shell->control[(*i)]->prioritet_start->end;
	}
	else
	{
		if ((*i) > 0 && my_shell->control[(*i) - 1]->command_type == PIPE)
			close(my_shell->control[(*i) - 1]->pip[0]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exit(make_exe(my_shell, (*i) + 1, \
		my_shell->control[(*i)]->prioritet_start->end + 1));
	}
}
