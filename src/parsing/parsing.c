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
	int i = 0;
	if (check_paren(my_shell))
	{
		printf("ERROR ( OR )\n");
		while (my_shell->double_list[i])
		{
			free(my_shell->double_list[i]);
			++i;
		}
		free(my_shell->double_list);
		free(my_shell->delimiter);
		my_shell->delimiter_count = 0;
		my_shell->delimiter = 0;
		my_shell->double_list = 0;
		return ;
	}
	control_parsing(my_shell);
	while (my_shell->double_list[i])
	{
		ft_echo(my_shell->double_list[i], 1);
		printf("|\n");
		++i;
	}
	printf("\n");
	i = 0;
	//printf("delimiter_count = %d delimiter -", my_shell->delimiter_count);
	// while (i < my_shell->delimiter_count)
	// {
	// 	printf(" %d |", my_shell->delimiter[i++]);
	// }
	// printf("\n");
	i = 0;
	while (i < my_shell->count)
	{
		if (my_shell->control[i]->command_type == EXE)
		{
			printf("EXE = %s\n",my_shell->control[i]->exe->full_name);
		}
		if (my_shell->control[i]->command_type == MY_EXE)
		{
			printf("MY_EXE = %s\n",my_shell->control[i]->my_exe->name);
		}
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{
			printf("PRIORITET_START \n");
		}
		if (my_shell->control[i]->command_type == PRIORITET_END)
		{
			printf("PRIORITET_END \n");
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
	i = 0;
	while (my_shell->double_list[i])
	{
		free(my_shell->double_list[i]);
		++i;
	}
	free(my_shell->double_list);
	free(my_shell->delimiter);
	my_shell->delimiter_count = 0;
	my_shell->delimiter = 0;
	my_shell->double_list = 0;
	my_shell->check_exe = -1;
	//system("leaks minishell");
}