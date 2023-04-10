#include "struct.h"
#include "minishell.h"

void	free_struct(t_shell *my_shell)
{
	int i;
	int	j;

	i = 0;
	// write (1, "free_1\n", 8);
	while (i < my_shell->count)
	{
		if (my_shell->control[i]->command_type == EXE)
		{
			free(my_shell->control[i]->exe->full_name);
			j = 0;
			while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j])
			{
				free(my_shell->control[i]->exe->options[j++]);
			}
			free(my_shell->control[i]->exe->options);
		}
		if (my_shell->control[i]->command_type == MY_EXE)
		{
			free(my_shell->control[i]->my_exe->name);
			j = 0;
			while (my_shell->control[i]->my_exe->options && my_shell->control[i]->my_exe->options[j])
			{
				free(my_shell->control[i]->my_exe->options[j++]);
			}
			free(my_shell->control[i]->my_exe->options);
		}
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{
			free(my_shell->control[i]->prioritet_start);
		}
		if (my_shell->control[i]->command_type == PRIORITET_END)
		{
			free(my_shell->control[i]->prioritet_end);
		}
		++i;
	}
	// write (1, "free_2\n", 8);
	i = 0;
	// printf("my_shell->count = %d\n", my_shell->count);
	while (i < my_shell->count)
	{
		// printf("i = %d\n", i);
		free(my_shell->control[i++]);
	}
	// write  (1, "free_3\n", 8);
	i = 0;
	while (my_shell->double_list && my_shell->double_list[i])
	{
		free(my_shell->double_list[i]);
		++i;
	}
	// write  (1, "free_4\n", 8);
	i = 0;
	while (my_shell->full_path && my_shell->full_path[i])
	{
		free(my_shell->full_path[i]);
		++i;
	}
	i = 0;
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