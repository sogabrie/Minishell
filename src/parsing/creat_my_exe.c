#include "struct.h"
#include "minishell.h"

void	creat_exe_2(t_shell *my_shell)
{
	if (!my_shell->control[my_shell->count - 1]->exe->full_name)
		malloc_error();
	my_shell->control[my_shell->count - 1]->exe->fd_output \
	= my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->exe->fd_input = my_shell->fd_input;
	my_shell->control[my_shell->count - 1]->exe->cpy_fd_output \
	= my_shell->cpy_fd_output;
	my_shell->control[my_shell->count - 1]->exe->cpy_fd_input = \
	my_shell->cpy_fd_input;
	my_shell->control[my_shell->count - 1]->exe->ptr_envp = my_shell->my_envp;
	my_shell->control[my_shell->count - 1]->exe->status = 0;
	my_shell->control[my_shell->count - 1]->exe->options = 0;
	my_shell->control[my_shell->count - 1]->exe->error = 0;
	my_shell->control[my_shell->count - 1]->exe->flag_input = -1;
	my_shell->control[my_shell->count - 1]->exe->flag_output = -1;
	my_shell->check_exe = my_shell->count - 1;
}

void	creat_exe(t_shell *my_shell, int *i)
{
	char	*a;
	int		j;

	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = EXE;
	my_shell->control[my_shell->count - 1]->exe = malloc(sizeof(t_exe));
	if (!my_shell->control[my_shell->count - 1]->exe)
		malloc_error();
	my_shell->control[my_shell->count - 1]->exe->full_name = \
	ft_strdup(my_shell->double_list[(*i)]);
	if (!my_shell->control[my_shell->count - 1]->exe->full_name)
		malloc_error();
	while (check_meta_char(my_shell->double_list[(*i) + 1]))
	{
		++(*i);
		a = ft_strjoin(my_shell->control[my_shell->count - \
		1]->exe->full_name, my_shell->double_list[(*i)]);
		if (!a)
			malloc_error();
		free(my_shell->control[my_shell->count - 1]->exe->full_name);
		my_shell->control[my_shell->count - 1]->exe->full_name = a;
	}
	creat_exe_2(my_shell);
}
