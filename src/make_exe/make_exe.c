#include "minishell.h"
#include "struct.h"

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


int	chek_and_or(t_shell *my_shell, t_mas_pid *my_pid, int *i, int j)
{
	int	i2;
	int	error;

	i2 = 0;
	if ((*i) > 0 && (my_shell->control[(*i) - 1]->command_type == LOGIC_AND || my_shell->control[(*i) - 1]->command_type == LOGIC_OR))
	{
		// printf("end_2 = %d\n", my_shell->my_error);
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
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_AND)
		{
			if (my_shell->error_status)
			{
				(*i) = j;
				// my_shell->my_error = NO_ERROR;
				return (1);
			}
		}
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_OR)
		{
			if (!my_shell->error_status)
			{
				(*i) = j;
				// my_shell->my_error = NO_ERROR;
				return (1);
			}
		}
	}
	return (0);
}

int	do_my_exe(t_shell *my_shell, int i)
{
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "echo"))
	{
		return(ft_echo(my_shell->control[i]->exe->options, my_shell->my_envp, my_shell->error_status, -1));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "cd"))
	{
		return (ft_cd(my_shell->control[i]->exe->options[0], &my_shell->my_envp, NULL, NULL));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "pwd"))
	{
		return(ft_pwd());
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "export"))
	{
		return(ft_export(my_shell->control[i]->exe->options, &my_shell->my_envp, -1, NULL));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "unset"))
	{

	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "env"))
	{
		return(ft_env(my_shell->my_envp, 0));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "exit"))
	{

	}
	return (0);
}

void	do_exe(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	int	error;

	// write(2,"ttttt_1\n", 9);
	my_shell->control[i]->exe->cpy_fd_input = dup(my_shell->fd_input);
	dup2(my_shell->control[i]->exe->fd_input, my_shell->fd_input);
	my_shell->control[i]->exe->cpy_fd_output = dup(my_shell->fd_output);
	dup2(my_shell->control[i]->exe->fd_output, my_shell->fd_output);
	// write(2,"ttttt_2\n", 9);

	my_shell->control[i]->exe->full_name = echo_line(my_shell->control[i]->exe->full_name, my_shell->my_envp, NULL, my_shell->my_error);
	if (!control_type_exe(my_shell, i))
	{
		// write(2,"ttttt_3\n", 9);
		if (chreat_process(my_shell, i))
		{
			// write(2,"ttttt_4\n", 9);
			write (2, "minishell: ", 12);
			write (2, my_shell->control[i]->exe->options[0], ft_strlen(my_shell->control[i]->exe->options[0]));
			write (2, ": command not found\n", 21);
			my_shell->error_status = 127;
		}
		// write(2,"ttttt_5\n", 9);
		add_pid(my_pid);
		my_pid->pid[my_pid->count - 1] = fork();
		if (my_pid->pid[my_pid->count - 1])
		{
			// write(2,"ttttt_6\n", 9);
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
				close(my_shell->control[i + 1]->pip[1]);
			}
			// waitpid(pid, &error, 0);
			// my_shell->my_error = error;
		}
		else
		{
			// write(2,"ttttt_7\n", 9);
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				close(my_shell->control[i - 1]->pip[0]);
			}
			if (my_shell->control[i]->error == NO_ERROR)
				exit(execve(my_shell->control[i]->exe->full_name, my_shell->control[i]->exe->options, my_shell->my_envp));
			exit(my_shell->control[i]->error);
		}
		// write(2,"ttttt_8\n", 9);
	}
	else //if (my_shell->control[i]->command_type == MY_EXE)
	{
		// write(2,"ttttt_9\n", 9);
		if ((i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE) || \
		(i > 0 && my_shell->control[i - 1]->command_type == PIPE))
		{		
			add_pid(my_pid);
			my_pid->pid[my_pid->count - 1] = fork();
			if (my_pid->pid[my_pid->count - 1])
			{
				if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
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
				if (my_shell->control[i]->error == NO_ERROR)
					exit(do_my_exe(my_shell, i));
				exit(my_shell->control[i]->error);
			}
		}
		else
		{
			add_pid(my_pid);
			my_pid->my_pid[my_pid->count - 1] = do_my_exe(my_shell, i);
		}
		// write(2,"tttt_10\n", 9);
	}
	// write(2,"tttt_11\n", 9);
}

