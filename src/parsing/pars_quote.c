#include "minishell.h"
#include "struct.h"

t_error_type	control_pars_1_2(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	if (!my_shell->line[(*i)])
		return (SYNT_ERROR);
	else
	{
		++(*i);
		cp_list = malloc((size_list(my_shell->double_list) + 2) \
		* sizeof(char *));
		if (!cp_list)
			malloc_error();
		cp_free(&my_shell->double_list, &cp_list);
		my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*j), (*i));
		my_shell->double_list[(*n)] = 0;
		(*j) = (*i);
	}
	return (NO_ERROR);
}

t_error_type	control_pars_1(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	if ((*j) != (*i))
	{
		cp_list = malloc((size_list(my_shell->double_list) + 2) \
		* sizeof(char *));
		if (!cp_list)
			malloc_error();
		cp_free(&my_shell->double_list, &cp_list);
		my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*j), (*i));
		my_shell->double_list[(*n)] = 0;
		(*j) = (*i);
	}
	++(*i);
	while (my_shell->line[(*i)] != '\'' && my_shell->line[(*i)] != 0)
		++(*i);
	return (control_pars_1_2(my_shell, i, j, n));
}

void	control_pars_6(t_shell *my_shell, int *i, int *j, int *n)
{
	if (my_shell->line[(*i)] == '\'')
		my_shell->my_error = control_pars_1(my_shell, i, j, n);
	else if (my_shell->line[(*i)] == '"')
		my_shell->my_error = control_pars_2(my_shell, i, j, n);
	else if ((my_shell->line[(*i)] == '|' \
	&& my_shell->line[(*i) + 1] == '|') || \
	(my_shell->line[(*i)] == '&' && my_shell->line[(*i) + 1] == '&') || \
	(my_shell->line[(*i)] == '<' && my_shell->line[(*i) + 1] == '<') || \
	(my_shell->line[(*i)] == '>' && my_shell->line[(*i) + 1] == '>'))
		my_shell->my_error = control_pars_3(my_shell, i, j, n);
	else if (my_shell->line[(*i)] == '|' || my_shell->line[(*i)] == '<' || \
	my_shell->line[(*i)] == '>' || my_shell->line[(*i)] == ')' || \
	my_shell->line[(*i)] == '(' || my_shell->line[(*i)] == ' ')
		my_shell->my_error = control_pars_4(my_shell, i, j, n);
	else if (my_shell->line[(*i) + 1] == 0)
		my_shell->my_error = control_pars_5(my_shell, i, j, n);
	else
		++(*i);
}

t_error_type	control_pars(t_shell *my_shell, int i, int j, int n)
{
	char	a[2];

	a[1] = 0;
	while (my_shell->line[i])
	{
		a[0] = my_shell->line[i];
		control_pars_6(my_shell, &i, &j, &n);
		if (my_shell->my_error != NO_ERROR)
			return (errors_print_sintexs(my_shell, a, SYNT_ERROR));
	}
	return (my_shell->my_error);
}
