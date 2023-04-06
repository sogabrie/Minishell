#include "minishell.h"
#include "struct.h"

// void	control_exec(t_shell	*my_shell)
// {
// 	int	i;
// 	int	exe_num;

// 	i = 0;
// 	exe_num = -1;
// 	while (my_shell->double_list[i])
// 	{
// 		my_shell->full_path = get_path(my_shell->my_envp);
// 		if (check_my_exe(my_shell->double_list[i]))
// 		{
// 			//exe_num = i;
// 			my_shell->control = add_control(my_shell);
// 			if (!my_shell->control)
// 				return (5);
// 			my_shell->control[my_shell->count - 1]->my_exe = malloc(sizeof (t_my_exe));
// 			if (!my_shell->control[my_shell->count]->my_exe)
// 				return (5);
// 			my_shell->control[my_shell->count - 1]->my_exe->name = my_shell->double_list[i];
// 			my_shell->control[my_shell->count - 1]->command_type = MY_EXE;
// 			my_shell->control[my_shell->count - 1]->error = NO_ERROR;
// 			++i;
// 			while (!check_end(my_shell->double_list[i]))
// 			{
// 				if (check_redirect(my_shell->double_list[i]))
// 				{
					
// 				}
// 				else if (!ft_strcmp(my_shell->double_list[i], "("))
// 				{
					
// 				}
// 				else if (!ft_strcmp(my_shell->double_list[i], ")"))
// 				{

// 				}
// 				else
// 				{
// 					add_options(my_shell->control[my_shell->count - 1]->my_exe->options);
// 					++i;
// 				}
// 			}
// 		}
// 		else if (check_redirect(my_shell->double_list[i]))
// 		{

// 		}
// 		else if (!ft_strcmp(my_shell->double_list[i], ")"))
// 		{

// 		}
// 		else if (!ft_strcmp(my_shell->double_list[i], "("))
// 		{

// 		}
// 		else if (!check_procces(my_shell->double_list[i], my_shell->full_path, 0, 0))
// 		{

// 		}
// 		else
// 		{
// 			my_shell->control = malloc(sizeof (t_control));
// 			if (my_shell->control)
// 				return (5);
// 			my_shell->control->error = C_N_F;
// 			while (!check_end(my_shell->double_list[i]))
// 			{
				
// 			}
// 		}

// 	}
// }

void	main_parsing(t_shell	*my_shell)
{
	t_error_type	error;

	my_shell->double_list = 0;
	error = control_pars(my_shell, 0, 0, 0);
	int i = 0;
	if (check_paren(my_shell))
	{
		printf("ERROR ( OR )\n");
		free(my_shell->double_list);
		my_shell->double_list = 0;
		return ;
	}
	while (my_shell->double_list[i])
	{
		ft_echo(my_shell->double_list[i], 1);
		printf("|\n");
		++i;
	}
	printf("\n");
	i = 0;
	while (my_shell->double_list[i])
	{
		free(my_shell->double_list[i]);
		++i;
	}
	free(my_shell->double_list);
	my_shell->double_list = 0;
	system("leaks minishell");
}