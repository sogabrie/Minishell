#include "struct.h"
#include "minishell.h"

void	creat_my_exe(t_shell *my_shell, char *name)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = MY_EXE;
	my_shell->control[my_shell->count - 1]->my_exe = malloc(sizeof(t_my_exe));
	if (!my_shell->control[my_shell->count - 1]->my_exe)
		malloc_error();
	my_shell->control[my_shell->count - 1]->my_exe->name = echo_line(name, my_shell->my_envp, NULL, my_shell->my_error);
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
	my_shell->control[my_shell->count - 1]->exe->full_name = echo_line(name, my_shell->my_envp, NULL, my_shell->my_error);
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
	char	*d;
	char	**mas;

	(*i)++;
	if (!ft_strcmp(my_shell->double_list[*i], " "))
		(*i)++;
	if (!ft_strcmp(b, "<<"))
		a = ft_strdup(heer_doc_echo(my_shell->double_list[*i]));
	else
		a = echo_line(my_shell->double_list[*i], my_shell->my_envp, NULL, my_shell->my_error);
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
		if (!ft_strcmp(b, "<<"))
			d = ft_strdup(heer_doc_echo(my_shell->double_list[*i]));
		else
			d = echo_line(my_shell->double_list[*i], my_shell->my_envp, NULL, my_shell->my_error);
		c = ft_strjoin(a, d);
		free(d);
		free(a);
		a = c;
		(*i)++;
	}
	if (ft_strcmp(b, "<<"))
	{
		mas = wildcards(ft_strdup(a));
		if (size_list(mas) > 1)
		{
			write(2, "minishell: ", 12);
			write(2, a, ft_strlen(a));
			write(2, ": shata filern\n", 16);
			free(a);
			two_dimensional_mas(&mas);
			return (ENOENT);
		}
		else if (size_list(mas) == 1)
		{
			free(a);
			a = mas[0];
			free(mas);
		}
		else
			two_dimensional_mas(&mas);
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

void	add_option_mas(char ***options, char *name, int i, t_shell *my_shell)
{
	char	**a;
	int		count;

	count = size_list(*options) + 1;
	a = malloc(sizeof(char *) * (count + 1));
	if (!a)
		malloc_error();
	while (++i < count - 1)
		a[i] = (*options)[i];
	a[i] = echo_line(name, my_shell->my_envp, NULL, my_shell->my_error);
	a[++i] = 0;
	free(*options);
	*options = a;
}

void	add_option(t_shell *my_shell, char *name, int *i)
{
	char	*d;
	char	*c;
	int		j;
	int		t;
	char	**mas;

	t = 0;
	if (my_shell->control[my_shell->check_exe]->command_type == EXE)
	{
		add_option_mas(\
		&(my_shell->control[my_shell->check_exe]->exe->options), name, -1, my_shell);
		j = size_list(my_shell->control[my_shell->check_exe]->exe->options) - 1;
		while (my_shell->double_list[(*i) + 1] && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "<<") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "<") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], ">>") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], ">") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "&&") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "||") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "|") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], " ") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], ")"))
		{
			d = echo_line(my_shell->double_list[(*i) + 1], my_shell->my_envp, NULL, my_shell->my_error);
			c = ft_strjoin(my_shell->control[my_shell->check_exe]->exe->options[j], d);
			free(d);
			free(my_shell->control[my_shell->check_exe]->exe->options[j]);
			my_shell->control[my_shell->check_exe]->exe->options[j] = c;
		}
		mas = wildcards(ft_strdup(my_shell->control[my_shell->check_exe]->exe->options[j]));
		if (size_list(mas) < 1)
			two_dimensional_mas(&mas);
		else
		{
			free(my_shell->control[my_shell->check_exe]->exe->options[j]);
			my_shell->control[my_shell->check_exe]->exe->options[j] = 0;
			while (mas[t])
			{
				add_option_mas(&(my_shell->control[my_shell->check_exe]->exe->options)\
				, mas[t], -1, my_shell);
				++t;
			}
			two_dimensional_mas(&mas);
		}
		(*i)++;
	}
	else
	{
		add_option_mas(\
		&(my_shell->control[my_shell->check_exe]->my_exe->options), name, -1, my_shell);
		j = size_list(my_shell->control[my_shell->check_exe]->my_exe->options) - 1;
		while (my_shell->double_list[(*i) + 1] && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "<<") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "<") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], ">>") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], ">") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "&&") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "||") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], "|") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], " ") && \
		ft_strcmp(my_shell->double_list[(*i) + 1], ")"))
		{
			d = echo_line(my_shell->double_list[(*i) + 1], my_shell->my_envp, NULL, my_shell->my_error);
			c = ft_strjoin(my_shell->control[my_shell->check_exe]->my_exe->options[j], d);
			free(d);
			free(my_shell->control[my_shell->check_exe]->my_exe->options[j]);
			my_shell->control[my_shell->check_exe]->my_exe->options[j] = c;
		}
		mas = wildcards(ft_strdup(my_shell->control[my_shell->check_exe]->my_exe->options[j]));
		if (size_list(mas) < 1)
			two_dimensional_mas(&mas);
		else
		{
			free(my_shell->control[my_shell->check_exe]->my_exe->options[j]);
			my_shell->control[my_shell->check_exe]->my_exe->options[j] = 0;
			while (mas[t])
			{
				add_option_mas(&(my_shell->control[my_shell->check_exe]->my_exe->options)\
				, mas[t], -1, my_shell);
				++t;
			}
			two_dimensional_mas(&mas);
		}
		(*i)++;
	}
}
