#include "minishell.h"

char	*update_shlvl(char *envp)
{
	char	*shlvl;
	char	*new_envp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	shlvl = ft_itoa(ft_atoi(envp + 6) + 1);
	if (shlvl == NULL)
		malloc_error();
	new_envp = malloc(sizeof(char) * (ft_strlen(shlvl) + 7));
	if (new_envp == NULL)
		malloc_error();
	while (envp[i] != '=')
		new_envp[j++] = envp[i++];
	i = 0;
	new_envp[j++] = '=';
	while (shlvl[i] != '\0')
		new_envp[j++] = shlvl[i++];
	new_envp[j] = '\0';
	free(shlvl);
	return (new_envp);
}

char	**replace_envp(char **envp)
{
	char	**new_envp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (new_envp == NULL)
		malloc_error();
	while (envp[i])
	{
		if (!ft_strncmp("SHLVL", envp[i], 5))
			new_envp[i] = update_shlvl(envp[i]);
		else
		{
			new_envp[i] = ft_strdup(envp[i]);
			if (new_envp[i] == NULL)
				malloc_error();
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
