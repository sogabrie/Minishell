#include "struct.h"
#include "minishell.h"

int	creat_my_exe(t_shell *my_shell, char *name)
{
	write(1, "my_e_1\n",8);
	if (chreat_cont(my_shell))
		return (7);
	write(1, "my_e_2\n",8);
	my_shell->control[my_shell->count - 1]->command_type = MY_EXE;
	write(1, "my_e_3\n",8);
	my_shell->control[my_shell->count - 1]->my_exe = malloc(sizeof(t_my_exe));
	write(1, "my_e_4\n",8);
	if (!my_shell->control[my_shell->count - 1]->my_exe)
		return (7);
	write(1, "my_e_5\n",8);
	my_shell->control[my_shell->count - 1]->my_exe->name = ft_strdup(name);
	write(1, "my_e_6\n",8);
	if (!my_shell->control[my_shell->count - 1]->my_exe->name)
		return (7);
	write(1, "my_e_7\n",8);
	my_shell->control[my_shell->count - 1]->my_exe->fd_output = my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->my_exe->fd_input = my_shell->fd_input;
	my_shell->control[my_shell->count - 1]->my_exe->ptr_envp = my_shell->my_envp;
	my_shell->control[my_shell->count - 1]->my_exe->staatus = 0;
	my_shell->control[my_shell->count - 1]->my_exe->options = 0;
	my_shell->check_exe = my_shell->count - 1 ;
	write(1, "my_e_8\n",8);
	//printf("my_shell->check_exe = %d\n",my_shell->check_exe );
	return (0);
}

int	creat_exe(t_shell *my_shell, char *name)
{
	write(1, "exe_1\n",8);
	if (chreat_cont(my_shell))
		return (7);
	write(1, "exe_2\n",8);
	my_shell->control[my_shell->count - 1]->command_type = EXE;
	write(1, "exe_3\n",8);
	// printf("my_shell->control[my_shell->count - 1]->command_type = %d\n",my_shell->control[my_shell->count - 1]->command_type);
	my_shell->control[my_shell->count - 1]->exe = malloc(sizeof(t_exe));
	write(1, "exe_4\n",8);
	if (!my_shell->control[my_shell->count - 1]->exe)
		return (7);
	write(1, "exe_5\n",8);
	my_shell->control[my_shell->count - 1]->exe->full_name = ft_strdup(name);
	write(1, "exe_6\n",8);
	if (!my_shell->control[my_shell->count - 1]->exe->full_name)
		return (7);
	write(1, "exe_7\n",8);
	my_shell->control[my_shell->count - 1]->exe->fd_output = my_shell->fd_output;
	my_shell->control[my_shell->count - 1]->exe->fd_input = my_shell->fd_input;
	my_shell->control[my_shell->count - 1]->exe->ptr_envp = my_shell->my_envp;
	my_shell->control[my_shell->count - 1]->exe->status = 0;
	my_shell->control[my_shell->count - 1]->exe->options = 0;
	my_shell->check_exe = my_shell->count - 1 ;
	write(1, "exe_8\n",8);
	//printf("my_shell->check_exe = %d\n",my_shell->check_exe );
	return (0);
}

int	creat_redirect(t_shell *my_shell, int *i)
{
	char	*a;
	char	*c;
	char	*b = my_shell->double_list[*i];

	write(1, "redir_1\n", 9);
	//(*i)++;
	if (!ft_strcmp(my_shell->double_list[*i], "<<"))
	{
		(*i)++;
		if (!ft_strcmp(my_shell->double_list[*i], " "))
			(*i)++;
		printf("my_shell->double_list[*i]-------------aaaaaaaaaaa = %s\n",my_shell->double_list[*i]);
		write(1, "redir_6\n", 9);
		a = ft_strdup(echo_line(my_shell->double_list[*i]));
		printf("-------------aaaaaaaaaaa = %s\n", a);
		(*i)++;
		write(1, "redir_7\n", 9);
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
			write(1, "redir_8\n", 9);
			b = ft_strjoin(a, echo_line(my_shell->double_list[*i]));
			free(a);
			a = b;
			(*i)++;
		}
		write(1, "redir_9\n", 9);
	}
	else
	{
		(*i)++;
		if (!ft_strcmp(my_shell->double_list[*i], " "))
			(*i)++;
		printf("my_shell->double_list[*i]-------------aaaaaaaaaaa = %s\n",my_shell->double_list[*i]);
		write(1, "redir_6\n", 9);
		a = ft_strdup(echo_line(my_shell->double_list[*i]));
		printf("-------------aaaaaaaaaaa = %s\n", a);
		(*i)++;
		write(1, "redir_7\n", 9);
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
			write(1, "redir_8\n", 9);
			b = ft_strjoin(a, echo_line(my_shell->double_list[*i]));
			free(a);
			a = b;
			(*i)++;
		}
		write(1, "redir_9\n", 9);
	}
	printf("a = %s\n", a);
	printf("a________a my_shell->double_list[*i] = %s\n",my_shell->double_list[*i]);
	write(1, "redir_10\n", 9);
	if (!ft_strcmp(b, "<"))
		return (red_input(a));
	else if (!ft_strcmp(b, ">"))
		return (red_out(a));
	else if (!ft_strcmp(b, "<<"))
		return (here_doc(a, 0));
	else if (!ft_strcmp(b, ">>"))
		return (red_out_append(a));
	write(1, "redir_11\n", 9);
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
	// write(1, "bb_1\n",6);
	printf("my_shell->check_exe = %d\n",my_shell->check_exe );
	if (my_shell->control[my_shell->check_exe]->command_type == EXE)
	{
		// write(1, "bb_2\n",6);
		if (add_option_mas(&(my_shell->control[my_shell->check_exe]->exe->options), name, -1))
			return (8);
		// write(1, "bb_3\n",6);
	}
	else
	{
		// write(1, "bb_4\n",6);
		if (add_option_mas(&(my_shell->control[my_shell->check_exe]->my_exe->options), name, -1))
			return (8);
		// write(1, "bb_5\n",6);
	}
	// write(1, "bb_6\n",6);
	return (0);
}