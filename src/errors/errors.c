/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:05:02 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:05:03 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	write(2, "minishell: Out of memory\n", 25);
	exit(1);
}

char	*error_here_doc(char *name)
{
	char	*error;

	error = ft_strdup("error");
	if (error == NULL)
		malloc_error();
	free(name);
	write(2, "-minishell: syntax error: unexpected end of file\n", 49);
	return (error);
}

void	exe_error(char *dir, int number, char *my_exe)
{
	char	*error;

	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(my_exe, 2);
	if (number == 276 && (!ft_strcmp(" exit: ", my_exe)))
	{
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return ;
	}
	if (number == 98 && (!ft_strcmp(" export: ", my_exe)
			|| !ft_strcmp(" unset: ", my_exe)))
	{
		write(2, "`", 1);
		ft_putstr_fd(dir, 2);
		write(2, "'", 1);
		ft_putendl_fd(": not a valid identifier", 2);
		return ;
	}
	ft_putstr_fd(dir, 2);
	error = strerror(number);
	write(2, ": ", 2);
	ft_putendl_fd(error, 2);
}
