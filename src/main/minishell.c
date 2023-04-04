#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	my_shell;

	init_shell(my_shell);
	my_shell.my_envp = replace_envp(envp);
	if (argc >  1)
		return (2);
    while(1)
	{
    	my_shell.line = readline("minishell-1.0$ ");
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