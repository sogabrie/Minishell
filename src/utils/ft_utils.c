#include "minishell.h"

enum e_flags_access {
	ROK = 4,
	WOK = 2,
	XOK = 1,
};

int	check_access(char *directory, int check_number)
{
	if (access(directory, F_OK) == 0)
	{
		if (check_number == ROK)
		{
			if (access(directory, R_OK) == 0)
				return (0);
			return (-1);
		}
		if (check_number == WOK)
		{
			if (access(directory, W_OK) == 0)
				return (0);
			return (-1);
		}
		if (check_number == XOK)
		{
			if (access(directory, X_OK) == 0)
				return (0);
			return (-1);
		}
		return (-1);
	}
	return (0);
}

char	*search_envp_in(char **envp, char *obj, int count)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(obj, envp[i], count)
			&& (envp[i][count] == '=' || envp[i][count] == '\0'))
		{
			if (envp[i][count] == '\0')
				return (envp[i] + count);
			else
				return (envp[i] + count + 1);
		}
		i++;
	}
	return (NULL);
}
