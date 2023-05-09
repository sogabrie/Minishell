/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:03:01 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:03:02 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_char(char *str)
{
	if (str[0] == 0)
	{
		exe_error("", 98, " export: ");
		return (1);
	}
	if (ft_strchr("0123456789!@%^ \'\"&*()-+=#{}[]|?/><~`;:.,\\", str[0]))
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
		if (ft_strchr("!@#%^&*()- {[]()|};:.,~`<>?/\\", str[start])
			|| (str[start] == '+' && str[start + 1] != '='))
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
	while (str[i])
	{
		if (str[i++] == '=')
		{
			if (!ft_strchr(ptr, '='))
				i -= 1;
			return (str + i);
		}
	}
	return (NULL);
}
