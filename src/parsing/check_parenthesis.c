#include "minishell.h"
#include "struct.h"

int	check_paren(t_shell	*my_shell)
{
	int	i;
	int	j;
	int	c;
	int	prior;

	i = 0;
	j = 0;
	prior = 0;
	while (my_shell->double_list[i])
	{
		if (!ft_strcmp(my_shell->double_list[i], "("))
			++prior;
		else if (!ft_strcmp(my_shell->double_list[i], ")"))
			--prior;
		if (prior < 0)
			return (6);
		++i;
	}
	if (prior)
		return (6);
	i = 0;
	//write (1, "pr_1\n", 5);
	while (my_shell->double_list[i])
	{
		if (!ft_strcmp(my_shell->double_list[i], "("))
		{
			c = i - 1;
			while (c >= 0 && !ft_strcmp(my_shell->double_list[c], " "))
				--c;
			if (c < 0  || !ft_strcmp(my_shell->double_list[c], "&&") \
			|| !ft_strcmp(my_shell->double_list[c], "||") \
			|| !ft_strcmp(my_shell->double_list[c], "|") \
			|| !ft_strcmp(my_shell->double_list[c], "("))
			{
				c = i + 1;
				while (my_shell->double_list[c] && !ft_strcmp(my_shell->double_list[c], " "))
					++c;
				if (my_shell->double_list[c] && ft_strcmp(my_shell->double_list[c], "&&") \
				&& ft_strcmp(my_shell->double_list[c], "||") \
				&& ft_strcmp(my_shell->double_list[c], "|") \
				&& ft_strcmp(my_shell->double_list[c], ")"))
					++i;
				else
					return (6);
			}
			else
				return (6);
		}
		else if (!ft_strcmp(my_shell->double_list[i], ")"))
		{
			c = i + 1;
			//write(1,my_shell->double_list[i], 5);
			while (my_shell->double_list[c] && !ft_strcmp(my_shell->double_list[c], " "))
				++c;
			//write(1, "aa_1", 5);
			if (!my_shell->double_list[c] || !ft_strcmp(my_shell->double_list[c], "&&") \
			|| !ft_strcmp(my_shell->double_list[c], "||") \
			|| !ft_strcmp(my_shell->double_list[c], "|") \
			|| !ft_strcmp(my_shell->double_list[c], ")"))
			{
				c = i - 1;
				while (c >= 0 && !ft_strcmp(my_shell->double_list[c], " "))
					--c;
				if (c >= 0  && ft_strcmp(my_shell->double_list[c], "&&") \
				&& ft_strcmp(my_shell->double_list[c], "||") \
				&& ft_strcmp(my_shell->double_list[c], "|") \
				&& ft_strcmp(my_shell->double_list[c], "("))
					++i;
				else
					return (6);
			}
			else
				return (6);
			//write(1, "aa_2", 5);
		}
		else
			++i;
	}
	return (0);
}