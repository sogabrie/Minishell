#include "minishell.h"

size_t	do_scop(char *str, size_t *i, char **envp)
{
	size_t	j;
	size_t	count;
	char	*ptr;

	j = 0;
	count = 0;
	if (str[j] == '?')
	{
		*i += 2;
		return (2);
	}
	while (str[j] != '\'' && str[j] != '/' && str[j] != '=')
		j++;
	*i += j;
	ptr = ft_substr(str, 0, j);
	if (ptr == NULL)
		malloc_error();
	count = ft_strlen(search_envp_in(envp, ptr, ft_strlen(ptr)));
	free(ptr);
	return (count);
}

char	*creat_new_line(char *str, char **envp, size_t i, size_t count)
{
	char	*new_line;

	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (ft_strchr(str + i, '\'') || ft_strchr(str + i, '/') \
				|| ft_strchr(str + i, '='))
				count += do_scop(str + i + 1, &i, envp);
			else
			{
				count += ft_strlen(search_envp_in(envp, str + i + 1, \
							ft_strlen(str + i + 1)));
				i += ft_strlen(str + i + 1);
			}
		}
		count++;
	}
	new_line = malloc(sizeof(char) * count);
	if (new_line == NULL)
		malloc_error();
	return (new_line);
}

int	check_flag(char *str, size_t *flag)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
		{
			*flag = 0;
			return (0);
		}
		i++;
	}
	*flag = 1;
	return (1);
}

char	*variable(char *str, size_t *i, char **envp, int error)
{
	size_t	j;
	char	*ptr;
	char	*variable_in;
	char	*error_s;

	j = 0;
	if (str[j] == '?')
	{
		error_s = ft_itoa(error);
		if (error_s == NULL)
			malloc_error();
		*i += 2;
		return (error_s);
	}
	while (str[j] && str[j] != '\'' && str[j] != '/' && str[j] != '=')
		j++;
	ptr = ft_substr(str, 0, j);
	if (ptr == NULL)
		malloc_error();
	*i += j + 1;
	variable_in = search_envp_in(envp, ptr, ft_strlen(ptr));
	free(ptr);
	return (variable_in);
}
