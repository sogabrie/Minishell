#include "struct.h"
#include "minishell.h"

void	init_shell(t_shell *my_shell)
{
	my_shell->line = NULL;
	my_shell->double_list = NULL;
	my_shell->full_path = NULL;
	my_shell->delimiter_count = 0;
	my_shell->delimiter = 0;
	my_shell->my_envp = NULL;
	my_shell->control = NULL;
	my_shell->count = 0;
	my_shell->my_error = NO_ERROR;
}

void init_control(t_shell *my_shell)
{
	my_shell->control[my_shell->count ]->exe = 0;
	my_shell->control[my_shell->count ]->my_exe = 0;
	my_shell->control[my_shell->count ]->prioritet = 0;
	my_shell->control[my_shell->count ]->logic_and = 0;
	my_shell->control[my_shell->count ]->logic_or = 0;
	my_shell->control[my_shell->count ]->fd_output = 1;
	my_shell->control[my_shell->count ]->fd_input = 0;
	my_shell->control[my_shell->count ]->command_type = MY_NULL;
	my_shell->control[my_shell->count ]->error = NO_ERROR;
}

int	creat_cont_mas(t_shell *my_shell)
{
	my_shell->control = malloc (sizeof(t_control *));
	if (!my_shell->control)
		return (6);
	my_shell->control[0] = malloc (sizeof(t_control));
	if (!my_shell->control[0])
		return (6);
	init_control(my_shell);
	++my_shell->count;
	return (0);
}

int	chreat_cont(t_shell *my_shell)
{
	int	i;
	t_control **a;

	if (!my_shell->count)
		return (creat_cont_mas(my_shell));
	a = malloc ((my_shell->count + 1) * sizeof(t_control *));
	if (!a)
		return (6);
	i = -1;
	while (++i < my_shell->count)
		a[i] = my_shell->control[i];
	a[i] = malloc (sizeof(t_control));
	if (!my_shell->control[i])
		return (6);
	init_control(my_shell);
	free(my_shell->control);
	my_shell->control = a;
	++my_shell->count;
	return (0);
}