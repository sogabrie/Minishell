#include "struct.h"
#include "minishell.h"

void	free_struct_2(t_shell *my_shell, int *i, int *j)
{
	int	i2;

	i2 = 0;
	// write(2, "exe_AA_1\n",10);
	if (my_shell->control[(*i)]->command_type == EXE)
	{
		// write(2, "exe_AA_2\n",10);
		while (i2 < my_shell->control[(*i)]->count_redir)
		{
			free(my_shell->control[(*i)]->redirect[i2]->filename);
			free(my_shell->control[(*i)]->redirect[i2++]);
		}
		// write(2, "exe_AA_3\n",10);
		free(my_shell->control[(*i)]->redirect);
		free(my_shell->control[(*i)]->exe->full_name);
		(*j) = 0;
		// write(2, "exe_AA_4\n",10);
		// printf("my_shell->control[(*i)]->exe->options = %p\n", my_shell->control[(*i)]->exe->options);
		while (my_shell->control[(*i)]->exe->options && \
		my_shell->control[(*i)]->exe->options[(*j)])
			free(my_shell->control[(*i)]->exe->options[(*j)++]);
		// write(2, "exe_SS_1\n",10);
		free(my_shell->control[(*i)]->exe->options);
		// write(2, "exe_SS_1\n",10);
		free(my_shell->control[(*i)]->exe);
		// write(2, "exe_AA_5\n",10);
	}
	// write(2, "exe_AA_6\n",10);
	if (my_shell->control[(*i)]->command_type == PRIORITET_START)
		free(my_shell->control[(*i)]->prioritet_start);
	// write(2, "exe_AA_7\n",10);
	if (my_shell->control[(*i)]->command_type == PRIORITET_END)
		free(my_shell->control[(*i)]->prioritet_end);
	// write(2, "exe_AA_8\n",10);
	free(my_shell->control[(*i)++]);
	// write(2, "exe_AA_9\n",10);
}

void	free_struct_3(t_shell *my_shell)
{
	int	i;

	i = 0;
	while (i < my_shell->close_fd_count)
		close(my_shell->close_fd[i++]);
	free(my_shell->line);
	free(my_shell->double_list);
	free(my_shell->delimiter);
	free(my_shell->control);
	free(my_shell->full_path);
	free(my_shell->close_fd);
	my_shell->line = 0;
	my_shell->control = 0;
	my_shell->delimiter_count = 0;
	my_shell->full_path = 0;
	my_shell->delimiter = 0;
	my_shell->double_list = 0;
	my_shell->check_exe = -1;
	my_shell->close_fd = 0;
	my_shell->close_fd_count = 0;
	my_shell->count = 0;
	my_shell->my_error = NO_ERROR;
	my_shell->count_redir = 0;
	my_shell->redirect = 0;
}

void	free_struct(t_shell *my_shell)
{
	int	i;
	int	j;

	i = 0;
	del_tmp_files(my_shell->start_here_doc, my_shell->full_name_here_doc, NULL, NULL);
	my_shell->start_here_doc_plus = my_shell->start_here_doc;
	// write(2,"fffff_1\n", 9);
	while (i < my_shell->count)
		free_struct_2(my_shell, &i, &j);
	// write(2,"fffff_3\n", 9);
	i = 0;
	while (my_shell->double_list && my_shell->double_list[i])
	{
		// write(2,"fffff_4\n", 9);
		free(my_shell->double_list[i]);
		++i;
	}
	// write(2,"fffff_6\n", 9);
	i = 0;
	while (my_shell->full_path && my_shell->full_path[i])
	{
		free(my_shell->full_path[i]);
		++i;
	}
	// write(2,"fffff_8\n", 9);
	free_struct_3(my_shell);
	// write(2,"ffff_10\n", 9);
}
