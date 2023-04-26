/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:43:20 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:43:21 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "minishell.h"

void	free_struct_2_2(t_shell *my_shell, int *i, int *j)
{
	free(my_shell->control[(*i)]->redirect);
	if (my_shell->control[(*i)]->command_type == EXE)
		free(my_shell->control[(*i)]->exe->full_name);
	(*j) = 0;
	while (my_shell->control[(*i)]->command_type == EXE && \
	my_shell->control[(*i)]->exe->options && \
	my_shell->control[(*i)]->exe->options[(*j)])
		free(my_shell->control[(*i)]->exe->options[(*j)++]);
	if (my_shell->control[(*i)]->command_type == EXE)
	{
		free(my_shell->control[(*i)]->exe->options);
		free(my_shell->control[(*i)]->exe);
	}
}

void	free_struct_2(t_shell *my_shell, int *i, int *j)
{
	int	i2;

	i2 = 0;
	if (my_shell->control[(*i)]->command_type == EXE || \
	my_shell->control[(*i)]->command_type == NO_EXE)
	{
		while (i2 < my_shell->control[(*i)]->count_redir)
		{
			free(my_shell->control[(*i)]->redirect[i2]->filename);
			free(my_shell->control[(*i)]->redirect[i2++]);
		}
		free_struct_2_2(my_shell, i, j);
	}
	if (my_shell->control[(*i)]->command_type == PRIORITET_START)
		free(my_shell->control[(*i)]->prioritet_start);
	if (my_shell->control[(*i)]->command_type == PRIORITET_END)
		free(my_shell->control[(*i)]->prioritet_end);
	free(my_shell->control[(*i)++]);
}

void	free_struct_3(t_shell *my_shell)
{
	int	i;

	i = 0;
	while (i < my_shell->close_fd_count)
		close(my_shell->close_fd[i++]);
	free(my_shell->line);
	free(my_shell->double_list);
	free(my_shell->delimiter);
	free(my_shell->control);
	free(my_shell->full_path);
	free(my_shell->close_fd);
	my_shell->line = 0;
	my_shell->control = 0;
	my_shell->delimiter_count = 0;
	my_shell->full_path = 0;
	my_shell->delimiter = 0;
	my_shell->double_list = 0;
	my_shell->check_exe = -1;
	my_shell->close_fd = 0;
	my_shell->close_fd_count = 0;
	my_shell->count = 0;
	my_shell->my_error = NO_ERROR;
	my_shell->count_redir = 0;
	my_shell->redirect = 0;
}

void	free_struct(t_shell *my_shell)
{
	int	i;
	int	j;

	i = 0;
	del_tmp_files(my_shell->start_here_doc, \
	my_shell->full_name_here_doc, NULL, NULL);
	my_shell->start_here_doc_plus = my_shell->start_here_doc;
	while (i < my_shell->count)
		free_struct_2(my_shell, &i, &j);
	i = 0;
	while (my_shell->double_list && my_shell->double_list[i])
	{
		free(my_shell->double_list[i]);
		++i;
	}
	i = 0;
	while (my_shell->full_path && my_shell->full_path[i])
	{
		free(my_shell->full_path[i]);
		++i;
	}
	free_struct_3(my_shell);
}
