// #include "minishell.h"

// size_t	do_scop(char *str, size_t *i, char **envp)
// {
// 	size_t	j;
// 	size_t	count;
// 	char	*ptr;

// 	j = 0;
// 	count = 0;
// 	while (str[j] != '\'')
// 		j++;
// 	*i += j;
// 	ptr = ft_substr(str, 0, j);
// 	count = ft_strlen(search_envp_in(envp, ptr, ft_strlen(ptr)));
// 	free(ptr);
// 	return (count);
// }

// int	valid_scop(char *str, size_t *i, char **envp)
// {
// 	size_t	j;
// 	char 	*ptr;

// 	j = 0;
// 	if(!ft_strchr(str, '\'') && !search_envp_in(envp, str, ft_strlen(str)));
// 		return (0);
// 	if(!ft_strchr(str, '\'') && search_envp_in(envp, str, ft_strlen(str)));
// 		return (1);
// 	while (str[j] && str[j] != '\'')
// 		j++;
// 	*i += j;
// 	ptr = ft_substr(str, 0, j);
// 	if (!search_envp_in(envp, ptr, ft_strlen(ptr)))
// 	{
// 		free(ptr);
// 		return (0);
// 	}
// 	free(ptr);
// 	return (1);
// }

// char	*creat_new_line(char *str, char **envp)
// {
// 	size_t	i;
// 	size_t	count;
// 	char 	*new_line;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			if(ft_strchr(str + i, '\''))
// 				count += do_scop(str + i + 1, &i, envp);
// 			else
// 			{
// 				count += ft_strlen(search_envp_in(envp, str + i + 1, ft_strlen(str + i + 1)));
// 				i += ft_strlen(str + i + 1);
// 			}
// 		}
// 		count++;
// 		i++;
// 	}
// 	new_line = malloc(sizeof(char) * count);
// 	if (new_line == NULL)
// 		malloc_error();
// 	return (new_line);
// }

// char	*echo_line(char *line, char **envp)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*str;
// 	char 	*new_line;

// 	i = 0;
// 	j = 0;
// 	if (line[i] == '\'')
// 		return (ft_strtrim(line, "\'"));
// 	str = ft_strtrim(line, "\"");
// 	new_line = creat_new_line(str, envp);
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && valid_scop(str + i + 1, &i, envp))
			
// 		else
// 			new_line[j++] = str[i++];
// 	}
// 	return (NULL);
// }

// int	ft_echo(char **args, char **envp)
// {
// 	char	*line;
// 	size_t	i;

// 	i = 0;
// 	if (args == NULL)
// 	{
// 		write(1, "\n", 1);
// 		return (0);
// 	}
// 	while (args[i])
// 	{
// 		line = echo_line(args[i], envp);
// 		printf("%s\n", line);
// 		i++;
// 		free(line);
// 	}
// 	return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **my_envp = replace_envp(envp);
// 	char **str = ft_split("\"$HOME\"", ' ');
// 	int error = ft_echo(str, my_envp);
// 	printf("error = %d\n", error);

// }