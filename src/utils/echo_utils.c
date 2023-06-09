/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:02:57 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:02:58 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	do_scop(char *str, size_t *i, char **envp)
{
	size_t	j;
	size_t	count;
	char	*ptr;

	j = 0;
	count = 0;
	if (str[j] == '?')
	{
		*i += 2;
		return (2);
	}
	while (!ft_strchr("@#%^*$}]{+=? \n\t.,-[|/>\'<;:~\\", str[j]))
		j++;
	*i += j;
	ptr = ft_substr(str, 0, j);
	if (ptr == NULL)
		malloc_error();
	count = ft_strlen(search_envp_in(envp, ptr, ft_strlen(ptr)));
	free(ptr);
	return (count);
}

int	ultra_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("@#%^$*}]{+=? \n\t.,-[|/>\'<;:~\\", str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*creat_new_line(char *str, char **envp, size_t i, size_t count)
{
	char	*new_line;

	if (str == NULL)
		malloc_error();
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (ultra_char(str + i))
				count += do_scop(str + i + 1, &i, envp);
			else
			{
				count += ft_strlen(search_envp_in(envp, str + i + 1, \
							ft_strlen(str + i + 1)));
				i += ft_strlen(str + i + 1);
			}
		}
		count++;
	}
	new_line = malloc(sizeof(char) * (count + 1));
	if (new_line == NULL)
		malloc_error();
	return (new_line);
}

int	check_flag(char *str, size_t *flag)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
		{
			*flag = 0;
			return (0);
		}
		i++;
	}
	*flag = 1;
	return (1);
}

char	*variable(char *str, size_t *i, char **envp, int error)
{
	size_t	j;
	char	*variable_in;
	char	*error_s;

	j = 0;
	variable_in = NULL;
	if (str[j] == '?')
	{
		error_s = ft_itoa(error);
		if (error_s == NULL)
			malloc_error();
		*i += 2;
		return (error_s);
	}
	while (str[j] && !ft_strchr("@#%^$*}]{+=? \n\t.,-[|/>\'<;:~\\", str[j]))
		j++;
	*i += j + 1;
	variable_in = var_in(variable_in, envp, j, str);
	return (variable_in);
}
