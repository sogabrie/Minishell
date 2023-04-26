#include "struct.h"
#include "minishell.h"

int	creat_redirect_2(t_shell *my_shell, char **a)
{
	int		pip[2];
	pid_t	pits;
	char	*h ;

	pipe(pip);
	pits = fork();
	if (!pits)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		rl_clear_history();
		h = here_doc((*a), my_shell->start_here_doc_plus, \
		my_shell->full_name_here_doc, my_shell->my_envp);
		write(pip[1], h, ft_strlen(h) + 1);
		close(pip[1]);
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pits, NULL, 0);
	++my_shell->start_here_doc_plus;
	return (creat_redirect_2_1(my_shell, a, pip));
}

void	creat_redirect_3(t_shell *my_shell, char **a, enum s_redir_type type)
{
	my_shell->redirect[my_shell->count_redir - 1]->filename = chreat_wal((*a));
	if (my_shell->redirect[my_shell->count_redir - 1]->filename)
		my_shell->redirect[my_shell->count_redir - 1]->error = NO_ERROR;
	else
		my_shell->redirect[my_shell->count_redir - 1]->error = 1;
	my_shell->redirect[my_shell->count_redir - 1]->type = type;
}

int	creat_redirect(t_shell *my_shell, int *i)
{
	char	*a;
	char	*b;

	b = my_shell->double_list[*i];
	creat_redirect_1(my_shell, i, &a, &b);
	add_redir(my_shell);
	if (!ft_strcmp(b, "<<"))
	{
		if (creat_redirect_2(my_shell, &a))
			return (1);
	}
	else if (!ft_strcmp(b, "<"))
		creat_redirect_3(my_shell, &a, INPUT);
	else if (!ft_strcmp(b, ">"))
		creat_redirect_3(my_shell, &a, OUTPT);
	else if (!ft_strcmp(b, ">>"))
		creat_redirect_3(my_shell, &a, OUTPUT_APP);
	free(a);
	return (0);
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
	char	*b;
	int		j;
	int		count;

	count = add_option_mas(\
	&my_shell->control[my_shell->check_exe]->exe->options, \
	my_shell->double_list[(*i)], -1) - 1;
	while (check_meta_char(my_shell->double_list[(*i) + 1]))
	{
		++(*i);
		b = ft_strjoin(\
		my_shell->control[my_shell->check_exe]->exe->options[count], \
		my_shell->double_list[(*i)]);
		if (!b)
			malloc_error();
		free(my_shell->control[my_shell->check_exe]->exe->options[count]);
		my_shell->control[my_shell->check_exe]->exe->options[count] = b;
	}
}
