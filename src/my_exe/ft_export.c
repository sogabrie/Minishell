#include "minishell.h"

char	*variable_name(char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		malloc_error();
	i = 0;
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*variable_add(char *str, char *ptr)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		if(str[i++] == '=')
		{
			if(!ft_strchr(ptr, '='))
				i -= 1;
			return (str + i);
		}
	}
	return (NULL);
}

char	**replace_variable(char **envp, char *name, char *str)
{
	size_t	i;
	char *tmp;

	i = 0;
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

char *ft_strdup_plus(char *str)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
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
			if(str[i] == '+')
				i++;
			while(str[i])
				ptr[j++] = str[i++]; 
			ptr[j] = '\0';
			return (ptr);
		}
		i++;
	}
	return (ft_strdup(str));
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
	new_envp[count] = ft_strdup_plus(str);
	if (new_envp[count++] == NULL)
		malloc_error();
	new_envp[count] = NULL;
	free(envp);
	return (new_envp);
}

int	ft_export(char **str, char ***envp)
{
	int		i;
	char	*name;

	i = -1;
	name = NULL;
	if (str == NULL || str[0] == NULL || str[0][0] == '#')
		return (ft_env(*envp, 1));
	while (str[++i])
	{
		if (valid_variable(str[i]))
			continue ;
		name = variable_name(str[i]);
		if (search_envp_in(*envp, name, ft_strlen(name)))
			*envp = replace_variable(*envp, name, str[i]);
		else
			*envp = replace_add_variable(*envp, str[i]);
		free(name);
		name = NULL;
	}
	return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **my_envp = replace_envp(envp);
// 	char **atr = ft_split("OMEGA++=", ' ');
// 	ft_export(atr, &my_envp);
// 	ft_export(NULL, &my_envp);
// 	for(int i = 0; my_envp[i]; i++)
// 		printf("%s\n", my_envp[i]);
// 	system("leaks minishell");
// }

// // ++++=========-+==+++++=+=+=++++===-+==
// // ++++=========-+==+++++=+=+=++++===-+==
