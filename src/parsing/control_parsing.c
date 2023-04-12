#include "struct.h"
#include "minishell.h"

int	control_pars_exe(t_shell *my_shell, int start, int end)
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
	while (i < end && my_shell->double_list[i]  && ft_strcmp(my_shell->double_list[i], ")"))
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
			if (creat_my_exe(my_shell, my_shell->double_list[i++]))
				return (7);
		}
		else if (!ft_strcmp(my_shell->double_list[i], "<") || \
		!ft_strcmp(my_shell->double_list[i], "<<") || \
		!ft_strcmp(my_shell->double_list[i], ">") || \
		!ft_strcmp(my_shell->double_list[i], ">>"))
		{
			creat_redirect(my_shell, &i);
		}
		else if (i == start || my_shell->check_exe == -1)
		{
			if (creat_exe(my_shell, my_shell->double_list[i++]))
				return (7);
		}
		else if (ft_strcmp(my_shell->double_list[i], " "))
		{
			add_option(my_shell, my_shell->double_list[i++]);
		}
		else
			++i;
	}
	while (i < end && my_shell->double_list[i] && (!ft_strcmp(my_shell->double_list[i], " ") || \
	!ft_strcmp(my_shell->double_list[i], ")")))
	{
		if (!ft_strcmp(my_shell->double_list[i], ")"))
		{
			if (creat_struct_prioritet_end(my_shell))
				return (9);
		}
		++i;
	}
	if (my_shell->control[my_shell->check_exe]->command_type == EXE)
	{
		my_shell->control[my_shell->check_exe]->exe->fd_input = my_shell->fd_input;
		my_shell->control[my_shell->check_exe]->exe->fd_output = my_shell->fd_output;
	}
	if (my_shell->control[my_shell->check_exe]->command_type == MY_EXE)
	{
		my_shell->control[my_shell->check_exe]->my_exe->fd_input = my_shell->fd_input;
		my_shell->control[my_shell->check_exe]->my_exe->fd_output = my_shell->fd_output;
	}
	my_shell->check_exe = -1;
	my_shell->fd_output = 1;
	my_shell->fd_input = 0;
	return (0);
}

int	control_parsing(t_shell	*my_shell)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i <= my_shell->delimiter_count)
	{
		start = end;
		if (i < my_shell->delimiter_count)
		{
			end = my_shell->delimiter[i];
		}
		else
		{
			while(my_shell->double_list[end])
				++end;
			++end;
		}
		control_pars_exe(my_shell, start, end);
		if (i < my_shell->delimiter_count && \
		(start || my_shell->double_list[end]))
		{
			if (!ft_strcmp(my_shell->double_list[end], "|"))
				creat_struct_pip(my_shell);
			else if (!ft_strcmp(my_shell->double_list[end], "||"))
				creat_struct_or(my_shell);
			else if (!ft_strcmp(my_shell->double_list[end], "&&"))
				creat_struct_and(my_shell);
		}
		++i;
		++end;
	}
	return (0);
}
