#include "minishell.h"

int	ft_export(char **str, char ***envp)
{
	int	i;
	int	flag_mas;

	i = -1;
	flag_mas = 0;
	if (str[0] == NULL || str[0][0] == '#')
		return (ft_env(*envp, 1));
	while (str[++i])
	{
		if (valid_variable(str[i], *envp, &flag_mas))
			continue ;

	}
	return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **my_envp = replace_envp(envp);
// 	char **str = ft_split("Linu", ' ');
// 	ft_export(str, &my_envp);
// }