int	make_exe(t_shell *my_shell, int i, int j)
{
	t_mas_pid	my_pid;
	int			error;
	int			i2;

	error = 0;
	my_pid.count = 0;
	my_pid.pid = 0;
	my_pid.my_pid = 0;
	// write(2,"bbbbb_1\n", 9);
	while (i < j)
	{
		// write(2,"bbbbb_2\n", 9);
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{
			if (chek_and_or(my_shell, &my_pid, &i, my_shell->control[i]->prioritet_start->end + 1))
				continue ;
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				my_shell->cpy_fd_input = dup(my_shell->fd_input);
				dup2(my_shell->control[i - 1]->pip[0], my_shell->fd_input);
			}
			if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
			my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
			{
				my_shell->cpy_fd_output = dup(my_shell->fd_output);
				dup2(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1], my_shell->fd_output);
			}
			add_pid(&my_pid);
			my_pid.pid[my_pid.count - 1] = fork();
			if (my_pid.pid[my_pid.count - 1])
			{
				i2 = i;
				while (i2 < my_shell->control[i]->prioritet_start->end)
				{
					if (my_shell->control[i2]->command_type == PIPE)
					{
						close(my_shell->control[i2]->pip[0]);
						close(my_shell->control[i2]->pip[1]);
					}
					++i2;
				}
				if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
				my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
				{
					close(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1]);
				}
				// waitpid(pid, &error, 0);
				// my_shell->my_error = error;
				if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
				{
					dup2(my_shell->cpy_fd_input, my_shell->fd_input);
					close(my_shell->cpy_fd_input);
				}
				if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
				my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
				{
					dup2(my_shell->cpy_fd_output, my_shell->fd_output);
					close(my_shell->cpy_fd_output);
				}
				i = my_shell->control[i]->prioritet_start->end;
			}
			else
			{
				if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
				{
					close(my_shell->control[i - 1]->pip[0]);
				}
				exit(make_exe(my_shell, i + 1, my_shell->control[i]->prioritet_start->end + 1));
			}
		 }
		 else if (my_shell->control[i]->command_type == EXE)
		 {
			// if (my_shell->control[i]->exe->)
			// write(2,"bbbbb_3\n", 9);
			if (chek_and_or(my_shell, &my_pid, &i, i + 1))
				continue ;
			// write(2,"ccccc_1\n", 9);
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				// if (my_shell->control[i]->command_type == EXE)
				// {
					if (my_shell->control[i]->exe->flag_input)
						my_shell->control[i]->exe->fd_input = my_shell->control[i - 1]->pip[0];
				// }
				// else if (my_shell->control[i]->command_type == MY_EXE)
				// {
				// 	if (my_shell->control[i]->my_exe->flag_input)
				// 		my_shell->control[i]->my_exe->fd_input = my_shell->control[i - 1]->pip[0];
				// }
			}
			// write(2,"ccccc_2\n", 9);
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
				// if (my_shell->control[i]->command_type == EXE)
				// {
					if (my_shell->control[i]->exe->flag_output)
						my_shell->control[i]->exe->fd_output = my_shell->control[i + 1]->pip[1];
				// }
				// else if (my_shell->control[i]->command_type == MY_EXE)
				// {
				// 	if (my_shell->control[i]->my_exe->flag_output)
				// 		my_shell->control[i]->my_exe->fd_output = my_shell->control[i + 1]->pip[1];
				// }
			}
			// write(2,"ccccc_3\n", 9);
			do_exe(my_shell, &my_pid, i);
			// if (my_shell->control[i]->command_type == EXE)
			// {
				dup2(my_shell->control[i]->exe->cpy_fd_input, my_shell->fd_input);
				close(my_shell->control[i]->exe->cpy_fd_input);
				dup2(my_shell->control[i]->exe->cpy_fd_output, my_shell->fd_output);
				close(my_shell->control[i]->exe->cpy_fd_output);
			// }
			// if (my_shell->control[i]->command_type == MY_EXE)
			// {
			// 	dup2(my_shell->control[i]->my_exe->cpy_fd_input, my_shell->fd_input);
			// 	close(my_shell->control[i]->my_exe->cpy_fd_input);
			// 	dup2(my_shell->control[i]->my_exe->cpy_fd_output, my_shell->fd_output);
			// 	close(my_shell->control[i]->my_exe->cpy_fd_output);
			// }
			// write(2,"ccccc_4\n", 9);
		 }
		//  write(2,"bbbbb_4\n", 9);
		 ++i;
	}
	i2 = 0;
	while (i2 < my_pid.count)
	{
		if (my_pid.my_pid[i2] == -1)
		{
			waitpid(my_pid.pid[i2], &error, 0);
			my_shell->error_status = error;
		}
		else
			my_shell->error_status = my_pid.my_pid[i2];
		// printf("my_shell->error_status = %d\n", my_shell->error_status);
		++i2;
	}
	free(my_pid.pid);
	free(my_pid.my_pid);
	my_pid.count = 0;
	my_pid.pid = 0;
	my_pid.my_pid = 0;
	return(my_shell->error_status);
}
