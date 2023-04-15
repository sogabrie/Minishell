#include "minishell.h"

int	first_char(char *str)
{
	if (ft_strchr("0123456789!@%^&*()-+={}[]|?/><~`;:.,\\", str[0]))
	{
		exe_error(str, 98, " export: ");
		return (1);
	}
	return (0);
}

int	check_inside(char *str, size_t start)
{
	while (str[start] != '\0')
	{
		if (ft_strchr("!&|;()`><", str[start]))
		{
			exe_error(str, 98, " export: ");
			return (1);
		}
		start++;
	}
	return (0);
}

int	valid_variable(char *str)
{
	size_t	start;

	start = 1;
	if (first_char(str))
		return (1);
	while (str[start] != '\0' && str[start] != '=')
	{
		if (ft_strchr("!@#%^&*()-+{[]()|};:.,~`<>?/\\", str[start]))
		{
			exe_error(str, 98, " export: ");
			return (1);
		}
		start++;
	}
	if (str[start] == '\0')
		return (0);
	if (check_inside(str, start))
		return (1);
	return (0);
}
