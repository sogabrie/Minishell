#include "minishell.h"

int	valid_unset(char *arg, int *error_code, char **envp, size_t i)
{
	if (ft_strchr("!@%^&*()-+=0123456 789\'\"{}$[]:;|~<>,.?/", arg[0])
		|| (arg[0] == '$' && arg[1] == '\0'))
	{
		exe_error(arg, 98, " unset: ");
		return (1);
	}
	while (arg[++i])
	{
		if (ft_strchr("!@#%^&*v()-+=[]{}\\|\'\";:,.$/~`><", arg[i]))
		{
			exe_error(arg, 98, " unset: ");
			return (1);
		}
	}
	return (0);
}

int	check_exists(char **envp, char *str)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(str, envp[i], ft_strlen(str)))
			return (0);
	return (1);
}

char	**delete_variable(char **envp, char *str, char **new_envp, size_t j)
{
	size_t	i;

	i = 0;
	if (check_exists(envp, str))
		return (envp);
	while (envp[i])
		i++;
	new_envp = ft_calloc(i, sizeof(char *));
	if (new_envp == NULL)
		malloc_error();
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], ft_strlen(str)))
			i++;
		else
		{
			new_envp[j] = ft_strdup(envp[i++]);
			if (new_envp[j++] == NULL)
				malloc_error();
		}
	}
	two_dimensional_mas(&envp);
	return (new_envp);
}

int	ft_unset(char **args, char ***envp)
{
	int		i;
	int		error_code;

	error_code = 0;
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '#')
			break ;
		if (valid_unset(args[i], &error_code, *envp, 1))
		{
			error_code = 1;
			continue ;
		}
		*envp = delete_variable(*envp, args[i], NULL, 0);
		error_code = 0;
	}
	return (error_code);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **my_envp = replace_envp(envp);
// 	for(int i = 0 ;my_envp[i]; i++)
// 		printf("%s\n", my_envp[i]);
// 	// printf("\n\n");
// 	char **str = ft_split("$PATH PATH asf", ' ');
// 	printf("%d\n", ft_unset(str, &my_envp));
// 	system("leaks minishell");
// 	// ft_export(str, &my_envp, -1, NULL);
// 	for(int i = 0 ;my_envp[i]; i++)
// 		printf("%s\n", my_envp[i]);
// 	// my_envp = replace_envp(my_envp);
// 	// for(int i = 0; my_envp[i]; i++)
// 		// printf("%s\n", my_envp[i]);
// 	// char **str = ft_split("*home", ' ');
// 	// int error = ft_unset(str, &my_envp);
// 	// for(int i = 0; my_envp[i]; i++)
// 		// printf("%s\n", my_envp[i]);
// 	// printf("error number = %d\n", error);
// 	// system("leaks minishell");
// 	return (0);
// }
