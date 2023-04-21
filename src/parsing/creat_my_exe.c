#include "struct.h"
#include "minishell.h"

// void	creat_my_exe(t_shell *my_shell, char *name)
// {
// 	chreat_cont(my_shell);
// 	my_shell->control[my_shell->count - 1]->command_type = MY_EXE;
// 	my_shell->control[my_shell->count - 1]->my_exe = malloc(sizeof(t_my_exe));
// 	if (!my_shell->control[my_shell->count - 1]->my_exe)
// 		malloc_error();
// 	my_shell->control[my_shell->count - 1]->my_exe->name = name;
// 	if (!my_shell->control[my_shell->count - 1]->my_exe->name)
// 		malloc_error();
// 	my_shell->control[my_shell->count - 1]->my_exe->fd_output \
// 	= my_shell->fd_output;
// 	my_shell->control[my_shell->count - 1]->my_exe->fd_input \
// 	= my_shell->fd_input;
// 	my_shell->control[my_shell->count - 1]->my_exe->cpy_fd_output \
// 	= my_shell->cpy_fd_output;
// 	my_shell->control[my_shell->count - 1]->my_exe->cpy_fd_input \
// 	= my_shell->cpy_fd_input;
// 	my_shell->control[my_shell->count - 1]->my_exe->ptr_envp \
// 	= my_shell->my_envp;
// 	my_shell->control[my_shell->count - 1]->my_exe->staatus = 0;
// 	my_shell->control[my_shell->count - 1]->my_exe->options = 0;
// 	my_shell->check_exe = my_shell->count - 1 ;
// }

void	creat_exe(t_shell *my_shell, int *i)
{
	char	*a;
	int		j;
	// write(2, "cccc_1\n", 8);
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = EXE;
	my_shell->control[my_shell->count - 1]->exe = malloc(sizeof(t_exe));
	// write(2, "cccc_2\n", 8);
	if (!my_shell->control[my_shell->count - 1]->exe)
		malloc_error();
	my_shell->control[my_shell->count - 1]->exe->full_name = ft_strdup(my_shell->double_list[(*i)]);
	if (!my_shell->control[my_shell->count - 1]->exe->full_name)
		malloc_error();
	// write(2, "cccc_3\n", 8);
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
		++(*i);
		a =  ft_strjoin(my_shell->double_list[(*i) + 1], my_shell->control[my_shell->count - 1]->exe->full_name);
		if (!a)
			malloc_error();
		free(my_shell->control[my_shell->count - 1]->exe->full_name);
		my_shell->control[my_shell->count - 1]->exe->full_name = a;
	}
	// write(2, "ccc_10\n", 8);
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
	char	*m;

	(*i)++;
	if (!ft_strcmp(my_shell->double_list[*i], " "))
		(*i)++;
	if (!ft_strcmp(b, "<<"))
		a = ft_strdup(heer_doc_echo(my_shell->double_list[*i]));
	else
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
		if (!ft_strcmp(b, "<<"))
			d = ft_strdup(heer_doc_echo(my_shell->double_list[*i]));
		else
			d = ft_strdup(my_shell->double_list[*i]);
		c = ft_strjoin(a, d);
		free(d);
		free(a);
		a = c;
		(*i)++;
	}
	if (!ft_strcmp(b, "<<"))
	{
		m = here_doc(a, 0, my_shell->my_envp, NULL);
		free(a);
		if (!m)
			return (ENOENT);
	}
	// if (ft_strcmp(b, "<<"))
	// {
	// 	mas = wildcards(ft_strdup(a));
	// 	if (size_list(mas) > 1)
	// 	{
	// 		write(2, "minishell: ", 12);
	// 		write(2, a, ft_strlen(a));
	// 		write(2, ": shata filern\n", 16);
	// 		free(a);
	// 		two_dimensional_mas(&mas);
	// 		return (ENOENT);
	// 	}
	// 	else if (size_list(mas) == 1)
	// 	{
	// 		free(a);
	// 		a = mas[0];
	// 		free(mas);
	// 	}
	// 	else
	// 		two_dimensional_mas(&mas);
	// }
	// if (!ft_strcmp(b, "<") && my_shell->my_error == NO_ERROR)
	// {
	// 	fd = red_input(a);
	// 	if (fd >= 0)
	// 		my_shell->fd_input = fd;
	// }
	// else if (!ft_strcmp(b, ">") && my_shell->my_error == NO_ERROR)
	// {
	// 	fd = red_out(a);
	// 	if (fd >= 0)
	// 		my_shell->fd_output = fd;
	// }
	// else if (!ft_strcmp(b, "<<"))
	// {
	// 	fd = here_doc(a, 0, my_shell->my_envp, NULL);
	// 	if (fd >= 0)
	// 		my_shell->fd_input = fd;
	// }
	// else if (!ft_strcmp(b, ">>") && my_shell->my_error == NO_ERROR)
	// {
	// 	fd = red_out_append(a);
	// 	if (fd >= 0)
	// 		my_shell->fd_output = fd;
	// }
	// free(a);
	// if (fd <= 0)
	// 	return (ENOENT);
	// creat_close_fd(my_shell, fd);
	// return (0);
}

int	add_option_mas(char ***options, char *name, int i)
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
	return (i);
}

void	add_option(t_shell *my_shell, int *i)
{
	// char	***a;
	char	**b;
	int		j;
	int		count;

	count = add_option_mas(&my_shell->control[my_shell->check_exe]->exe->options, my_shell->double_list[(*i)], -1) - 1;
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
		++(*i);
		b = ft_strjoin(my_shell->control[my_shell->check_exe]->exe->options[count], my_shell->double_list[(*i)]);
		if (!b)
			malloc_error();
		free(my_shell->control[my_shell->check_exe]->exe->options[count]);
		my_shell->control[my_shell->check_exe]->exe->options[count] = b;
	}
	(*i)++;
}
