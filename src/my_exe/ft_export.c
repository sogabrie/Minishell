#include "minishell.h"

char	*ft_strdup_plus(char *str, size_t i, size_t j)
{
	char	*ptr;

	while (str[i])
	{
		if (str[i] == '+')
		{
			ptr = malloc(sizeof(char) * (ft_strlen(str)));
			if (ptr == NULL)
				malloc_error();
			i = 0;
			while (str[i] && str[i] != '+' && str[i] != '=')
				ptr[j++] = str[i++];
			if (str[i] == '+')
				i++;
			while (str[i])
				ptr[j++] = str[i++];
			ptr[j] = '\0';
			return (ptr);
		}
		i++;
	}
	return (ft_strdup(str));
}

char	**replace_variable(char **envp, char *name, char *str, size_t i)
{
	char	*tmp;

	while (envp[i])
	{
		if (!ft_strncmp(name, envp[i], ft_strlen(name)))
		{
			if (ft_strchr(str, '+'))
			{
				tmp = envp[i];
				envp[i] = ft_strjoin(envp[i], variable_add(str, envp[i]));
				free(tmp);
			}
			else
			{
				free(envp[i]);
				envp[i] = ft_strdup(str);
			}
			if (envp[i] == NULL)
				malloc_error();
			break ;
		}
		i++;
	}
	return (envp);
}

char	**replace_add_variable(char **envp, char *str)
{
	char	**new_envp;
	size_t	count;

	count = 0;
	new_envp = NULL;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (new_envp == NULL)
		malloc_error();
	count = 0;
	while (envp[count])
	{
		new_envp[count] = envp[count];
		count++;
	}
	new_envp[count] = ft_strdup_plus(str, 0, 0);
	if (new_envp[count++] == NULL)
		malloc_error();
	new_envp[count] = NULL;
	free(envp);
	return (new_envp);
}

int	ft_export(char **str, char ***envp, int i)
{
	char	*name;
	int		error_code;

	error_code = 1;
	name = NULL;
	if (str == NULL || str[0] == NULL || str[0][0] == '#')
		return (ft_env(*envp, 1));
	while (str[++i])
	{
		if (valid_variable(str[i]))
		{
			error_code = 1;
			continue ;
		}
		name = variable_name(str[i]);
		if (search_envp_in(*envp, name, ft_strlen(name)))
			*envp = replace_variable(*envp, name, str[i], 0);
		else
			*envp = replace_add_variable(*envp, str[i]);
		free(name);
		name = NULL;
		error_code = 0;
	}
	return (error_code);
}
