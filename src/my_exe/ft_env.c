#include "minishell.h"

void	print_export(char **envp, int i, int j, int f_h)
{
	while (envp[++i])
	{
		printf("declare -x ");
		while (envp[i][++j] != '\0')
		{
			if (envp[i][j - 1] == '=')
			{
				f_h = 1;
				printf("%c", '"');
			}
			printf("%c", envp[i][j]);
		}
		if (envp[i][j - 1] == '=')
			printf("%c%c", '"', '"');
		if (f_h == 1)
			printf("%c", '"');
		f_h = 0;
		j = -1;
		printf("\n");
	}
}

int	ft_env(char **envp, int f_export)
{
	size_t	i;

	i = 0;
	if (f_export == 0)
	{
		while (envp[i])
		{
			if (ft_strchr(envp[i], '='))
				printf("%s\n", envp[i]);
			i++;
		}
		return (0);
	}
	print_export(envp, -1, -1, 0);
	return (0);
}
