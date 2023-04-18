#include "minishell.h"
#include "struct.h"

int	chek_and_or(t_shell *my_shell, int *i, int j)
{
	if ((*i) > 0 && (my_shell->control[(*i) - 1]->command_type == LOGIC_AND || my_shell->control[(*i) - 1]->command_type == LOGIC_OR))
	{
		printf("bbbbbb\n");
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

int	do_exe(t_shell *my_shell, int i)
{
	pid_t	pid;
	int		error;
	// if (my_shell->control[i]->command_type == EXE)
	// {
	// 	chreat_process(my_shell, i);
	// 	printf("EXE = %s intpt = %d output = %d\n",my_shell->control[i]->exe->full_name, \
	// 	my_shell->control[i]->exe->fd_input, my_shell->control[i]->exe->fd_output);
	// 	int j = 0;
	// 	while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j])
	// 		printf("	Options = %s\n", my_shell->control[i]->exe->options[j++]);
	// }
	// else if (my_shell->control[i]->command_type == MY_EXE)
	// {
	// 	printf("MY_EXE = %s intpt = %d output = %d\n",my_shell->control[i]->my_exe->name, \
	// 	my_shell->control[i]->my_exe->fd_input, my_shell->control[i]->my_exe->fd_output);
	// 	int j = 0;
	// 	while (my_shell->control[i]->my_exe->options && my_shell->control[i]->my_exe->options[j])
	// 		printf("	Options = %s\n", my_shell->control[i]->my_exe->options[j++]);
	// }

	if (my_shell->control[i]->command_type == EXE)
	{
		// printf("my_shell->fd_input = %d my_shell->fd_output = %d\n", my_shell->fd_input, my_shell->fd_output);

		my_shell->control[i]->exe->cpy_fd_input = dup(my_shell->fd_input);
		dup2(my_shell->control[i]->exe->fd_input, my_shell->fd_input);
		my_shell->control[i]->exe->cpy_fd_output = dup(my_shell->fd_output);
		dup2(my_shell->control[i]->exe->fd_output, my_shell->fd_output);
		
		chreat_process(my_shell, i);
		pid = fork();
		if (pid)
		{
			// if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			// {
			// 	//write (2, "aaaa_2\n", 8);
			// 	close(my_shell->control[i - 1]->pip[0]);
			// }
			// dup2(my_shell->control[i]->exe->cpy_fd_input, my_shell->fd_input);
			// dup2(my_shell->control[i]->exe->cpy_fd_output, my_shell->fd_output);
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
				close(my_shell->control[i + 1]->pip[1]);
			}
			waitpid(pid, &error, 0);
			my_shell->my_error = error;
			dup2(my_shell->control[i]->exe->cpy_fd_input, my_shell->fd_input);
			close(my_shell->control[i]->exe->cpy_fd_input);
			dup2(my_shell->control[i]->exe->cpy_fd_output, my_shell->fd_output);
			close(my_shell->control[i]->exe->cpy_fd_output);

			// write (2, "aaaa_1\n", 8);
		}
		else
		{
			// my_shell->control[i]->exe->cpy_fd_input = dup(my_shell->fd_input);
			// dup2(my_shell->control[i]->exe->fd_input, my_shell->fd_input);
			// my_shell->control[i]->exe->cpy_fd_output = dup(my_shell->fd_output);
			// dup2(my_shell->control[i]->exe->fd_output, my_shell->fd_output);
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				close(my_shell->control[i - 1]->pip[0]);
			}	
			exit(execve(my_shell->control[i]->exe->full_name, my_shell->control[i]->exe->options, my_shell->my_envp));
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
	pid_t	pid;
	int		error;

	error = 0;
	while (i < j)
	{
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{
			if (chek_and_or(my_shell, &i, my_shell->control[i]->prioritet_start->end + 1))
				continue ;
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				my_shell->cpy_fd_input = dup(my_shell->fd_input);
				dup2(my_shell->control[i - 1]->pip[0], my_shell->fd_input);
			}
			if (my_shell->control[i]->prioritet_start->end + 1 < j && \
			my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
			{
				my_shell->cpy_fd_output = dup(my_shell->fd_output);
				dup2(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1], my_shell->fd_output);
			}
			pid = fork();
			if (pid)
			{
				if (i + 1 < my_shell->count && my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
				{
					close(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1]);
				}
				waitpid(pid, &error, 0);
				my_shell->my_error = error;
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
			if (chek_and_or(my_shell, &i, i + 1))
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
			my_shell->my_error = do_exe(my_shell, i);
		 }
		 ++i;
	}
	return(my_shell->my_error);
}
