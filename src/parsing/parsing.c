/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:45:00 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 01:20:58 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

void	sigint_pars_exe_1(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	sigquit_pars_exe_1(int sig)
{
	write(1, "Quit: 3\n", 9);
	(void)sig;
}

void	main_parsing(t_shell	*my_shell)
{
	my_shell->double_list = 0;
	if (!control_pars(my_shell, 0, 0, 0) && !check_paren(my_shell))
	{
		creat_delimiter(my_shell);
		if (!control_parsing(my_shell))
		{
			signal(SIGINT, sigint_pars_exe_1);
			signal(SIGQUIT, sigquit_pars_exe_1);
			make_exe(my_shell, 0, my_shell->count);
		}
	}
	free_struct(my_shell);
	if (my_shell->global_error)
		my_shell->error_status = my_shell->global_error;
	my_shell->global_error = 0;
	system("leaks minishell");
}
