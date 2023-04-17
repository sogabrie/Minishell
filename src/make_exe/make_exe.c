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
			if (chek_and_or(my_shell, &i, my_shell->control[i]->prioritet_start->end))
				continue ;
			++i;
			pid = fork();
			if (pid)
			{
				waitpid(pid, NULL, 0);
				i = my_shell->control[i - 1]->prioritet_start->end;
			}
			else
			{
				exit(make_exe(my_shell, i));
			}
		 }
		 else if (my_shell->control[i]->command_type == EXE || my_shell->control[i]->command_type == MY_EXE)
		 {
			if (chek_and_or(my_shell, &i, i))
				continue ;
			my_shell->my_error = do_exe(my_shell, i);
		 }
		 ++i;
	}
	return(my_shell->my_error);
}
