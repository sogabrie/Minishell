/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:42:42 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 20:31:05 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_pars_exe(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	sigquit_pars_exe(int sig)
{
	write(1, "Quit: 3\n", 9);
	(void)sig;
}

int	control_type_exe(t_shell *my_shell, int i)
{
	if ((!ft_strcmp(my_shell->control[i]->exe->full_name, "echo") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "cd") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "pwd") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "export") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "unset") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "env") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "exit")))
		return (1);
	return (0);
}

void	chek_and_or_2(t_shell *my_shell, t_mas_pid *my_pid)
{
	int	i2;
	int	error;

	i2 = 0;
	while (i2 < my_pid->count)
	{
		if (my_pid->my_pid[i2] == -1)
		{
			waitpid(my_pid->pid[i2], &error, 0);
			my_shell->error_status = error;
		}
		else
			my_shell->error_status = my_pid->my_pid[i2];
		++i2;
	}
	free(my_pid->pid);
	free(my_pid->my_pid);
	my_pid->count = 0;
	my_pid->pid = 0;
	my_pid->my_pid = 0;
}

int	chek_and_or(t_shell *my_shell, t_mas_pid *my_pid, int *i, int j)
{
	if ((*i) > 0 && (my_shell->control[(*i) - 1]->command_type == LOGIC_AND \
	|| my_shell->control[(*i) - 1]->command_type == LOGIC_OR))
	{
		chek_and_or_2(my_shell, my_pid);
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_AND)
		{
			if (my_shell->error_status)
			{
				(*i) = j;
				return (1);
			}
		}
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_OR)
		{
			if (!my_shell->error_status)
			{
				(*i) = j;
				return (1);
			}
		}
	}
	return (0);
}
