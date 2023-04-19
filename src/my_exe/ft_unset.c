// #include "minishell.h"

// int	valid_unset(char *arg, int *error_code)
// {
// 	size_t	i;

// 	i = 0;
// 	if(ft_strchr("0123456789!@%^ \'\"&*()-+={}[]|?/><~`;:.,\\", arg[0]))
// 	{
// 		exe_error(arg, 98, " unset:" );
// 		return (1);
// 	}

// }

// int	ft_unset(char **args, char ***envp)
// {
// 	size_t	i;
// 	int		error_code;

// 	error_code = 0;
// 	while (args[i])
// 	{
// 		if (args[i][0] == '#')
// 			break ;
// 		if (valid_unset(args[i], &error_code))
// 			return (1);
// 		i++; 
// 	}
// 	return (error_code);
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	// char **my_envp = replace_envp(envp);
// 	char **str = ft_split("a$HOME$sfasf$HOME\'fasfas", ' ');
// 	// int error = ft_unset(str, &my_envp);
// 	// for(int i = 0; my_envp[i]; i++)
// 		// printf("%s\n", my_envp[i]);
// 	// printf("error number = %d\n", error);
// 	return (0);
// }
