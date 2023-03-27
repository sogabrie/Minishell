/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:34:39 by sogabrie          #+#    #+#             */
/*   Updated: 2023/03/27 17:28:04 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef enum s_command_type
{
	EXE,
	OPTION,
	MY_EXE,
	MY_OPTION,
	REDIRECTIONS,
	PIPE,
	VARIABLE,
	PRIORITET,
	WILDCARDS,
}	t_command_type;

typedef struct s_exe
{
	
}	t_exe;

typedef struct s_control
{
	t_command_type	command_type;
	t_exe			*to_exe;
	// t_option		*to_option;
	// t_my_exe		*to_my_exe;
	// t_my_option		*to_my_option;
	// t_redirections	*to_redirections;
	// t_pipe			*to_pipe;
	// t_variables		*to_variable;
	// t_priorities	*to_prioritet;
	// t_wildcards		*to_wildcards;
	// t_error			*to_error;
}	t_control;

#endif