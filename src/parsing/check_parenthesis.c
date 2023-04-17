#include "minishell.h"
#include "struct.h"

int	check_paren_cont_1(t_shell	*my_shell, int *i, int *c)
{
	(*c) = (*i) - 1;
	while ((*c) >= 0 && !ft_strcmp(my_shell->double_list[(*c)], " "))
		--(*c);
	if ((*c) < 0 || !ft_strcmp(my_shell->double_list[(*c)], "&&") \
	|| !ft_strcmp(my_shell->double_list[(*c)], "||") \
	|| !ft_strcmp(my_shell->double_list[(*c)], "("))
	{
		(*c) = (*i) + 1;
		while (my_shell->double_list[(*c)] && \
		!ft_strcmp(my_shell->double_list[(*c)], " "))
			++(*c);
		if (my_shell->double_list[(*c)] && \
		ft_strcmp(my_shell->double_list[(*c)], "&&") \
		&& ft_strcmp(my_shell->double_list[(*c)], "||") \
		&& ft_strcmp(my_shell->double_list[(*c)], "|") \
		&& ft_strcmp(my_shell->double_list[(*c)], ")"))
			++(*i);
		else
			return (6);
	}
	else
		return (6);
	return (0);
}

int	check_paren_cont_2(t_shell	*my_shell, int *i, int *c)
{
	(*c) = (*i) + 1;
	while (my_shell->double_list[(*c)] && \
	!ft_strcmp(my_shell->double_list[(*c)], " "))
		++(*c);
	if (!my_shell->double_list[(*c)] || \
	!ft_strcmp(my_shell->double_list[(*c)], "&&") \
	|| !ft_strcmp(my_shell->double_list[(*c)], "||") \
	|| !ft_strcmp(my_shell->double_list[(*c)], ")"))
	{
		(*c) = (*i) - 1;
		while ((*c) >= 0 && !ft_strcmp(my_shell->double_list[(*c)], " "))
			--(*c);
		if (c >= 0 && ft_strcmp(my_shell->double_list[(*c)], "&&") \
		&& ft_strcmp(my_shell->double_list[(*c)], "||") \
		&& ft_strcmp(my_shell->double_list[(*c)], "|") \
		&& ft_strcmp(my_shell->double_list[(*c)], "("))
			++(*i);
		else
			return (6);
	}
	else
		return (6);
	return (0);
}

int	check_paren_cont(t_shell	*my_shell)
{
	int	i;
	int	c;
	int	res;

	i = 0;
	c = 0;
	while (my_shell->double_list[i])
	{
		if (!ft_strcmp(my_shell->double_list[i], "("))
		{
			if (check_paren_cont_1(my_shell, &i, &c))
				return (errors_print_sintexs(my_shell, \
				my_shell->double_list[i], SYNT_ERROR));
		}
		else if (!ft_strcmp(my_shell->double_list[i], ")"))
		{
			if (check_paren_cont_2(my_shell, &i, &c))
				return (errors_print_sintexs(my_shell, \
				my_shell->double_list[i], SYNT_ERROR));
		}
		else
			++i;
	}
	return (0);
}

int	check_paren(t_shell	*my_shell)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (check_metachar(my_shell))
		return (6);
	while (my_shell->double_list[i])
	{
		if (!ft_strcmp(my_shell->double_list[i], "("))
			++c;
		else if (!ft_strcmp(my_shell->double_list[i], ")"))
			--c;
		if (c < 0)
			return (errors_print_sintexs(my_shell, \
			my_shell->double_list[i], SYNT_ERROR));
		++i;
	}
	if (c)
		return (errors_print_sintexs(my_shell, "(", SYNT_ERROR));
	return (check_paren_cont(my_shell));
}
