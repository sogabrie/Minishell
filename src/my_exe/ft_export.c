// #include "minishell.h"


// int	check_inside(char *str, size_t start, int *flag_mas)
// {
// 	start++;
// 	if (str[start] == '(' && str[start + 1] == ')' &&
// 		(ft_strlen(str) - start) == 2)
// 	{
// 		*flag_mas = 2;
// 		return (0);
// 	}
// 	if (str[start] == '=' && str[start + 1] == '(' && 
// 		str[ft_strlen(str) - 1] == ')')
// 	{
// 		*flag_mas = 2;
// 		start++;
// 	}
// 	else if (str[start] == '(' && str[ft_strlen(str) - 1] == ')')
// 		*flag_mas = 1;
// 	while (++start != ft_strlen(str) - 1)
// 	{
// 		if (ft_strchr("!&|;()`><", str[start]))
// 		{
// 			exe_error(str, 98, " export: ");
// 						printf("error\n");
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int	valid_variable(char *str, char **envp, int *flag_mas)
// {
// 	size_t	i;

// 	i = 1;
// 	if (ft_strchr("0123456789!@%^&*()-+={}[]|?/><~`;:.,\\", str[0]))
// 	{
// 		exe_error(str, 98, " export: ");
// 		return (1);
// 	}
// 	if (str[0] == '#')
// 	{
// 		ft_env(envp, 1);
// 		return (1);
// 	}
// 	while (str[i] != '\0' && str[i] != '=')
// 	{
// 		if (ft_strchr("!@#%^&*()-+{[]|};:.,~`<>?/\\", str[i]))
// 		{
// 			exe_error(str, 98, " export: ");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	if (check_inside(str, i, flag_mas))
// 		return (1);
// 	return (0);
// }

// int	ft_export(char **str, char ***envp)
// {
// 	int	i;
// 	int	flag_mas;

// 	i = -1;
// 	flag_mas = 0;
// 	if (str[0] == NULL)
// 		return (ft_env(*envp, 1));
// 	while (str[++i])
// 	{
// 		if (valid_variable(str[i], *envp, &flag_mas))
// 			continue ;
// 		if(flag_mas == 2)
// 			printf("mas empty\n");
// 		else if (flag_mas == 1)
// 			printf("mas\n");
// 		printf("%s\n", str[i]);
// 	}
// 	return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **my_envp = replace_envp(envp);
// 	char **str = ft_split("Linux", ' ');
// 	ft_export(str, &my_envp);
// }