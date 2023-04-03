#include "minishell.h"
#include "struct.h"

t_error_type	control_pars_1_2(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	if (!my_shell->line[(*i)])
	{
		printf("ERROR");
		exit(5);
	}
	else
	{
		++(*i);
		cp_list = malloc((size_list(my_shell->double_list) + 2) \
		* sizeof(char *));
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

t_error_type	control_pars_2_2(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	if (!my_shell->line[(*i)])
	{
		printf("ERROR");
		exit(5);
	}
	else
	{
		++(*i);
		cp_list = malloc((size_list(my_shell->double_list) + 2) \
		* sizeof(char *));
		cp_free(&my_shell->double_list, &cp_list);
		my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*j), (*i));
		my_shell->double_list[(*n)] = 0;
		(*j) = (*i);
	}
	return (NO_ERROR);
}

t_error_type	control_pars_2(t_shell *my_shell, int *i, int *j, int *n)
{
	char	**cp_list;

	if ((*j) != (*i))
	{
		cp_list = malloc((size_list(my_shell->double_list) + 2) \
		* sizeof(char *));
		cp_free(&my_shell->double_list, &cp_list);
		my_shell->double_list[(*n)++] = my_cat(my_shell->line, (*j), (*i));
		my_shell->double_list[(*n)] = 0;
		(*j) = (*i);
	}
	++(*i);
	while (my_shell->line[(*i)] != '"' && my_shell->line[(*i)] != 0)
		++(*i);
	return (control_pars_2_2(my_shell, i, j, n));
}



t_error_type	control_pars(t_shell *my_shell, int i, int j, int n)
{
	t_error_type	my_error;

	my_error = NO_ERROR;
	while (my_shell->line[i])
	{
		if (my_shell->line[i] == '\'')
			my_error = control_pars_1(my_shell, &i, &j, &n);
		else if (my_shell->line[i] == '"')
			my_error = control_pars_2(my_shell, &i, &j, &n);
		else if ((my_shell->line[i] == '|' && my_shell->line[i + 1] == '|') || \
		(my_shell->line[i] == '&' && my_shell->line[i + 1] == '&') || \
		(my_shell->line[i] == '<' && my_shell->line[i + 1] == '<') || \
		(my_shell->line[i] == '>' && my_shell->line[i + 1] == '>'))
			my_error = control_pars_3(my_shell, &i, &j, &n);
		else if (my_shell->line[i] == '|' || my_shell->line[i] == '<' || \
		my_shell->line[i] == '>' || my_shell->line[i] == ')' || \
		my_shell->line[i] == '(' || my_shell->line[i] == ' ')
			my_error = control_pars_4(my_shell, &i, &j, &n);
		else if (my_shell->line[i + 1] == 0)
			my_error = control_pars_5(my_shell, &i, &j, &n);
		else
			++i;
		if (my_error != NO_ERROR)
			return (my_error);
	}
	return (my_error);
}
