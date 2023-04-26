/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:46:37 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 19:46:38 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "minishell.h"

void	creat_redir(t_shell *my_shell)
{
	my_shell->redirect = malloc (sizeof(t_redir *));
	if (!my_shell->redirect)
		malloc_error();
	my_shell->redirect[0] = malloc (sizeof(t_redir));
	if (!my_shell->redirect[0])
		malloc_error();
	my_shell->redirect[my_shell->count_redir]->filename = 0;
	++my_shell->count_redir;
}

void	creat_cont_mas(t_shell *my_shell)
{
	my_shell->control = malloc (sizeof(t_control *));
	if (!my_shell->control)
		malloc_error();
	my_shell->control[0] = malloc (sizeof(t_control));
	if (!my_shell->control[0])
		malloc_error();
	init_control(my_shell->control, 0);
	++my_shell->count;
}
