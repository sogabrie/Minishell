/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exe_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:42:49 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 16:14:02 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_my_exe(t_shell *my_shell, int i)
{
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "echo"))
		return (ft_echo(my_shell->control[i]->exe->options, \
		my_shell->my_envp, my_shell->error_status));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "cd"))
	{
		if (my_shell->control[i]->exe->options)
			return (ft_cd(my_shell->control[i]->exe->options[0] \
			, &my_shell->my_envp, NULL, NULL));
		return (ft_cd(NULL, &my_shell->my_envp, NULL, NULL));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "export"))
		return (ft_export(my_shell->control[i]->exe->options, \
		&my_shell->my_envp, -1, NULL));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "unset"))
		return (ft_unset(my_shell->control[i]->exe->options, \
		&my_shell->my_envp));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "env"))
		return (ft_env(my_shell->my_envp, 0));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "exit"))
		ft_exit(my_shell->control[i]->exe->options, 0);
	return (0);
}

void	do_exe_2(t_shell *my_shell, int i)
{
	char	*new_name;

	my_shell->control[i]->exe->cpy_fd_input = dup(my_shell->fd_input);
	dup2(my_shell->control[i]->exe->fd_input, my_shell->fd_input);
	my_shell->control[i]->exe->cpy_fd_output = dup(my_shell->fd_output);
	dup2(my_shell->control[i]->exe->fd_output, my_shell->fd_output);
	new_name = parse_line(my_shell->control[i]->exe->full_name, \
	my_shell->my_envp, my_shell->error_status, 0);
	if (new_name)
	{
		free(my_shell->control[i]->exe->full_name);
		my_shell->control[i]->exe->full_name = new_name;
	}
}

void	do_exe_3_1(t_shell *my_shell, int i)
{
	char	*new_name;
	int		j;

	j = 0;
	while (my_shell->control[i]->exe->options && \
	my_shell->control[i]->exe->options[j])
	{
		new_name = parse_line(my_shell->control[i]->exe->options[j], \
		my_shell->my_envp, my_shell->error_status, 0);
		if (new_name)
		{
			free(my_shell->control[i]->exe->options[j]);
			my_shell->control[i]->exe->options[j] = new_name;
		}
		++j;
	}
}

void	do_exe_3_2(t_shell *my_shell, int i, int *j, char	***cp_dubl)
{
	char	**new_dubl;
	int		j2;
	int		j3;
	int		mas_count;

	j2 = -1;
	j3 = 0;
	mas_count = size_list(my_shell->control[i]->exe->options) \
	+ size_list((*cp_dubl));
	new_dubl = malloc(mas_count * sizeof(char *));
	if (!new_dubl)
		malloc_error();
	while (++j2 < (*j))
		new_dubl[j2] = my_shell->control[i]->exe->options[j2];
	j3 = 0;
	while ((*cp_dubl)[j3])
		new_dubl[j2++] = (*cp_dubl)[j3++];
	free(my_shell->control[i]->exe->options[(*j)]);
	j3 = (*j);
	(*j) = j2 - 1;
	while (j2 < mas_count - 1)
		new_dubl[j2++] = my_shell->control[i]->exe->options[++j3];
	new_dubl[j2] = 0;
	free(my_shell->control[i]->exe->options);
	my_shell->control[i]->exe->options = new_dubl;
}

void	do_exe_3(t_shell *my_shell, int i)
{
	char	**cp_dubl;
	int		j;

	do_exe_3_1(my_shell, i);
	j = 0;
	while (my_shell->control[i]->exe->options && \
	my_shell->control[i]->exe->options[j])
	{
		cp_dubl = wildcards(ft_strdup(my_shell->control[i]->exe->options[j]));
		if (cp_dubl)
		{
			do_exe_3_2(my_shell, i, &j, &cp_dubl);
			free(cp_dubl);
		}
		++j;
	}
}
