#include "struct.h"
#include "minishell.h"

void	sigint_pars_doc(int sig)
{
	// signal(SIGINT, SIG_IGN);
	write(1, "\n", 1);
	exit(0);
	// signal(SIGINT, SIG_IGN);
	(void)sig;
}

void	sigquit_pars_doc(int sig)
{
	write(1, "Quit: 3\n", 9);
	(void)sig;
}

void	creat_exe(t_shell *my_shell, int *i)
{
	char	*a;
	int		j;
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = EXE;
	my_shell->control[my_shell->count - 1]->exe = malloc(sizeof(t_exe));
	if (!my_shell->control[my_shell->count - 1]->exe)
		malloc_error();
	my_shell->control[my_shell->count - 1]->exe->full_name = ft_strdup(my_shell->double_list[(*i)]);
	if (!my_shell->control[my_shell->count - 1]->exe->full_name)
		malloc_error();
	while (check_meta_char(my_shell->double_list[(*i) + 1]))
	{
		++(*i);
		a =  ft_strjoin( my_shell->control[my_shell->count - 1]->exe->full_name, my_shell->double_list[(*i)]);
		if (!a)
			malloc_error();
		free(my_shell->control[my_shell->count - 1]->exe->full_name);
		my_shell->control[my_shell->count - 1]->exe->full_name = a;
	}
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
	my_shell->control[my_shell->count - 1]->exe->flag_input = -1;
	my_shell->control[my_shell->count - 1]->exe->flag_output = -1;
	my_shell->check_exe = my_shell->count - 1 ;
}

char	*chreat_wal(char *name)
{
	char	**a;
	char	*c;
	int		i;

	// write(2, "wal_1\n", 7);
	a = wildcards(ft_strdup(name));
	if (!a)
	{
		// printf("name = %s\n", name);
		// write(2, "wal_2\n", 7);
		c = ft_strdup(name);
		if (!c)
			malloc_error();
		// write(2, "wal_3\n", 7);
		return (c);
	}
	// write(2, "wal_4\n", 7);
	if (size_list(a) > 1)
	{
		i = -1;
		write (2, "minishell: ", 11);
		write (2, name, ft_strlen(name));
		write (2, ": ambiguous redirect\n", 22);
		while(a[++i])
			free(a[i]);
		free(a);
		return (0);
	}
	// write(2, "wal_5\n", 7);
	c = a[0];
	// write(2, "wal_6\n", 7);
	free(a);
	// write(2, "wal_7\n", 7);
	return (c);
}

void	creat_redirect(t_shell *my_shell, int *i)
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
	while (check_meta_char(my_shell->double_list[(*i)]))
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
	add_redir(my_shell);
	if (!ft_strcmp(b, "<<"))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
		int	pip[2];
		pid_t pits = fork();
		if (!pits)
		{

			signal(SIGINT, sigint_pars_doc);
			signal(SIGQUIT, sigquit_pars_doc);
			rl_clear_history();
			int q = here_doc(a, 0, my_shell->my_envp, 0);
			close(pip[0]);
			char *h =  ft_itoa(q);
			write(pip[1], h, ft_strlen(h));
			printf("q = %d\n", q);
			exit(0);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
		close(pip[1]);
		waitpid(pits, NULL, 0);
		char *t = ft_calloc(1, 20);
		read(pip[1], t, 19);
		int f = ft_atoi(t);
		free(t);
		// waitpid(pits, &f, 0);
		printf("f = %d\n", f);
		printf("f = %p\n", &f);
		// printf("f = %d\n", *f);
		my_shell->redirect[my_shell->count_redir - 1]->here_doc = f;
		if (!my_shell->redirect[my_shell->count_redir - 1]->here_doc)
			my_shell->redirect[my_shell->count_redir - 1]->error = ENOENT;
		else
			my_shell->redirect[my_shell->count_redir - 1]->error = NO_ERROR;
		my_shell->redirect[my_shell->count_redir - 1]->type = HERE_DOC;
	}
	else if (!ft_strcmp(b, "<"))
	{
		my_shell->redirect[my_shell->count_redir - 1]->filename = chreat_wal(a);
		// write(2, "wal_8\n", 7);
		if (my_shell->redirect[my_shell->count_redir - 1]->filename)
			my_shell->redirect[my_shell->count_redir - 1]->error = NO_ERROR;
		else
			my_shell->redirect[my_shell->count_redir - 1]->error = 1;
		// write(2, "wal_9\n", 7);
		my_shell->redirect[my_shell->count_redir - 1]->type = INPUT;
	}
	else if (!ft_strcmp(b, ">"))
	{
		my_shell->redirect[my_shell->count_redir - 1]->filename = chreat_wal(a);
		if (my_shell->redirect[my_shell->count_redir - 1]->filename)
			my_shell->redirect[my_shell->count_redir - 1]->error = NO_ERROR;
		else
			my_shell->redirect[my_shell->count_redir - 1]->error = 1;
		my_shell->redirect[my_shell->count_redir - 1]->type = OUTPT;
	}
	else if (!ft_strcmp(b, ">>"))
	{
		my_shell->redirect[my_shell->count_redir - 1]->filename = chreat_wal(a);
		if (my_shell->redirect[my_shell->count_redir - 1]->filename)
			my_shell->redirect[my_shell->count_redir - 1]->error = NO_ERROR;
		else
			my_shell->redirect[my_shell->count_redir - 1]->error = 1;
		my_shell->redirect[my_shell->count_redir - 1]->type = OUTPUT_APP;
	}
	free(a);
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

	count = add_option_mas(&my_shell->control[my_shell->check_exe]->exe->options, my_shell->double_list[(*i)], -1) - 1;
	while (check_meta_char(my_shell->double_list[(*i) + 1]))
	{
		++(*i);
		b = ft_strjoin(my_shell->control[my_shell->check_exe]->exe->options[count], my_shell->double_list[(*i)]);
		if (!b)
			malloc_error();
		free(my_shell->control[my_shell->check_exe]->exe->options[count]);
		my_shell->control[my_shell->check_exe]->exe->options[count] = b;
	}
	// (*i)++;
}
