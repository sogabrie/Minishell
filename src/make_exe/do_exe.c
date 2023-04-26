/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:42:55 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 00:54:43 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exe_4_1(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	add_pid(my_pid);
	my_pid->pid[my_pid->count - 1] = fork();
	if (my_pid->pid[my_pid->count - 1] == -1)
		global_error(my_shell);
	if (my_pid->pid[my_pid->count - 1])
	{
		if (i + 1 < my_shell->count && my_shell->control[i \
		+ 1]->command_type == PIPE)
		{
			close(my_shell->control[i + 1]->pip[1]);
		}
	}
	else
	{
		if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
		{
			close(my_shell->control[i - 1]->pip[0]);
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (my_shell->control[i]->error == NO_ERROR)
			exit(execve(my_shell->control[i]->exe->full_name, \
			my_shell->control[i]->exe->options, my_shell->my_envp));
		exit(my_shell->control[i]->error);
	}
}

int	do_exe_4(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	if (chreat_process(my_shell, i))
	{
		write (2, "minishell: ", 12);
		write (2, my_shell->control[i]->exe->options[0], \
		ft_strlen(my_shell->control[i]->exe->options[0]));
		if (my_shell->control[i]->exe->error == 127)
			write (2, ": command not found\n", 21);
		else if (my_shell->control[i]->exe->error == 126)
			write (2, ": No such file or directory\n", 29);
		else
			write (2, ": Permission denied\n", 21);
		my_shell->error_status = 127;
		return (1);
	}
	do_exe_4_1(my_shell, my_pid, i);
	return (0);
}

void	do_exe_5_2(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	add_pid(my_pid);
	my_pid->pid[my_pid->count - 1] = fork();
	if (my_pid->pid[my_pid->count - 1] == -1)
		global_error(my_shell);
	if (my_pid->pid[my_pid->count - 1])
	{
		if (i + 1 < my_shell->count && \
		my_shell->control[i + 1]->command_type == PIPE)
			close(my_shell->control[i + 1]->pip[1]);
	}
	else
	{
		if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			close(my_shell->control[i - 1]->pip[0]);
		if (my_shell->control[i]->error == NO_ERROR)
			exit(do_my_exe(my_shell, i));
		exit(my_shell->control[i]->error);
	}
}

void	do_exe_5(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	if ((i + 1 < my_shell->count && \
	my_shell->control[i + 1]->command_type == PIPE) || \
	(i > 0 && my_shell->control[i - 1]->command_type == PIPE))
		do_exe_5_2(my_shell, my_pid, i);
	else
	{
		add_pid(my_pid);
		my_pid->my_pid[my_pid->count - 1] = do_my_exe(my_shell, i);
	}
}

void	do_exe(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	do_exe_2(my_shell, i);
	if (ft_strcmp(my_shell->control[i]->exe->full_name, "echo"))
		do_exe_3(my_shell, i);
	if (!control_type_exe(my_shell, i))
	{
		if (do_exe_4(my_shell, my_pid, i))
			return ;
	}
	else
		do_exe_5(my_shell, my_pid, i);
}
