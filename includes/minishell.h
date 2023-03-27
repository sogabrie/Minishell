#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

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