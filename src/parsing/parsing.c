#include "minishell.h"
#include "struct.h"

// void	control_exec(t_shell	*my_shell)
// {
	
// }

void	main_parsing(t_shell	*my_shell)
{
	t_error_type	error;

	my_shell->double_list = 0;
	error = control_pars(my_shell, 0, 0, 0);
	creat_delimiter(my_shell);
	if (check_paren(my_shell))
	{
		printf("ERROR ( OR )\n");
		free_struct(my_shell);
		return ;

	}
	control_parsing(my_shell);
	int i = 0;
	// while (my_shell->double_list[i])
	// {
	// 	ft_echo(my_shell->double_list[i], 1);
	// 	printf("|\n");
	// 	++i;
	// }
	i = 0;
	while (i < my_shell->count)
	{
		if (my_shell->control[i]->command_type == EXE)
		{
			printf("EXE = %s intpt = %d output = %d\n",my_shell->control[i]->exe->full_name, \
			my_shell->control[i]->exe->fd_input, my_shell->control[i]->exe->fd_output);
			int j = 0;
			while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j])
				printf("	Options = %s\n", my_shell->control[i]->exe->options[j++]);
		}
		if (my_shell->control[i]->command_type == MY_EXE)
		{
			printf("MY_EXE = %s intpt = %d output = %d\n",my_shell->control[i]->my_exe->name, \
			my_shell->control[i]->my_exe->fd_input, my_shell->control[i]->my_exe->fd_output);
			int j = 0;
			while (my_shell->control[i]->my_exe->options && my_shell->control[i]->my_exe->options[j])
				printf("	Options = %s\n", my_shell->control[i]->my_exe->options[j++]);
		}
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{
			printf("PRIORITET_START  start = %d end = %d \n",my_shell->control[i]->prioritet_start->start , my_shell->control[i]->prioritet_start->end);
		}
		if (my_shell->control[i]->command_type == PRIORITET_END)
		{
			printf("PRIORITET_END  start = %d end = %d \n",my_shell->control[i]->prioritet_end->start , my_shell->control[i]->prioritet_end->end);
		}
		if (my_shell->control[i]->command_type == LOGIC_AND)
		{
			printf("LOGIC_AND \n");
		}
		if (my_shell->control[i]->command_type == LOGIC_OR)
		{
			printf("LOGIC_OR \n");
		}
		if (my_shell->control[i]->command_type == PIPE)
		{
			printf("PIPE \n");
		}
		++i;
	}

	free_struct(my_shell);
	//system("leaks minishell");
}