#include "minishell.h"
#include "struct.h"

void	sigint_pars_exe_1(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	sigquit_pars_exe_1(int sig)
{
	write(1, "Quit: 3\n", 9);
	(void)sig;
}

void	main_parsing(t_shell	*my_shell)
{
	my_shell->double_list = 0;
	if (!control_pars(my_shell, 0, 0, 0) && !check_paren(my_shell))
	{
		creat_delimiter(my_shell);
		if (!control_parsing(my_shell))
		{
			signal(SIGINT, sigint_pars_exe_1);
			signal(SIGQUIT, sigquit_pars_exe_1);
			make_exe(my_shell, 0, my_shell->count);
		}
	}
	free_struct(my_shell);
	// system("leaks minishell");
}
