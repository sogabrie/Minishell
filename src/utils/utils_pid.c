/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:47:00 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 00:02:43 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

void	add_pid(t_mas_pid	*my_pid)
{
	pid_t	*pid;
	int		*int_pid;
	int		i;

	i = -1;
	pid = malloc(sizeof(pid_t) * my_pid->count + 1);
	int_pid = malloc(sizeof(int) * my_pid->count + 1);
	if (!pid || !int_pid)
		malloc_error();
	while (++i < my_pid->count)
	{
		pid[i] = my_pid->pid[i];
		int_pid[i] = my_pid->my_pid[i];
	}
	free(my_pid->pid);
	free(my_pid->my_pid);
	my_pid->pid = pid;
	my_pid->my_pid = int_pid;
	++my_pid->count;
	my_pid->my_pid[my_pid->count - 1] = -1;
}
