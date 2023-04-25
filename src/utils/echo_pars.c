#include "minishell.h"

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
	count++;
	(*i)++;
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		malloc_error();
	while (args[start] && start < count)
	{
		str[start] = args[start];
		start++;
	}
	str[start] = '\0';
	return (str);
}

char	*parse_scop(char *args, size_t *i, size_t count, size_t start)
{
	char	*str;

	if (args[0] && args[0] == '\'')
		return (scop_one(args, '\'', i));
	if (args[0] && args[0] == '\"')
		return (scop_one(args, '\"', i));
	while (args[count] && args[count] != '\'' && args[count] != '\"')
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
	if (count == 0)
		(*i) += start;
	str[start] = '\0';
	return (str);
}

char	*parse_line(char *args, char **envp, int error, size_t i)
{
	char	*pars;
	char	*line;
	char	*final_str;

	final_str = NULL;
	while (args[i])
	{
		pars = parse_scop(args + i, &i, 0, 0);
		line = echo_line(pars, envp, NULL, error);
		if (line[0] != 0)
			final_str = ft_strjoin_exlusive(final_str, line);
		free(pars);
		free(line);
	}
	return (final_str);
}

char	*parse_wild(char *line)
{
	char	**wild_str;
	size_t	j;
	char	*new_line;

	j = 0;
	new_line = NULL;
	if (line == NULL)
		return (NULL);
	wild_str = wildcards(ft_strdup(line));
	if (wild_str == NULL)
		return (line);
	while (wild_str[j])
	{
		new_line = ft_strjoin_exlusive(new_line, wild_str[j++]);
		if (wild_str[j])
			new_line = ft_strjoin_exlusive(new_line, " ");
	}
	two_dimensional_mas(&wild_str);
	free(line);
	return (new_line);
}

char	*var_in(char *variable_in, char **envp, size_t j, char *str)
{
	char	*ptr;

	ptr = NULL;
	ptr = ft_substr(str, 0, j);
	if (ptr == NULL)
		malloc_error();
	variable_in = search_envp_in(envp, ptr, ft_strlen(ptr));
	if (variable_in == NULL)
	{
		free(ptr);
		return (NULL);
	}
	variable_in = ft_strdup(variable_in);
	if (variable_in == NULL)
		malloc_error();
	free(ptr);
	return (variable_in);
}
