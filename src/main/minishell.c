#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	*my_shell;

	creat_shell(my_shell);
	my_shell.my_envp = replace_envp(envp);
	// int i = 0;
	// while (envp[i])
	// 	printf("%s\n",envp[i++]);
	if (argc >  1)
		return (2);
    while(1)
	{
    	my_shell.line = readline("minishell-1.0$ ");
		if (line)
		{
			add_history(my_shell.line);
			// main_parsing(&my_shell);
		}
		free(my_shell.line);
		my_shell.line = 0;
	}
    return 0;
}