#include "minishell.h"

char	*variable_name(char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		malloc_error();
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
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
	new_envp[count] = ft_strdup(str);
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
// 	// char **str = ft_split("1_asfd LINUXX= OMEGA=123 Liux_123=123 peeep=pppep", ' ');
// 	// char **ptr = ft_split("OMEGA==Linux=123==", ' ');
// 	// ptr = ft_split("OLDPWD", ' ');
// 	// ptr = ft_split("OLDPWD", ' ');
// 	// ptr = ft_split("OLD_PWD=\"\"", ' ');
// 	// ptr = ft_split("TEST+=100", ' ');
// 	// ft_export(str, &my_envp);
// 	// ft_export(ptr, &my_envp);
// 	// system("leaks minishell");
// 	// for(int i = 0; my_envp[i]; i++)
// 	// 	printf("%s\n", my_envp[i]);
// 	// ft_export(NULL, &my_envp);
// 	// ft_cd("bark bark", &my_envp, NULL, NULL);
// 	for(int i = 0; my_envp[i]; i++)
// 		printf("%s\n", my_envp[i]);
// 	// system("leaks minishell");
// }
