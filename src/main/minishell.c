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

int main(int argc, char **argv, char **envp)
{
	t_shell	my_shell;

	init_shell(&my_shell);
	my_shell.full_name_here_doc = path_tmp();
	my_shell.start_here_doc = count_tmp_files(my_shell.full_name_here_doc);
	my_shell.start_here_doc_plus = my_shell.start_here_doc;
	my_shell.my_envp = replace_envp(envp);
	// int i = 0;
	// while (envp[i])
	// 	printf("%s\n", envp[i++]);
	printf("MMMMMMMMMMMMMMMMMMMMM\n");
	if (argc >  1)
		return (2);
    while(1)
	{
		rl_catch_signals = 0;
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