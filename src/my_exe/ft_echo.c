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

	start = 0;
	count = 1;
	(*i)++;
	while (args[count] && args[count] != end)
	{
		(*i)++;
		count++;
	}
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		malloc_error();
	while (start < count)
	{
		str[start] = args[start];
		start++;
	}
	str[start] = '\0';
	return (str);
}

char	*parse_scop(char *args, size_t *i)
{
	char	*str;
	size_t	count;
	size_t	start;

	count = 0;
	start = 0;
	if (args[0] && args[0] == '\'')
		return (scop_one(args, '\'', i));
	if (args[0] && args[0] == '\"')
		return (scop_one(args, '\"', i));
	while (args[(*i)] && args[(*i)] != '\'' && args[(*i)] != '\"')
	{
		(*i)++;
		count++;
	}
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		malloc_error();
	while (args[start] && args[start] != '\'' && args[start] != '\"')
	{
		str[start] = args[start];
		start++;
	}
	str[start] = '\0';
	return (str);
}

char	*parse_line(char *args, char **envp, int error, size_t i)
{
	char	*pars;
	char	*line;
	char	*final_str;
	char	**line_wild;

	final_str = NULL;
	while (args[i])
	{
		pars = parse_scop(args + i, &i);
		line = echo_line(pars, envp, NULL, error);
		if (line[0] != 0)
			final_str = ft_strjoin_exlusive(final_str, line);
		free(pars);
		free(line);
	}
	return (final_str);
}

int	ft_echo(char **args, char **envp, int error, int i)
{
	char	*line;
	size_t	flag_n;

	flag_n = 0;
	if (args == NULL || args[0] == NULL || args[0][0] == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[++i])
	{
		line = parse_line(args[i], envp, error, 0);
		if (line == NULL)
			continue ;
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
// 	char *str[3] = {"-nnnnnnn", "\"\'\'asfasfaf\'asfasf\'$\"HOME\"\'$USER\'\'ASDASF\'123124124124\"\"\'\"", NULL};
// 	ft_echo(str, envp, 0, -1);
// 	// system("leaks minishell");
// }
