#include "minishell.h"
#include "struct.h"

int	check_metachar_and_redirect(char *c)
{
	if (!ft_strcmp(c, "&&") || !ft_strcmp(c, "||") \
	|| !ft_strcmp(c, "|") || !ft_strcmp(c, ">>") \
	|| !ft_strcmp(c, "<<") || !ft_strcmp(c, ">") \
	|| !ft_strcmp(c, "<"))
		return (6);
	return (0);
}

int	check_metachar_cont_2(t_shell	*my_shell, int i)
{
	int	c;

	c = i + 1;
	while (my_shell->double_list[c] && \
	!ft_strcmp(my_shell->double_list[c], " "))
		++c;
	if (!my_shell->double_list[c] || \
		check_metachar_and_redirect(my_shell->double_list[c]))
		return (6);
	return (0);
}

int	check_metachar_cont(t_shell	*my_shell, int i)
{
	int	c;

	c = i - 1;
	while (c >= 0 && (!ft_strcmp(my_shell->double_list[c], " ") || \
	!ft_strcmp(my_shell->double_list[c], ")") || \
	!ft_strcmp(my_shell->double_list[c], "(")))
		--c;
	if (c < 0 || check_metachar_and_redirect(my_shell->double_list[c]))
		return (5);
	c = i + 1;
	while (my_shell->double_list[c] && \
	(!ft_strcmp(my_shell->double_list[c], " ") || \
	!ft_strcmp(my_shell->double_list[c], ")") || \
	!ft_strcmp(my_shell->double_list[c], "(")))
		++c;
	if (!my_shell->double_list[c] || \
	!ft_strcmp(my_shell->double_list[c], "&&") \
	|| !ft_strcmp(my_shell->double_list[c], "||") \
	|| !ft_strcmp(my_shell->double_list[c], "|"))
		return (6);
	return (0);
}

int	check_metachar(t_shell	*my_shell)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (my_shell->double_list[i])
	{
		if (!ft_strcmp(my_shell->double_list[i], "&&") || \
		!ft_strcmp(my_shell->double_list[i], "||") || \
		!ft_strcmp(my_shell->double_list[i], "|"))
		{
			if (check_metachar_cont(my_shell, i))
				return (6);
		}
		else if (!ft_strcmp(my_shell->double_list[i], "<<") || \
		!ft_strcmp(my_shell->double_list[i], ">>") || \
		!ft_strcmp(my_shell->double_list[i], "<") || \
		!ft_strcmp(my_shell->double_list[i], ">"))
		{
			if (check_metachar_cont_2(my_shell, i))
				return (6);
		}
		++i;
	}
	return (0);
}
