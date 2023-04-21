#include "minishell.h"

typedef struct s_oper {
	size_t	i;
	size_t	k;
	size_t	j;
	char	*ptr;
	char	*str;
}	t_oper;

char	*new_line_creat(char *line)
{
	char	*new_line;

	new_line = ft_strtrim(line, "\'");
	if (new_line == NULL)
		malloc_error();
	return (new_line);
}


char	*adds(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(ptr) + 1);
	if (str == NULL)
		return (NULL);
	while (ptr[i] != '\0')
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_exlusive(char *str, char *ptr)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (str == NULL && ft_strlen(ptr) > 0)
		return (adds(ptr));
	new_str = malloc(sizeof(char) * (ft_strlen(ptr) + ft_strlen(str) + 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	i = 0;
	while (ptr[i] != '\0')
		new_str[j++] = ptr[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*echo_line(char *line, char **envp, char *new_line, int error)
{
	t_oper	jik;

	jik.i = 0;
	jik.j = 0;
	jik.k = 0;
	if (line[jik.i] == '\'')
		return (new_line_creat(line));
	jik.str = ft_strtrim(line, "\"");
	new_line = creat_new_line((jik.str), envp, -1, 0);
	while ((jik.str)[jik.i])
	{
		if ((jik.str)[jik.i] == '$' && (jik.str)[jik.i + 1] != '\0')
		{
			jik.ptr = variable((jik.str) + jik.i + 1, &(jik.i), envp, error);
			while ((jik.ptr) && (jik.ptr)[jik.k])
				new_line[jik.j++] = (jik.ptr)[jik.k++];
		}
		else
			new_line[jik.j++] = (jik.str)[jik.i++];
		jik.k = 0;
	}
	new_line[jik.j] = '\0';
	free(jik.str);
	return (new_line);
}


char	*scop_one(char *args, char end, size_t *i)
{
	char	*str;
	size_t	count;
	size_t	start;
	size_t	start_str;

	start = (*i);
	count = 0;
	start_str = 0;
	++(*i);
	while(args[*i] && args[*i] != end)
	{
		(*i)++;
		count++;
	}
	++(*i);
	count += 2;
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		malloc_error();
	while(start_str < count)
		str[start_str++] = args[start++];
	str[start_str] = '\0';
	// printf("ssssss = %s\n", str);
	return (str);
}

char 	*parse_scop(char *args, size_t *i)
{
	char	*str;
	size_t	count;
	size_t	start;
	size_t	start_str;

	count = 0;
	start_str = 0;
	start = (*i);
	if (args[*i] && args[*i] == '\'')
		return (scop_one(args, '\'', i));
	if (args[*i] && args[*i] == '\"')
		return (scop_one(args, '\"', i));
	while(args[(*i)] && args[(*i)] != '\'' && args[(*i)] != '\"')
	{
		(*i)++;
		count++;
	}
	// printf("iiii = %d\n", count);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		malloc_error();
	// printf("yyyyyy = %d\n", start);
	while(args[start] && args[start] != '\'' && args[start] != '\"')
		str[start_str++] = args[start++];
	str[start_str] = '\0';
	// printf("uuuuuu = %s\n", str);
	return (str);
}

char	*parse_line(char *args, char **envp, int error)
{
	char	*pars;
	char	*line;
	char	*final_str;
	size_t	i;

	final_str = NULL;
	i = 0;
	while(args[i])
	{
		// printf("i = %zu\n", i);
		// printf("ttttt = %s\n", args + i);
		pars = parse_scop(args, &i);
		// ft_putendl_fd(pars, 1);
		// ft_putnbr_fd(i, 1);
		// write(1, "\n", 1);
		line = echo_line(pars, envp, NULL, error);
		// ft_putendl_fd(line, 1);
		final_str = ft_strjoin_exlusive(final_str, line);
		// ft_putendl_fd(final_str, 1);
		free(pars);
		free(line);
		// ++i;
	}
	// ft_putendl_fd(final_str, 1);
	return (final_str);
}

int	ft_echo(char **args, char **envp, int error, int i)
{
	char	*line;
	char 	*pars;
	size_t	flag_n;
	char	*final_str;

	flag_n = 0;
	final_str = NULL;
	if (args == NULL || args[0] == NULL || args[0][0] == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[++i])
	{
		line = parse_line(args[i], envp, error);
		if (i == 0 && line[0] == '-' && check_flag(line + 1, &flag_n))
		{
			free(line);
			continue ;
		}
		printf("%s", line);
		if (args[i + 1] != NULL)
			printf(" ");
		free(line);
	}
	if (flag_n == 0)
		printf("\n");
	return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	char *str[2] = {"\"asdasd'asfa$HOME'adssad\"", NULL};
// 	ft_echo(str, envp, 0, -1);
	
// }