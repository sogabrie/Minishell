#include "minishell.h"

int	first_char(char *str, char **envp)
{
	if (ft_strchr("0123456789!@%^&*()-+={}[]|?/><~`;:.,\\", str[0]))
	{
		exe_error(str, 98, " export: ");
		return (1);
	}
	return (0);
}

int	determine(char *str, size_t start)
{
	start++;
	if (str[start] == '(' && str[start + 1] == ')'
		&& str[start + 2] == '\0')
		return (2);
	if (str[start] == '=' && str[start + 1] == '('
		&& str[ft_strlen(str) - 1] == ')')
		return (2);
	if (str[start] == '(' && str[ft_strlen(str) - 1] == ')')
		return (1);
	return (0);
}

int	check_mas(char *str, size_t start)
{
	while (start < ft_strlen(str) - 1)
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

int	check_inside(char *str, size_t start, int *flag_mas)
{
	*flag_mas = determine(str, start);
	if ((ft_strlen(str) - start) == 3)
		return (0);
	if (*flag_mas != 0)
	{
		if (*flag_mas == 2)
			start++;
		start += 2;
		if (check_mas(str, start))
			return (1);
	}
	else
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
	}
	return (0);
}

int	valid_variable(char *str, char **envp, int *flag_mas)
{
	size_t	start;

	start = 1;
	if (first_char(str, envp))
		return (1);
	while (str[start] != '\0' && str[start] != '=')
	{
		if (ft_strchr("!@#%^&*()-+{[]|};:.,~`<>?/\\", str[start]))
		{
			exe_error(str, 98, " export: ");
			return (1);
		}
		start++;
	}
	if (str[start] == '\0')
		return (0);
	if (check_inside(str, start, flag_mas))
		return (1);
	return (0);
}
