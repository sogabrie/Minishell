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
	int i = 0;
	while (my_shell->double_list[i])
	{
		ft_echo(my_shell->double_list[i], -1);
		printf("|\n");
		++i;
	}
	i = 0;
	while (my_shell->double_list[i])
	{
		free(my_shell->double_list[i]);
		++i;
	}
	free(my_shell->double_list);
	my_shell->double_list = 0;
	//system("leaks minishell");
}