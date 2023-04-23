#include "minishell.h"
#include <signal.h>

void	sigint_pars(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
	(void)sig;
}

// void	signal_pars(int action)
// {
// 	if (action == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 	}
// 	else if (action == 1)
// 	{
// 		signal(SIGINT, sigint_handler);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	else if (action == 2)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// }


int main(int argc, char **argv, char **envp)
{
	t_shell	my_shell;

	init_shell(&my_shell);
	my_shell.my_envp = replace_envp(envp);
	// int i = 0;
	// while (envp[i])
	// 	printf("%s\n", envp[i++]);
	printf("MMMMMMMMMMMMMMMMMMMMM\n");
	if (argc >  1)
		return (2);
    while(1)
	{
		// signal_handler(1);
		rl_catch_signals = 0;
		// sigemptyset(0);
		signal(SIGINT, sigint_pars);
		signal(SIGQUIT, SIG_IGN);
    	my_shell.line = readline("minishell-1.0$ ");
		if (!my_shell.line)
		{
			
			// write(1, "exit", 5);
			// rl_on_new_line();
			// rl_replace_line("exit", 1);
			write(1, "exit\n", 6);
   			// rl_redisplay();
			// write(1, "exit", 5);
			exit(my_shell.error_status);
		}
		if (my_shell.line && ft_strlen(my_shell.line))
		{
			add_history(my_shell.line);
			main_parsing(&my_shell);
		}
		free(my_shell.line);
		my_shell.line = 0;
	}
    return 0;
}