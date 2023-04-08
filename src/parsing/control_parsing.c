#include "struct.h"
#include "minishell.h"

int	control_pars_exe(t_shell *my_shell, int start, int end, int *j)
{
	int	i;

	while (!ft_strcmp(my_shell->double_list[start], " ") || \
	!ft_strcmp(my_shell->double_list[start], "("))
	{
		if (!ft_strcmp(my_shell->double_list[start], "("))
		{
			if (creat_struct_prioritet_start(my_shell))
				return (9);
		}
		++start;
	}
	i = start;
	while (i < end && ft_strcmp(my_shell->double_list[i], ")"))
	{
		if ((!ft_strcmp(my_shell->double_list[i], "echo") || \
		!ft_strcmp(my_shell->double_list[i], "cd") || \
		!ft_strcmp(my_shell->double_list[i], "pwd") || \
		!ft_strcmp(my_shell->double_list[i], "export") || \
		!ft_strcmp(my_shell->double_list[i], "unset") || \
		!ft_strcmp(my_shell->double_list[i], "env") || \
		!ft_strcmp(my_shell->double_list[i], "exit")) \
		&& my_shell->check_exe == -1)
		{
			if (creat_my_exe(my_shell, my_shell->double_list[i]))
				return (7);
			my_shell->check_exe = my_shell->count;
		}
		else if (!ft_strcmp(my_shell->double_list[i], "<") || \
		!ft_strcmp(my_shell->double_list[i], "<<") || \
		!ft_strcmp(my_shell->double_list[i], ">") || \
		!ft_strcmp(my_shell->double_list[i], ">>"))
		{
			if (creat_redirect(my_shell, i))
				return (8);
		}
		else if (i == start || my_shell->check_exe == -1)
		{
			if (creat_exe(my_shell, my_shell->double_list[i]))
				return (7);
			my_shell->check_exe = my_shell->count;
		}
		else if (ft_strcmp(my_shell->double_list[i], " "))
		{
			// vercnel vorpes option
		}
		++i;
	}
	while ((!ft_strcmp(my_shell->double_list[i], " ") || \
	!ft_strcmp(my_shell->double_list[i], ")")) && i < end)
	{
		if (!ft_strcmp(my_shell->double_list[i], ")"))
		{
			if (creat_struct_prioritet_start(my_shell))
				return (9);
		}
		++i;
	}
	my_shell->check_exe = -1;
	return (0);
}

int	control_parsing(t_shell	*my_shell)
{
	int	i;
	int	start;
	int	end;
	int	j;

	i = 0;
	start = 0;
	end = 0;
	while (i <= my_shell->delimiter_count)
	{
		start = end;
		if (i < my_shell->delimiter_count)
			end = my_shell->delimiter[i];
		else
		{
			while(my_shell->double_list[end])
				++end;
			++end;
		}
		control_pars_exe(my_shell, start, end, &j);
		++i;
		if (i > my_shell->delimiter_count && \
		(start || my_shell->double_list[end]))
		{
			if (!ft_strcmp(my_shell->double_list[i], "|"))
				creat_struct_pip(my_shell);
			else if (!ft_strcmp(my_shell->double_list[i], "||"))
				creat_struct_or(my_shell);
			else if (!ft_strcmp(my_shell->double_list[i], "&&"))
				creat_struct_and(my_shell);
		}
	}
	return (0);
}
