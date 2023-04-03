#include "minishell.h"
#include "struct.h"

t_error_type	control_pars_3(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	if ((*j) != (*i))
	{
		cp_list = malloc((size_list(my_shell->double_list) + 2) \
		* sizeof(char *));
		cp_free(&my_shell->double_list, &cp_list);
		my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*j), (*i));
		my_shell->double_list[(*n)] = 0;
	}
	cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
	cp_free(&my_shell->double_list, &cp_list);
	my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*i), (*i) + 2);
	my_shell->double_list[(*n)] = 0;
	(*i) += 2;
	(*j) = (*i);
	return (NO_ERROR);
}

t_error_type	control_pars_4(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	if ((*j) != (*i))
	{
		cp_list = malloc((size_list(my_shell->double_list) + 2) \
		* sizeof(char *));
		cp_free(&my_shell->double_list, &cp_list);
		my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*j), (*i));
		my_shell->double_list[(*n)] = 0;
	}
	cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
	cp_free(&my_shell->double_list, &cp_list);
	my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*i), (*i) + 1);
	my_shell->double_list[(*n)] = 0;
	++(*i);
	(*j) = (*i);
	return (NO_ERROR);
}

t_error_type	control_pars_5(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	++(*i);
	cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
	cp_free(&my_shell->double_list, &cp_list);
	my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*j), (*i));
	my_shell->double_list[(*n)] = 0;
	return (NO_ERROR);
}
