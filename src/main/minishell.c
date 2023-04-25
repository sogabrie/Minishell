#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	sigint_pars(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	(void)sig;
}

void	go_minishell(t_shell *my_shell, struct termios *conf)
{
	while (1)
	{
		tcsetattr(0, TCSANOW, conf);
		signal(SIGINT, sigint_pars);
		signal(SIGQUIT, SIG_IGN);
		my_shell->line = readline("minishell-1.0$ ");
		if (!my_shell->line)
		{
			write(1, "exit\n", 6);
			exit(my_shell->error_status);
		}
		if (my_shell->line && ft_strlen(my_shell->line))
		{
			add_history(my_shell->line);
			main_parsing(my_shell);
		}
		free(my_shell->line);
		my_shell->line = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell			my_shell;
	struct termios	conf;

	tcgetattr(0, &conf);
	init_shell(&my_shell);
	my_shell.full_name_here_doc = path_tmp();
	my_shell.start_here_doc = count_tmp_files(my_shell.full_name_here_doc);
	my_shell.start_here_doc_plus = my_shell.start_here_doc;
	my_shell.my_envp = replace_envp(envp);
	rl_catch_signals = 0;
	printf("MMMMMMMMMMMMMMMMMMMMM\n");
	if (argc > 1)
		return (2);
	go_minishell(&my_shell, &conf);
	return (0);
}
