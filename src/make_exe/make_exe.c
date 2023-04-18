#include "minishell.h"
#include "struct.h"

int	chek_and_or(t_shell *my_shell, int *i, int j)
{
	if ((*i) > 0 && (my_shell->control[(*i) - 1]->command_type == LOGIC_AND || my_shell->control[(*i) - 1]->command_type == LOGIC_OR))
	{
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
	if (my_shell->control[i]->command_type == EXE)
	{
		printf("EXE = %s intpt = %d output = %d\n",my_shell->control[i]->exe->full_name, \
		my_shell->control[i]->exe->fd_input, my_shell->control[i]->exe->fd_output);
		int j = 0;
		while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j])
			printf("	Options = %s\n", my_shell->control[i]->exe->options[j++]);
	}
	else if (my_shell->control[i]->command_type == MY_EXE)
	{
		printf("MY_EXE = %s intpt = %d output = %d\n",my_shell->control[i]->my_exe->name, \
		my_shell->control[i]->my_exe->fd_input, my_shell->control[i]->my_exe->fd_output);
		int j = 0;
		while (my_shell->control[i]->my_exe->options && my_shell->control[i]->my_exe->options[j])
			printf("	Options = %s\n", my_shell->control[i]->my_exe->options[j++]);
	}
	return (0);
}

int	make_exe(t_shell *my_shell, int i)
{
	pid_t	pid;
	int		error;

	error = 0;
	while (i < my_shell->count)
	{
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{
			printf("1 i = %d\n", i);
			printf("end + 1 = %d\n", my_shell->control[i]->prioritet_start->end);
			if (chek_and_or(my_shell, &i, my_shell->control[i]->prioritet_start->end + 1))
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
			pid = fork();
			if (pid)
			{
				//printf("1 i = %d\n", i);
				waitpid(pid, &error, 0);
				//printf("2 i = %d\n", i);
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
				exit(make_exe(my_shell, i + 1));
			}
		 }
		 else if (my_shell->control[i]->command_type == EXE || my_shell->control[i]->command_type == MY_EXE)
		 {
			printf("5 i = %d\n", i);
			if (chek_and_or(my_shell, &i, i + 1))
				continue ;
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				if (my_shell->control[i]->command_type == EXE)
				{
					my_shell->control[i]->exe->fd_input = my_shell->control[i - 1]->pip[1];
				}
				else if (my_shell->control[i]->command_type == MY_EXE)
				{
					my_shell->control[i]->my_exe->fd_input = my_shell->control[i - 1]->pip[1];
				}
			}
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
				if (my_shell->control[i]->command_type == EXE)
				{
					my_shell->control[i]->exe->fd_output = my_shell->control[i + 1]->pip[0];
				}
				else if (my_shell->control[i]->command_type == MY_EXE)
				{
					my_shell->control[i]->my_exe->fd_output = my_shell->control[i + 1]->pip[0];
				}
			}
			my_shell->my_error = do_exe(my_shell, i);
		 }
		 ++i;
	}
	return(my_shell->my_error);
}
