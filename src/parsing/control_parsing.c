#include "struct.h"
#include "minishell.h"


void	control_pars_exe_2(t_shell *my_shell, int *start, int *end, int *i)
{
	//char	cp;

	//cp = echo_line(my_shell->double_list[i])
	// if (control_pars_exe_2_2(my_shell, i) \
	// && my_shell->check_exe == -1)
	// 	creat_my_exe(my_shell, my_shell->double_list[(*i)]);
	if (!ft_strcmp(my_shell->double_list[(*i)], "<") || \
	!ft_strcmp(my_shell->double_list[(*i)], "<<") || \
	!ft_strcmp(my_shell->double_list[(*i)], ">") || \
	!ft_strcmp(my_shell->double_list[(*i)], ">>"))
		my_shell->my_error = creat_redirect(my_shell, i);
	else if (i == start || my_shell->check_exe == -1)
		creat_exe(my_shell, i);
	else if (ft_strcmp(my_shell->double_list[(*i)], " "))
		add_option(my_shell, i);
	++(*i);
}

void	control_pars_exe_1(t_shell *my_shell, int *start, int *end, int *i)
{
	while (!ft_strcmp(my_shell->double_list[*start], " ") || \
	!ft_strcmp(my_shell->double_list[*start], "("))
	{
		if (!ft_strcmp(my_shell->double_list[*start], "("))
			creat_struct_prioritet_start(my_shell);
		++(*start);
	}
	(*i) = (*start);
}

void	control_pars_exe_3(t_shell *my_shell, int *end, int *i)
{
	while ((*i) < (*end) && my_shell->double_list[(*i)] && \
	(!ft_strcmp(my_shell->double_list[(*i)], " ") || \
	!ft_strcmp(my_shell->double_list[(*i)], ")")))
	{
		if (!ft_strcmp(my_shell->double_list[(*i)], ")"))
			creat_struct_prioritet_end(my_shell);
		++(*i);
	}
}

void	control_pars_exe_4(t_shell *my_shell)
{
	// if (my_shell->control[my_shell->check_exe]->command_type \
	// == EXE)
	// {
		my_shell->control[my_shell->check_exe]->exe->fd_input \
		= my_shell->fd_input;
		my_shell->control[my_shell->check_exe]->exe->fd_output \
		= my_shell->fd_output;
		if (my_shell->fd_input != 0)
			my_shell->control[my_shell->check_exe]->exe->flag_input = 0;
		else
			my_shell->control[my_shell->check_exe]->exe->flag_input = 1;
		if (my_shell->fd_output != 1)
			my_shell->control[my_shell->check_exe]->exe->flag_output = 0;
		else
			my_shell->control[my_shell->check_exe]->exe->flag_output = 1;

	// }
	// if (my_shell->control[my_shell->check_exe]->command_type == MY_EXE)
	// {
	// 	my_shell->control[my_shell->check_exe]->my_exe->fd_input \
	// 	= my_shell->fd_input;
	// 	my_shell->control[my_shell->check_exe]->my_exe->fd_output \
	// 	= my_shell->fd_output;
	// 	if (my_shell->fd_input != 0)
	// 		my_shell->control[my_shell->check_exe]->my_exe->flag_input = 0;
	// 	else
	// 		my_shell->control[my_shell->check_exe]->my_exe->flag_input = 1;
	// 	if (my_shell->fd_output != 1)
	// 		my_shell->control[my_shell->check_exe]->my_exe->flag_output = 0;
	// 	else
	// 		my_shell->control[my_shell->check_exe]->my_exe->flag_output = 1;
	// }
	my_shell->control[my_shell->check_exe]->error = my_shell->my_error;
}

void	control_pars_exe_5(t_shell *my_shell)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = NO_EXE;
	my_shell->check_exe = my_shell->count - 1 ;
	my_shell->control[my_shell->check_exe]->error = my_shell->my_error;
	
}

void	control_pars_exe(t_shell *my_shell, int start, int end)
{
	int		i;
 
	control_pars_exe_1(my_shell, &start, &end, &i);
	while (i < end && my_shell->double_list[i] && \
	ft_strcmp(my_shell->double_list[i], ")"))
	{
		control_pars_exe_2(my_shell, &start, &end, &i);
	}
	control_pars_exe_3(my_shell, &end, &i);
	if (my_shell->check_exe >= 0)
		control_pars_exe_4(my_shell);
	else
		control_pars_exe_5(my_shell);
	my_shell->check_exe = -1;
	my_shell->fd_output = 1;
	my_shell->fd_input = 0;
	my_shell->my_error = NO_ERROR;
}

void	control_parsing_2(t_shell *my_shell, int start, int end, int i)
{
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
}

void	control_parsing(t_shell	*my_shell)
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
		control_parsing_2(my_shell, start, end, i);
		++i;
		++end;
	}
}
