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
		printf("%s|\n", my_shell->double_list[i]);
		++i;
	}
	i = 0;
	while (my_shell->double_list[i])
	{
		free(my_shell->double_list[i]);
		++i;
	}
	free(my_shell->double_list);
	system("leaks minishell");
	// if (error != NO_ERROR)
	// 	quote_error(erroe);
	//control_exec(my_shell);
}