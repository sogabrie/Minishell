#include "minishell.h"

char	*variable_name(char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	ptr = malloc(sizeof(char) * i + 1);
	if (ptr == NULL)
		malloc_error();
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		ptr[i] = str[i];
		i++;
	}
	return (ptr);
}

char	**replace_variable(char **envp, char *name, char *str)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(name, envp[i], ft_strlen(name)))
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			break ;
		}
		i++;
	}
	return (envp);
}

int	ft_export(char **str, char ***envp)
{
	int	i;
	int	flag_mas;
	char *name;

	i = -1;
	flag_mas = 0;
	if (str[0] == NULL || str[0][0] == '#')
		return (ft_env(*envp, 1));
	while (str[++i])
	{
		if (valid_variable(str[i], *envp, &flag_mas))
			continue ;
		name = variable_name(str[i]);
		printf("%s\n", name);
		if (search_envp_in(*envp, name, ft_strlen(name)))
		{
			*envp = replace_variable(*envp, name, str[i]);
			for(int i = 0; (*envp)[i]; i++)
				printf("%s\n", (*envp)[i]);
		}
		else
			printf("chgtav\n");
	}
	return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	char **my_envp = replace_envp(envp);
// 	char **str = ft_split("OLDPWD=asfasf", ' ');
// 	ft_export(str, &my_envp);
// }