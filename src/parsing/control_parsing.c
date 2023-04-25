#include "struct.h"
#include "minishell.h"

int	control_pars_exe(t_shell *my_shell, int start, int end)
{
	int		i;
	int		j;

	j = 0;
	control_pars_exe_1(my_shell, &start, &end, &i);
	while (!j && i < end && my_shell->double_list[i] && \
	ft_strcmp(my_shell->double_list[i], ")"))
		j = control_pars_exe_2(my_shell, &start, &end, &i);
	control_pars_exe_3(my_shell, &end, &i);
	if (my_shell->check_exe >= 0)
		control_pars_exe_4(my_shell);
	else
		control_pars_exe_5(my_shell);
	my_shell->check_exe = -1;
	my_shell->fd_output = 1;
	my_shell->fd_input = 0;
	my_shell->my_error = NO_ERROR;
	return (j);
}

int	control_parsing_2(t_shell *my_shell, int start, int end, int i)
{
	if (control_pars_exe(my_shell, start, end))
		return (1);
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
			end = my_shell->delimiter[i];
		else
		{
			while (my_shell->double_list[end])
				++end;
			++end;
		}
		if (control_parsing_2(my_shell, start, end, i))
			return (1);
		++i;
		++end;
	}
	return (0);
}
