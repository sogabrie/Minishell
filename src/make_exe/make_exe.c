#include "minishell.h"
#include "struct.h"

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
			waitpid(my_pid->pid[i2++], &error, 0);
			my_shell->my_error = error;
		}
		free(my_pid->pid);
		my_pid->count = 0;
		my_pid->pid = 0;
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_AND)
		{
			if (my_shell->my_error)
			{
				(*i) = j;
				my_shell->my_error = NO_ERROR;
				return (1);
			}
		}
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_OR)
		{
			if (!my_shell->my_error)
			{
				(*i) = j;
				my_shell->my_error = NO_ERROR;
				return (1);
			}
		}
	}
	return (0);
}

int	do_exe(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	int	error;

	if (my_shell->control[i]->command_type == EXE)
	{
		// printf("my_shell->fd_input = %d my_shell->fd_output = %d\n", my_shell->fd_input,my_shell->fd_output);
		// printf("my_shell->fd_input = %d my_shell->fd_output = %d\n", my_shell->control[i]->exe->fd_input, my_shell->control[i]->exe->fd_output);
		my_shell->control[i]->exe->cpy_fd_input = dup(my_shell->fd_input);
		dup2(my_shell->control[i]->exe->fd_input, my_shell->fd_input);
		my_shell->control[i]->exe->cpy_fd_output = dup(my_shell->fd_output);
		dup2(my_shell->control[i]->exe->fd_output, my_shell->fd_output);
		if (chreat_process(my_shell, i))
		{
			write (2, "minishell: ", 12);
			write (2, my_shell->control[i]->exe->options[0], ft_strlen(my_shell->control[i]->exe->options[0]));
			write (2, ": command not found\n", 21);
			my_shell->my_error = 127;
		}
		add_pid(my_pid);
		my_pid->pid[my_pid->count - 1] = fork();
		if (my_pid->pid[my_pid->count - 1])
		{
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
				close(my_shell->control[i + 1]->pip[1]);
			}
			// waitpid(pid, &error, 0);
			// my_shell->my_error = error;
		}
		else
		{
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				close(my_shell->control[i - 1]->pip[0]);
			}
			if (my_shell->control[i]->error == NO_ERROR)
				exit(execve(my_shell->control[i]->exe->full_name, my_shell->control[i]->exe->options, my_shell->my_envp));
			exit(my_shell->control[i - 1]->command_type);
		}
	}
	else if (my_shell->control[i]->command_type == MY_EXE)
	{
		printf("MY_EXE = %s intpt = %d output = %d\n",my_shell->control[i]->my_exe->name, \
		my_shell->control[i]->my_exe->fd_input, my_shell->control[i]->my_exe->fd_output);
		int j = 0;
		while (my_shell->control[i]->my_exe->options && my_shell->control[i]->my_exe->options[j])
			printf("	Options = %s\n", my_shell->control[i]->my_exe->options[j++]);
	}

	// if (my_shell->control[i]->command_type == MY_EXE)
	// {
	// 	printf("my_exe go\n");
	// 	return (0);
	// }
	// else
	// {
		
	// }
	return (0);
}

int	make_exe(t_shell *my_shell, int i, int j)
{
	t_mas_pid	my_pid;
	int			error;
	int			i2;

	error = 0;
	my_pid.count = 0;
	my_pid.pid = 0;
	while (i < j)
	{
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
		 else if (my_shell->control[i]->command_type == EXE || my_shell->control[i]->command_type == MY_EXE)
		 {
			if (chek_and_or(my_shell, &my_pid, &i, i + 1))
				continue ;
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				if (my_shell->control[i]->command_type == EXE)
				{
					my_shell->control[i]->exe->fd_input = my_shell->control[i - 1]->pip[0];
				}
				else if (my_shell->control[i]->command_type == MY_EXE)
				{
					my_shell->control[i]->my_exe->fd_input = my_shell->control[i - 1]->pip[0];
				}
			}
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
				if (my_shell->control[i]->command_type == EXE)
				{
					my_shell->control[i]->exe->fd_output = my_shell->control[i + 1]->pip[1];
				}
				else if (my_shell->control[i]->command_type == MY_EXE)
				{
					my_shell->control[i]->my_exe->fd_output = my_shell->control[i + 1]->pip[1];
				}
			}
			do_exe(my_shell, &my_pid, i);
			dup2(my_shell->control[i]->exe->cpy_fd_input, my_shell->fd_input);
			close(my_shell->control[i]->exe->cpy_fd_input);
			dup2(my_shell->control[i]->exe->cpy_fd_output, my_shell->fd_output);
			close(my_shell->control[i]->exe->cpy_fd_output);
		 }
		 ++i;
	}
	i2 = 0;
	while (i2 < my_pid.count)
	{
		waitpid(my_pid.pid[i2++], &error, 0);
		my_shell->my_error = error;
	}
	free(my_pid.pid);
	my_pid.count = 0;
	my_pid.pid = 0;
	return(my_shell->my_error);
}
