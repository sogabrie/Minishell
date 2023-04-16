#include "struct.h"
#include "minishell.h"

void	free_struct_2(t_shell *my_shell, int *i, int *j)
{
	if (my_shell->control[(*i)]->command_type == EXE)
	{
		free(my_shell->control[(*i)]->exe->full_name);
		(*j) = 0;
		while (my_shell->control[(*i)]->exe->options && \
		my_shell->control[(*i)]->exe->options[(*j)])
			free(my_shell->control[(*i)]->exe->options[(*j)++]);
		free(my_shell->control[(*i)]->exe->options);
		free(my_shell->control[(*i)]->exe);
	}
	if (my_shell->control[(*i)]->command_type == MY_EXE)
	{
		free(my_shell->control[(*i)]->my_exe->name);
		(*j) = 0;
		while (my_shell->control[(*i)]->my_exe->options && \
		my_shell->control[(*i)]->my_exe->options[(*j)])
			free(my_shell->control[(*i)]->my_exe->options[(*j)++]);
		free(my_shell->control[(*i)]->my_exe->options);
		free(my_shell->control[(*i)]->my_exe);
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
}

void	free_struct(t_shell *my_shell)
{
	int	i;
	int	j;

	i = 0;
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
