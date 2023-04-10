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
	my_shell->fd_output = 1;
	my_shell->fd_input = 0;
	my_shell->check_exe = -1;
	my_shell->close_fd  = NULL;
	my_shell->close_fd_count = 0;
}

void init_control(t_control **control, int i)
{
	control[i]->exe = 0;
	control[i]->my_exe = 0;
	control[i]->prioritet_start = 0;
	control[i]->prioritet_end = 0;
	control[i]->logic_and = 0;
	control[i]->logic_or = 0;
	control[i]->fd_output = 1;
	control[i]->fd_input = 0;
	control[i]->command_type = MY_NULL;
	control[i]->error = NO_ERROR;
}

int	creat_cont_mas(t_shell *my_shell)
{
	my_shell->control = malloc (sizeof(t_control *));
	if (!my_shell->control)
		return (6);
	my_shell->control[0] = malloc (sizeof(t_control));
	if (!my_shell->control[0])
		return (6);
	init_control(my_shell->control, 0);
	++my_shell->count;
	return (0);
}

int	chreat_cont(t_shell *my_shell)
{
	int	i;
	t_control **a;

	write(1, "con_1\n",8);
	if (!my_shell->count)
		return (creat_cont_mas(my_shell));
	write(1, "con_2\n",8);
	a = malloc ((my_shell->count + 1) * sizeof(t_control *));
	write(1, "con_3\n",8);
	if (!a)
		return (6);
	write(1, "con_4\n",8);
	i = -1;
	while (++i < my_shell->count)
		a[i] = my_shell->control[i];
	write(1, "con_5\n",8);
	a[i] = malloc (sizeof(t_control));
	write(1, "con_6\n",8);
	if (!a[i])
		return (6);
	write(1, "con_7\n",8);
	init_control(a, i);
	write(1, "con_8\n",8);
	free(my_shell->control);
	write(1, "con_9\n",8);
	my_shell->control = a;
	write(1, "con_10\n",8);
	++my_shell->count;
	write(1, "con_11\n",8);
	return (0);
}