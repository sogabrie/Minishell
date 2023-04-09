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
	my_shell->control[my_shell->count - 1]->my_exe->fd_output = my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->my_exe->fd_input = my_shell->fd_input;
	my_shell->control[my_shell->count - 1]->my_exe->ptr_envp = my_shell->my_envp;
	my_shell->control[my_shell->count - 1]->my_exe->staatus = 0;
	my_shell->control[my_shell->count - 1]->my_exe->options = 0;
	return (0);
}

int	creat_exe(t_shell *my_shell, char *name)
{
	if (chreat_cont(my_shell))
		return (7);
	my_shell->control[my_shell->count - 1]->command_type = EXE;
	my_shell->control[my_shell->count - 1]->exe = malloc(sizeof(t_exe));
	if (!my_shell->control[my_shell->count - 1]->exe)
		return (7);
	my_shell->control[my_shell->count - 1]->exe->full_name = ft_strdup(name);
	if (!my_shell->control[my_shell->count - 1]->exe->full_name)
		return (7);
	my_shell->control[my_shell->count - 1]->exe->fd_output = my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->exe->fd_input = my_shell->fd_input;
	my_shell->control[my_shell->count - 1]->exe->ptr_envp = my_shell->my_envp;
	my_shell->control[my_shell->count - 1]->exe->status = 0;
	my_shell->control[my_shell->count - 1]->exe->options = 0;
	return (0);
}

int	creat_redirect(t_shell *my_shell, int *i)
{
	char	*a;
	char	*c;
	char	*b = my_shell->double_list[*i];

	if (!ft_strcmp(my_shell->double_list[*i], "<<"))
	{
		a = ft_strdup(echo_line(my_shell->double_list[*i]));
		(*i)++;
		while (ft_strcmp(my_shell->double_list[*i], "<<") || \
		ft_strcmp(my_shell->double_list[*i], "<") || \
		ft_strcmp(my_shell->double_list[*i], ">>") || \
		ft_strcmp(my_shell->double_list[*i], ">") || \
		ft_strcmp(my_shell->double_list[*i], "&&") || \
		ft_strcmp(my_shell->double_list[*i], "||") || \
		ft_strcmp(my_shell->double_list[*i], "|") || \
		ft_strcmp(my_shell->double_list[*i], " ") || \
		ft_strcmp(my_shell->double_list[*i], ")"))
		{
			c = ft_strjoin(a, echo_line(my_shell->double_list[*i]));
			free(a);
			a = c;
			(*i)++;
		}
	}
	else
	{
		a = ft_strdup(echo_line(my_shell->double_list[*i]));
		(*i)++;
		while (ft_strcmp(my_shell->double_list[*i], "<<") || \
		ft_strcmp(my_shell->double_list[*i], "<") || \
		ft_strcmp(my_shell->double_list[*i], ">>") || \
		ft_strcmp(my_shell->double_list[*i], ">") || \
		ft_strcmp(my_shell->double_list[*i], "&&") || \
		ft_strcmp(my_shell->double_list[*i], "||") || \
		ft_strcmp(my_shell->double_list[*i], "|") || \
		ft_strcmp(my_shell->double_list[*i], " ") || \
		ft_strcmp(my_shell->double_list[*i], ")"))
		{
			b = ft_strjoin(a, echo_line(my_shell->double_list[*i]));
			free(a);
			a = b;
			(*i)++;
		}
	}
	if (!ft_strcmp(b, "<"))
		return (red_input(a));
	else if (!ft_strcmp(b, ">"))
		return (red_out(a));
	else if (!ft_strcmp(b, "<<"))
		return (here_doc(a, 0));
	else if (!ft_strcmp(b, ">>"))
		return (red_out_append(a));
	return (0);
}

int	add_option_mas(char ***options, char *name, int i)
{
	char **a;
	int	count;

	count = size_list(*options) + 1;
	a = malloc(sizeof(char *) * (count + 1));
	if (!a)
		return (7);
	while (++i < count - 1)
		a[i] = (*options)[i];
	a[i] = ft_strdup(name);
	a[++i] = 0;
	free(*options);
	*options = a;
	return (0);
}

int	add_option(t_shell *my_shell, char *name)
{
	if (my_shell->control[my_shell->check_exe]->command_type == EXE)
	{
		if (add_option_mas(&(my_shell->control[my_shell->check_exe]->exe->options), name, -1))
			return (8);
	}
	else
	{
		if (add_option_mas(&(my_shell->control[my_shell->check_exe]->my_exe->options), name, -1))
			return (8);
	}
	return (0);
}