/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:15 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 22:30:54 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	overflow_or_not(char *str)
{
	int					minus;
	int					i;
	unsigned long long	oper;

	oper = 0;
	i = 0;
	minus = 1;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		oper = oper * 10 + str[i] - '0';
		i++;
	}
	if (minus == -1 && oper > (unsigned long long)(9223372036854775807) + 1)
		return (1);
	if (minus == 1 && oper > LONG_MAX)
		return (1);
	return (0);
}

int	char_args(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **args, size_t	count)
{
	unsigned char	exit_code;

	if (args == NULL || args[0] == NULL)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (overflow_or_not(args[0]) || char_args(args[0]))
	{
		ft_putendl_fd("exit", 1);
		exe_error(args[0], 276, " exit: ");
		exit(255);
	}
	while (args[count])
		count++;
	if (count != 1)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_code = (unsigned char)(ft_atoi(args[0]));
	ft_putendl_fd("exit", 1);
	exit(exit_code);
}
