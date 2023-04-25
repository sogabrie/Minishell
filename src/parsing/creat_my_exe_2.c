#include "struct.h"
#include "minishell.h"

char	*chreat_wal_2(char *name, char ***a)
{
	int		i;

	i = -1;
	write (2, "minishell: ", 11);
	write (2, name, ft_strlen(name));
	write (2, ": ambiguous redirect\n", 22);
	while ((*a)[++i])
		free((*a)[i]);
	free((*a));
	return (NULL);
}

char	*chreat_wal(char *name)
{
	char	**a;
	char	*c;

	a = wildcards(ft_strdup(name));
	if (!a)
	{
		c = ft_strdup(name);
		if (!c)
			malloc_error();
		return (c);
	}
	if (size_list(a) > 1)
		return (chreat_wal_2(name, &a));
	c = a[0];
	free(a);
	return (c);
}

void	creat_redirect_1_1(t_shell *my_shell, int *i, char **a, char **b)
{
	(*i)++;
	if (!ft_strcmp(my_shell->double_list[*i], " "))
		(*i)++;
	if (!ft_strcmp((*b), "<<"))
		(*a) = ft_strdup(heer_doc_echo(my_shell->double_list[*i]));
	else
		(*a) = ft_strdup(my_shell->double_list[*i]);
	if (!(*a))
		malloc_error();
	(*i)++;
}

void	creat_redirect_1(t_shell *my_shell, int *i, char **a, char **b)
{
	char	*c;
	char	*d;

	creat_redirect_1_1(my_shell, i, a, b);
	while (check_meta_char(my_shell->double_list[(*i)]))
	{
		if (!ft_strcmp((*b), "<<"))
			d = ft_strdup(heer_doc_echo(my_shell->double_list[*i]));
		else
			d = ft_strdup(my_shell->double_list[*i]);
		if (!d)
			malloc_error();
		c = ft_strjoin((*a), d);
		if (!c)
			malloc_error();
		free(d);
		free((*a));
		(*a) = c;
		(*i)++;
	}
}

int	creat_redirect_2_1(t_shell *my_shell, char **a, int	*pip)
{
	char	*t;

	close(pip[1]);
	t = ft_calloc(1, 100);
	if (!t)
		malloc_error();
	read(pip[0], t, 99);
	close(pip[0]);
	if (!t || !t[0])
	{
		write(1, "\n", 1);
		free(t);
		free((*a));
		return (1);
	}
	my_shell->redirect[my_shell->count_redir - 1]->filename = t;
	if (!ft_strcmp(my_shell->redirect[my_shell->count_redir - 1]->filename, \
	"error"))
		my_shell->redirect[my_shell->count_redir - 1]->error = ENOENT;
	else
		my_shell->redirect[my_shell->count_redir - 1]->error = NO_ERROR;
	my_shell->redirect[my_shell->count_redir - 1]->type = HERE_DOC;
	return (0);
}
