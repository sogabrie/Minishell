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
	my_shell->cpy_fd_output = 1;
	my_shell->cpy_fd_input = 0;
	my_shell->check_exe = -1;
	my_shell->redirect = 0;
	my_shell->count_redir = 0;
	my_shell->close_fd = NULL;
	my_shell->close_fd_count = 0;
	my_shell->error_status = NO_ERROR;
	my_shell->full_name_here_doc = NULL;
	my_shell->start_here_doc = 0;
	my_shell->start_here_doc_plus = 0;
}

void	init_control(t_control **control, int i)
{
	control[i]->exe = 0;
	control[i]->prioritet_start = 0;
	control[i]->prioritet_end = 0;
	control[i]->logic_and = 0;
	control[i]->logic_or = 0;
	control[i]->redirect = 0;
	control[i]->count_redir = 0;
	control[i]->command_type = MY_NULL;
	control[i]->error = NO_ERROR;
}

void	creat_redir(t_shell *my_shell)
{
	my_shell->redirect = malloc (sizeof(t_redir *));
	if (!my_shell->redirect)
		malloc_error();
	my_shell->redirect[0] = malloc (sizeof(t_redir));
	if (!my_shell->redirect[0])
		malloc_error();
	my_shell->redirect[my_shell->count_redir]->filename = 0;
	++my_shell->count_redir;
}

void	add_redir(t_shell *my_shell)
{
	int		i;
	t_redir	**a;

	if (!my_shell->count_redir)
	{
		creat_redir(my_shell);
		return ;
	}
	a = malloc ((my_shell->count_redir + 1) * sizeof(t_redir *));
	if (!a)
		malloc_error();
	i = -1;
	while (++i < my_shell->count_redir)
		a[i] = my_shell->redirect[i];
	a[i] = malloc (sizeof(t_redir));
	if (!a[i])
		malloc_error();
	free(my_shell->redirect);
	my_shell->redirect = a;
	my_shell->redirect[my_shell->count_redir]->filename = 0;
	++my_shell->count_redir;
}

void	creat_cont_mas(t_shell *my_shell)
{
	my_shell->control = malloc (sizeof(t_control *));
	if (!my_shell->control)
		malloc_error();
	my_shell->control[0] = malloc (sizeof(t_control));
	if (!my_shell->control[0])
		malloc_error();
	init_control(my_shell->control, 0);
	++my_shell->count;
}

void	chreat_cont(t_shell *my_shell)
{
	int			i;
	t_control	**a;

	if (!my_shell->count)
	{
		creat_cont_mas(my_shell);
		return ;
	}
	a = malloc ((my_shell->count + 1) * sizeof(t_control *));
	if (!a)
		malloc_error();
	i = -1;
	while (++i < my_shell->count)
		a[i] = my_shell->control[i];
	a[i] = malloc (sizeof(t_control));
	if (!a[i])
		malloc_error();
	init_control(a, i);
	free(my_shell->control);
	my_shell->control = a;
	++my_shell->count;
}
