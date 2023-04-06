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
	while (my_shell->double_list[i])
	{
		ft_echo(my_shell->double_list[i], 1);
		//printf("|\n");
		++i;
	}
	printf("\n");
	i = 0;
	printf("delimiter_count = %d delimiter -", my_shell->delimiter_count);
	while (i < my_shell->delimiter_count)
	{
		printf(" %d |", my_shell->delimiter[i++]);
	}
	printf("\n");
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
	system("leaks minishell");
}