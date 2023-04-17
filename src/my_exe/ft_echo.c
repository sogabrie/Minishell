// #include "minishell.h"

// char	*echo_line(char *line, char **envp)
// {
//     size_t  count;
//     size_t  i;
//     char    *new_line;

//     count = 0;
//     i = 0;
//     if (line[i] == '\'' || line[i] == '\"')
//         i++;
//     while(i < ft_strlen(line) - 1)
//     {
//         if(line[i] == '$')
//         {
//             i++;
//             printf("%zu\n", ft_strlen(search_envp_in(envp, line + i, ft_strlen(line + i))));
//             count += ft_strlen(search_envp_in(envp, line + i, ft_strlen(line + i)));
//             break;
//         }
//         count++;
//         i++;
//     }
//     printf("%zu\n", count);
//     return (NULL);
// }

// int	ft_echo(char **args, char **envp)
// {
// 	char	*line;
// 	int		flag_n;
// 	size_t	i;

// 	i = 0;
// 	flag_n = 0;
// 	while (args[i])
// 	{
//         line = echo_line(args[i], envp);
//         i++;
// 	}
//     return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
//     char **my_envp = replace_envp(envp);
// 	char **str = ft_split("asf$HOMEas", ' ');
// 	int error = ft_echo(str, envp);
// 	printf("error = %d\n", error);

// }