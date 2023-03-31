#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**my_envp;

	my_envp = replace_envp(envp);
	int i = 0;
	while (envp[i])
		printf("%s\n",envp[i++]);
	if (argc >  1)
		return (2);
    while(1)
	{
    	line = readline("minishell-1.0$ ");
		if (line)
		{
			add_history(line);
			// main_parsing(line, my_envp);
		}
		free(line);
	}
    return 0;
}