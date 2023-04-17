#include "minishell.h"

// char	*echo_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line && line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			remov_quote(line, i, '\'');
// 			return (line);
// 		}
// 		if (line[i] == '\"')
// 		{
// 			remov_quote(line, i, '\"');
// 			return (line);
// 		}
// 		++i;
// 	}
// 	return (line);
// }

// int	init_n(char *str)
// {
// 	size_t	i;
	
// 	i = 0;
// 	if (str[i] == '\'' || str[i] == '\"')
// 		i++;
// 	if (str[i++] != '-')
// 		return (0);
// 	while (str[i] != '\0')
// 	{
// 		if ((str[i] == '\'' && str[i + 1] != '\0')
// 			|| (str[i] == '\"' && str[i + 1] != '\0')
// 			||  str[i] != 'n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	ft_echo(char **args)
// {
// 	char	*line;
// 	int		flag_n;
// 	size_t	i;

// 	i = 0;
// 	flag_n = 0;
// 	flag_n = init_n(args[0]);
// 	printf("%d\n", flag_n);
// 	// while (args[i])
// 	// {
// 	// 	if(args[i][0] == '\'')
// 	// 	{
// 	// 		ft_putstr_fd()
// 	// 	}
// 	// 	i++;
// 	// }
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **str = ft_split("oper_echo", ' ');
// 	int error = ft_echo(str);
// 	printf("error = %d\n", error);

// }