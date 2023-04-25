#include "struct.h"
#include "minishell.h"

int	check_meta_char(char *name)
{
	if (name && \
	ft_strcmp(name, "<<") && \
	ft_strcmp(name, "<") && \
	ft_strcmp(name, ">>") && \
	ft_strcmp(name, ">") && \
	ft_strcmp(name, "&&") && \
	ft_strcmp(name, "||") && \
	ft_strcmp(name, "|") && \
	ft_strcmp(name, " ") && \
	ft_strcmp(name, ")"))
		return (1);
	return (0);
}

int	check_my_exe(char *name)
{
	if (!ft_strcmp(name, "echo") \
		|| !ft_strcmp(name, "cd") \
		|| !ft_strcmp(name, "pwd") \
		|| !ft_strcmp(name, "export") \
		|| !ft_strcmp(name, "unset") \
		|| !ft_strcmp(name, "env") \
		|| !ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

int	check_redirect(char *name)
{
	if (!ft_strcmp(name, "<") \
		|| !ft_strcmp(name, ">") \
		|| !ft_strcmp(name, "<<") \
		|| !ft_strcmp(name, ">>"))
		return (1);
	return (0);
}

int	check_end(char *name)
{
	if (!ft_strcmp(name, "&&") \
		|| !ft_strcmp(name, "||") \
		|| !ft_strcmp(name, "|"))
		return (1);
	return (0);
}

void	creat_struct_prioritet_end_2(t_shell *my_shell, int *i, int *j)
{
	my_shell->control[my_shell->count - 1]->prioritet_end->end \
	= my_shell->count - 1;
	(*i) = my_shell->count - 2;
	(*j) = 1;
	while ((*i) >= 0)
	{
		if (my_shell->control[(*i)]->command_type == PRIORITET_START)
			--(*j);
		if (my_shell->control[(*i)]->command_type == PRIORITET_END)
			++(*j);
		if (!(*j))
		{
			my_shell->control[my_shell->count - 1]->prioritet_end->start = (*i);
			my_shell->control[(*i)]->prioritet_start->end = my_shell->count - 1;
			(*i) = 0;
		}
		--(*i);
	}
	my_shell->control[my_shell->count - 1]->prioritet_end->status = 0;
}
