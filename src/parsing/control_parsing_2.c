/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_parsing_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:43:43 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:43:44 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "minishell.h"

int	control_pars_exe_2(t_shell *my_shell, int *start, int *end, int *i)
{
	int	j;

	j = 0;
	if ((!ft_strcmp(my_shell->double_list[(*i)], "<") || \
	!ft_strcmp(my_shell->double_list[(*i)], "<<") || \
	!ft_strcmp(my_shell->double_list[(*i)], ">") || \
	!ft_strcmp(my_shell->double_list[(*i)], ">>")))
		j = creat_redirect(my_shell, i);
	else if (i == start || my_shell->check_exe == -1)
		creat_exe(my_shell, i);
	else if (ft_strcmp(my_shell->double_list[(*i)], " "))
		add_option(my_shell, i);
	++(*i);
	return (j);
}

void	control_pars_exe_1(t_shell *my_shell, int *start, int *end, int *i)
{
	while (!ft_strcmp(my_shell->double_list[*start], " ") || \
	!ft_strcmp(my_shell->double_list[*start], "("))
	{
		if (!ft_strcmp(my_shell->double_list[*start], "("))
			creat_struct_prioritet_start(my_shell);
		++(*start);
	}
	(*i) = (*start);
}

void	control_pars_exe_3(t_shell *my_shell, int *end, int *i)
{
	while ((*i) < (*end) && my_shell->double_list[(*i)] && \
	(!ft_strcmp(my_shell->double_list[(*i)], " ") || \
	!ft_strcmp(my_shell->double_list[(*i)], ")")))
	{
		if (!ft_strcmp(my_shell->double_list[(*i)], ")"))
			creat_struct_prioritet_end(my_shell);
		++(*i);
	}
}

void	control_pars_exe_4(t_shell *my_shell)
{
	my_shell->control[my_shell->check_exe]->redirect = my_shell->redirect;
	my_shell->control[my_shell->check_exe]->count_redir = my_shell->count_redir;
	my_shell->count_redir = 0;
	my_shell->redirect = 0;
	my_shell->control[my_shell->check_exe]->error = my_shell->my_error;
}

void	control_pars_exe_5(t_shell *my_shell)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = NO_EXE;
	my_shell->check_exe = my_shell->count - 1 ;
	my_shell->control[my_shell->check_exe]->redirect = my_shell->redirect;
	my_shell->control[my_shell->check_exe]->count_redir = my_shell->count_redir;
	my_shell->count_redir = 0;
	my_shell->redirect = 0;
	my_shell->control[my_shell->check_exe]->error = my_shell->my_error;
}
