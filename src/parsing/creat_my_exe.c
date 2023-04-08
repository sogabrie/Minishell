#include "struct.h"
#include "minishell.h"

int	creat_my_exe(t_shell *my_shell, char *name)
{
	if (chreat_cont(my_shell))
		return (7);
	my_shell->control[my_shell->count - 1]->command_type = MY_EXE;
	my_shell->control[my_shell->count - 1]->my_exe = malloc(sizeof(t_my_exe));
	if (!my_shell->control[my_shell->count - 1]->my_exe)
		return (7);
	my_shell->control[my_shell->count - 1]->my_exe->name = ft_strdup(name);
	if (!my_shell->control[my_shell->count - 1]->my_exe->name)
		return (7);
	my_shell->control[my_shell->count - 1]->my_exe->fd_output = 1;
	my_shell->control[my_shell->count - 1]->my_exe->fd_input = my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->my_exe->staatus = my_shell->fd_input;
	return (0);
}

int	creat_exe(t_shell *my_shell, char *name)
{
	if (chreat_cont(my_shell))
		return (7);
	my_shell->control[my_shell->count - 1]->command_type = MY_EXE;
	my_shell->control[my_shell->count - 1]->my_exe = malloc(sizeof(t_my_exe));
	if (!my_shell->control[my_shell->count - 1]->my_exe)
		return (7);
	my_shell->control[my_shell->count - 1]->my_exe->name = ft_strdup(name);
	if (!my_shell->control[my_shell->count - 1]->my_exe->name)
		return (7);
	my_shell->control[my_shell->count - 1]->my_exe->fd_output = 1;
	my_shell->control[my_shell->count - 1]->my_exe->fd_input = my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->my_exe->staatus = my_shell->fd_input;
	return (0);
}

int	creat_redirect(t_shell *my_shell, int i)
{
	char	*a;

	if (!ft_strcmp(my_shell->double_list[i], "<"))
		return (redirect_input(a));
	else if (!ft_strcmp(my_shell->double_list[i], ">"))
		return (red_out(a));
	else if (!ft_strcmp(my_shell->double_list[i], "<<"))
		return (here_doc(a));
	else if (!ft_strcmp(my_shell->double_list[i], ">>"))
		return (red_out_append(a));
	return (0);
}