#include "struct.h"
#include "minishell.h"

void	creat_my_exe(t_shell *my_shell, char *name)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = MY_EXE;
	my_shell->control[my_shell->count - 1]->my_exe = malloc(sizeof(t_my_exe));
	if (!my_shell->control[my_shell->count - 1]->my_exe)
		malloc_error();
	my_shell->control[my_shell->count - 1]->my_exe->name = ft_strdup(name);
	if (!my_shell->control[my_shell->count - 1]->my_exe->name)
		malloc_error();
	my_shell->control[my_shell->count - 1]->my_exe->fd_output \
	= my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->my_exe->fd_input \
	= my_shell->fd_input;
	my_shell->control[my_shell->count - 1]->my_exe->cpy_fd_output \
	= my_shell->cpy_fd_output;
	my_shell->control[my_shell->count - 1]->my_exe->cpy_fd_input \
	= my_shell->cpy_fd_input;
	my_shell->control[my_shell->count - 1]->my_exe->ptr_envp \
	= my_shell->my_envp;
	my_shell->control[my_shell->count - 1]->my_exe->staatus = 0;
	my_shell->control[my_shell->count - 1]->my_exe->options = 0;
	my_shell->check_exe = my_shell->count - 1 ;
}

void	creat_exe(t_shell *my_shell, char *name)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = EXE;
	my_shell->control[my_shell->count - 1]->exe = malloc(sizeof(t_exe));
	if (!my_shell->control[my_shell->count - 1]->exe)
		malloc_error();
	my_shell->control[my_shell->count - 1]->exe->full_name = ft_strdup(name);
	if (!my_shell->control[my_shell->count - 1]->exe->full_name)
		malloc_error();
	my_shell->control[my_shell->count - 1]->exe->fd_output \
	= my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->exe->fd_input = my_shell->fd_input;
	my_shell->control[my_shell->count - 1]->exe->cpy_fd_output \
	= my_shell->cpy_fd_output;
	my_shell->control[my_shell->count - 1]->exe->cpy_fd_input = my_shell->cpy_fd_input;
	my_shell->control[my_shell->count - 1]->exe->ptr_envp = my_shell->my_envp;
	my_shell->control[my_shell->count - 1]->exe->status = 0;
	my_shell->control[my_shell->count - 1]->exe->options = 0;
	my_shell->control[my_shell->count - 1]->exe->error = 0;
	my_shell->check_exe = my_shell->count - 1 ;
}

t_error_type	creat_redirect(t_shell *my_shell, int *i)
{
	int		fd = 0;
	char	*a;
	char	*c;
	char	*b = my_shell->double_list[*i];

	if (!ft_strcmp(my_shell->double_list[*i], "<<"))
	{
		(*i)++;
		if (!ft_strcmp(my_shell->double_list[*i], " "))
			(*i)++;
		a = ft_strdup(my_shell->double_list[*i]);
		(*i)++;
		while (my_shell->double_list[*i] && \
		ft_strcmp(my_shell->double_list[*i], "<<") && \
		ft_strcmp(my_shell->double_list[*i], "<") && \
		ft_strcmp(my_shell->double_list[*i], ">>") && \
		ft_strcmp(my_shell->double_list[*i], ">") && \
		ft_strcmp(my_shell->double_list[*i], "&&") && \
		ft_strcmp(my_shell->double_list[*i], "||") && \
		ft_strcmp(my_shell->double_list[*i], "|") && \
		ft_strcmp(my_shell->double_list[*i], " ") && \
		ft_strcmp(my_shell->double_list[*i], ")"))
		{
			c = ft_strjoin(a, my_shell->double_list[*i]);
			free(a);
			a = c;
			(*i)++;
		}
	}
	else
	{
		(*i)++;
		if (!ft_strcmp(my_shell->double_list[*i], " "))
			(*i)++;
		a = ft_strdup(my_shell->double_list[*i]);
		(*i)++;
		while (my_shell->double_list[*i] && \
		ft_strcmp(my_shell->double_list[*i], "<<") && \
		ft_strcmp(my_shell->double_list[*i], "<") && \
		ft_strcmp(my_shell->double_list[*i], ">>") && \
		ft_strcmp(my_shell->double_list[*i], ">") && \
		ft_strcmp(my_shell->double_list[*i], "&&") && \
		ft_strcmp(my_shell->double_list[*i], "||") && \
		ft_strcmp(my_shell->double_list[*i], "|") && \
		ft_strcmp(my_shell->double_list[*i], " ") && \
		ft_strcmp(my_shell->double_list[*i], ")"))
		{
			c = ft_strjoin(a, my_shell->double_list[*i]);
			free(a);
			a = c;
			(*i)++;
		}
	}
	if (!ft_strcmp(b, "<") && my_shell->my_error == NO_ERROR)
	{
		fd = red_input(a);
		if (fd >= 0)
			my_shell->fd_input = fd;
	}
	else if (!ft_strcmp(b, ">") && my_shell->my_error == NO_ERROR)
	{
		fd = red_out(a);
		if (fd >= 0)
			my_shell->fd_output = fd;
	}
	else if (!ft_strcmp(b, "<<"))
	{
		fd = here_doc(a, 0, my_shell->my_envp, NULL);
		printf("fd = %d\n", fd);
		if (fd >= 0)
			my_shell->fd_input = fd;
	}
	else if (!ft_strcmp(b, ">>") && my_shell->my_error == NO_ERROR)
	{
		fd = red_out_append(a);
		if (fd >= 0)
			my_shell->fd_output = fd;
	}
	free(a);
	if (fd <= 0)
		return (ENOENT);
	creat_close_fd(my_shell, fd);
	return (0);
}

void	add_option_mas(char ***options, char *name, int i)
{
	char	**a;
	int		count;

	count = size_list(*options) + 1;
	a = malloc(sizeof(char *) * (count + 1));
	if (!a)
		malloc_error();
	while (++i < count - 1)
		a[i] = (*options)[i];
	a[i] = ft_strdup(name);
	a[++i] = 0;
	free(*options);
	*options = a;
}

void	add_option(t_shell *my_shell, char *name)
{
	if (my_shell->control[my_shell->check_exe]->command_type == EXE)
	{
		add_option_mas(\
		&(my_shell->control[my_shell->check_exe]->exe->options), name, -1);
	}
	else
	{
		add_option_mas(\
		&(my_shell->control[my_shell->check_exe]->my_exe->options), name, -1);
	}
}
