/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env_and_access.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:44:24 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/27 15:31:10 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "minishell.h"

char	**get_path_2(int *i, char **avp, char **path, char ***new_path)
{
	(*path) = ft_strdup(avp[(*i)]);
	if (!(*path))
		malloc_error();
	(*path)[3] = '.';
	(*path)[4] = ':';
	(*new_path) = ft_split((*path) + 3, ':');
	if (!(*new_path))
		malloc_error();
	free((*path));
	return ((*new_path));
}

char	**get_path(char **avp)
{
	char	**new_path;
	char	*path;
	int		i;

	i = 0;
	while (avp[i])
	{
		if (!ft_strncmp("PATH=", avp[i], 5))
			break ;
		else
			++i;
	}
	if (!avp[i])
	{
		new_path = malloc(sizeof(char *) * 2);
		if (!new_path)
			malloc_error();
		new_path[0] = ft_strdup(".");
		if (!new_path[0])
			malloc_error();
		new_path[1] = 0;
		return (new_path);
	}
	return (get_path_2(&i, avp, &path, &new_path));
}

char	*check_procces_2(t_shell *my_shell, int i, int si, char **mas)
{
	int	size_p;
	int	size;

	size_p = ft_strlen(my_shell->control[si]->exe->full_name);
	size = ft_strlen(my_shell->full_path[i]);
	(*mas) = ft_calloc(size + size_p + 2, sizeof(char));
	if (!(*mas))
		malloc_error();
	ft_strlcat((*mas), my_shell->full_path[i], size + 1);
	ft_strlcat((*mas), "/", size + 2);
	ft_strlcat((*mas), my_shell->control[si]->exe->full_name, \
	size + size_p + 2);
	if (!access((*mas), F_OK))
	{
		if (!access((*mas), X_OK))
		{
			free(my_shell->control[si]->exe->full_name);
			return ((*mas));
		}
	}
	free((*mas));
	return (0);
}

char	*check_procces(t_shell *my_shell, int si, int size, int size_p)
{
	int		i;
	char	*mas;

	i = 0;
	if (!ft_strrchr(my_shell->control[si]->exe->full_name, '/'))
	{
		while (my_shell->full_path[i])
		{
			if (check_procces_2(my_shell, i, si, &mas))
				return (mas);
			++i;
		}
		my_shell->control[si]->exe->error = 127;
		return (my_shell->control[si]->exe->full_name);
	}
	if (access(my_shell->control[si]->exe->full_name, F_OK))
		my_shell->control[si]->exe->error = 126;
	else
		if (access(my_shell->control[si]->exe->full_name, X_OK))
			my_shell->control[si]->exe->error = 125;
	return (my_shell->control[si]->exe->full_name);
}

int	chreat_process(t_shell *my_shell, int i)
{
	char	**cp_option;
	int		j;
	int		j2;

	j = 0;
	j2 = 0;
	my_shell->full_path = get_path(my_shell->my_envp);
	cp_option = malloc(sizeof(char *) * \
	(size_list(my_shell->control[i]->exe->options) + 2));
	if (!cp_option)
		malloc_error();
	cp_option[j++] = ft_strdup(my_shell->control[i]->exe->full_name);
	while (my_shell->control[i]->exe->options && \
	my_shell->control[i]->exe->options[j2])
		cp_option[j++] = my_shell->control[i]->exe->options[j2++];
	cp_option[j] = 0;
	free(my_shell->control[i]->exe->options);
	my_shell->control[i]->exe->options = cp_option;
	my_shell->control[i]->exe->full_name = check_procces(my_shell, i, 0, 0);
	two_dimensional_mas(&my_shell->full_path);
	return (my_shell->control[i]->exe->error);
}
