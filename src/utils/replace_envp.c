#include "minishell.h"

int	lvl_check(char *envp, int *flag_z)
{
	int	lvl;
	int	i_atoi;

	i_atoi = ft_atoi(envp + 6);
	if (i_atoi < 0)
		return (0);
	lvl = i_atoi + 1;
	if (lvl == 1000)
	{
		lvl = 0;
		*flag_z = 1;
	}
	if (lvl > 1000)
	{
		printf("minishell: warning: shell level");
		printf("(%d) too high, resetting to 1\n", lvl);
		lvl = 1;
	}
	return (lvl);
}

char	*update_shlvl(char *envp, int lvl, int flag_z)
{
	char	*shlvl;
	char	*new_envp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	lvl = lvl_check(envp, &flag_z);
	shlvl = ft_itoa(lvl);
	if (shlvl == NULL)
		malloc_error();
	new_envp = malloc(sizeof(char) * (ft_strlen(shlvl) + 7));
	if (new_envp == NULL)
		malloc_error();
	while (envp[i] != '=')
		new_envp[j++] = envp[i++];
	i = 0;
	new_envp[j++] = '=';
	while (shlvl[i] != '\0' && flag_z != 1)
		new_envp[j++] = shlvl[i++];
	new_envp[j] = '\0';
	free(shlvl);
	return (new_envp);
}

char	**fill_envp(char **envp, char **new_envp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (envp[j])
	{
		if (!ft_strncmp("SHLVL=", envp[j], 6))
			new_envp[i++] = update_shlvl(envp[j], 0, 0);
		else
		{
			if (ft_strncmp("OLDPWD=", envp[j], 7))
			{
				new_envp[i] = ft_strdup(envp[j]);
				if (new_envp[i++] == NULL)
					malloc_error();
			}
		}
		j++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	**replace_envp(char **envp)
{
	char		**new_envp;
	size_t		count;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (new_envp == NULL)
		malloc_error();
	new_envp = fill_envp(envp, new_envp);
	return (new_envp);
}
