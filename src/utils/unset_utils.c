#include "minishell.h"

int	valid_unset(char *arg, int *error_code, char **envp, size_t i)
{
	if (ft_strchr("!@%^&*()-+=0123456 789\'\"{}$[]:;|~<>,.?/", arg[0])
		|| (arg[0] == '$' && arg[1] == '\0'))
	{
		exe_error(arg, 98, " unset: ");
		return (1);
	}
	while (arg[++i])
	{
		if (ft_strchr("!@#%^&*v()-+=[]{}\\|\'\";:,.$/~`><", arg[i]))
		{
			exe_error(arg, 98, " unset: ");
			return (1);
		}
	}
	return (0);
}

int	check_exists(char **envp, char *str)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(str, envp[i], ft_strlen(str)))
			return (0);
	return (1);
}
