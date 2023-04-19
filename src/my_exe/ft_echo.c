#include "minishell.h"

size_t	do_scop(char *str, size_t *i, char **envp)
{
	size_t	j;
	size_t	count;
	char	*ptr;

	j = 0;
	count = 0;
	while (str[j] != '\'')
		j++;
	*i += j;
	ptr = ft_substr(str, 0, j);
	count = ft_strlen(search_envp_in(envp, ptr, ft_strlen(ptr)));
	free(ptr);
	return (count);
}

char	*creat_new_line(char *str, char **envp)
{
	size_t	i;
	size_t	count;
	char 	*new_line;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if(ft_strchr(str + i, '\''))
				count += do_scop(str + i + 1, &i, envp);
			else
			{
				count += ft_strlen(search_envp_in(envp, str + i + 1, ft_strlen(str + i + 1)));
				i += ft_strlen(str + i + 1);
			}
		}
		count++;
		i++;
	}
	new_line = malloc(sizeof(char) * count);
    printf("count = %zu\n", count);
	if (new_line == NULL)
		malloc_error();
	return (new_line);
}

char *variable(char *str, size_t *i, char **envp)
{
    size_t  j;
    char *ptr;
    char *variable_in;

    j = 0;
    while(str[j] && str[j] != '\'')
        j++;
    ptr = ft_substr(str, 0, j);
    printf("%s\n", ptr);
    *i += j + 1;
    variable_in = search_envp_in(envp, ptr, ft_strlen(ptr));
    printf("%s\n", variable_in);
    free(ptr);
    return (variable_in);
}

char	*echo_line(char *line, char **envp, char *str, char *new_line)
{
	size_t	i;
	size_t	j;
    size_t  k;
    char    *ptr;

	i = 0;
	j = 0;
    k = 0;
	if (line[i] == '\'')
		return (ft_strtrim(line, "\'"));
	str = ft_strtrim(line, "\"");
	new_line = creat_new_line(str, envp);
	while (str[i])
	{
		if (str[i] == '$')
        {
            ptr = variable(str + i + 1, &i, envp);
            while(ptr && ptr[k])
                new_line[j++] = ptr[k++];
            printf("%c\n", str[i]);
        }
		else
			new_line[j++] = str[i++];
        k = 0;
	}
    new_line[j] = '\0';
    free(str);
	return (new_line);
}

int	ft_echo(char **args, char **envp)
{
	char	*line;
	size_t	i;

	i = 0;
	if (args == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[i])
	{
		line = echo_line(args[i], envp, NULL, NULL);
		printf("line = %s\n", line);
		free(line);
        i++;
	}
	return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **my_envp = replace_envp(envp);
// 	char **str = ft_split("\"asfasf$HOMEa\"", ' ');
// 	int error = ft_echo(str, my_envp);
// 	// printf("error = %d\n", error);

// }