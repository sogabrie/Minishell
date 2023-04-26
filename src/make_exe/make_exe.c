/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:43:11 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:43:12 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_exe_2_1_1(t_shell *my_shell, int *i, int re_co, int fd)
{
	char	*a;

	make_exe_2_2(my_shell, &a, i, &re_co);
	if (my_shell->control[(*i)]->redirect[re_co]->type == INPUT && \
	my_shell->control[(*i)]->redirect[re_co]->error == NO_ERROR)
		make_exe_2_1_input(my_shell, i, &a, &fd);
	else if (my_shell->control[(*i)]->redirect[re_co]->type == OUTPT \
	&& my_shell->control[(*i)]->redirect[re_co]->error == NO_ERROR)
		make_exe_2_1_out(my_shell, i, &a, &fd);
	else if (my_shell->control[(*i)]->redirect[re_co]->type == \
	HERE_DOC && my_shell->control[(*i)]->redirect[re_co]->error == NO_ERROR)
		make_exe_2_1_here_doc(my_shell, i, &a, &fd);
	else if (my_shell->control[(*i)]->redirect[re_co]->type == \
	OUTPUT_APP && my_shell->control[(*i)]->redirect[re_co]->error == \
	NO_ERROR)
		make_exe_2_1_out_append(my_shell, i, &a, &fd);
	else if (my_shell->control[(*i)]->redirect[re_co]->error != NO_ERROR)
	{
		my_shell->control[(*i)]->exe->error = \
		my_shell->control[(*i)]->redirect[re_co]->error;
	}
	free(a);
	creat_close_fd(my_shell, fd);
}

void	make_exe_2_1(t_shell *my_shell, int *i)
{
	int			re_co;
	int			fd;
	char		*a;

	re_co = 0;
	while (re_co < my_shell->control[(*i)]->count_redir && \
	my_shell->control[(*i)]->exe->error == NO_ERROR)
	{
		make_exe_2_1_1(my_shell, i, re_co, 0);
		++re_co;
	}
}

void	make_exe_2(t_shell *my_shell, t_mas_pid	*my_pid, int *i)
{
	make_exe_2_1(my_shell, i);
	if (chek_and_or(my_shell, my_pid, i, (*i) + 1))
		return ;
	if ((*i) > 0 && my_shell->control[(*i) - 1]->command_type == PIPE)
	{
		if (my_shell->control[(*i)]->exe->flag_input)
			my_shell->control[(*i)]->exe->fd_input = \
			my_shell->control[(*i) - 1]->pip[0];
	}
	if ((*i) + 1 < my_shell->count && \
	my_shell->control[(*i) + 1]->command_type == PIPE)
	{
		if (my_shell->control[(*i)]->exe->flag_output)
			my_shell->control[(*i)]->exe->fd_output = \
			my_shell->control[(*i) + 1]->pip[1];
	}
	if (my_shell->control[(*i)]->exe->error == NO_ERROR)
	{
		do_exe(my_shell, my_pid, (*i));
		dup2(my_shell->control[(*i)]->exe->cpy_fd_input, my_shell->fd_input);
		close(my_shell->control[(*i)]->exe->cpy_fd_input);
		dup2(my_shell->control[(*i)]->exe->cpy_fd_output, my_shell->fd_output);
		close(my_shell->control[(*i)]->exe->cpy_fd_output);
	}
}

int	make_exe(t_shell *my_shell, int i, int j)
{
	t_mas_pid	my_pid;

	my_pid.count = 0;
	my_pid.pid = 0;
	my_pid.my_pid = 0;
	while (i < j)
	{
		if (my_shell->control[i]->command_type == PRIORITET_START)
			make_exe_1(my_shell, &my_pid, &i);
		else if (my_shell->control[i]->command_type == EXE)
			make_exe_2(my_shell, &my_pid, &i);
		++i;
	}
	chek_and_or_2(my_shell, &my_pid);
	return (my_shell->error_status);
}
