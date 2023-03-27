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

typedef enum s_error_type
{
	NO_ERROR = 0
}	t_error_type;

typedef struct s_exe
{
	char	*full_name;
	char	**options;
	char	**ptr_avp;
}	t_exe;

typedef struct s_option
{
	char	*options_name;
}	t_option;

typedef struct s_my_exe
{
	char	*name;
	char	*options;
}	t_my_exe;

typedef struct s_my_option
{
	
}	t_my_option;

typedef struct s_redirections
{
	
}	t_redirections;

typedef struct s_pipe
{
	
}	t_pipe;

typedef struct s_variables	
{
	
}	t_variables	;

typedef struct s_priorities
{
	
}	t_priorities;

typedef struct s_wildcards	
{
	
}	t_wildcards	;

typedef struct s_control
{
	t_exe			*to_exe;
	t_option		*to_option;
	t_my_exe		*to_my_exe;
	t_my_option		*to_my_option;
	t_redirections	*to_redirections;
	t_pipe			*to_pipe;
	t_variables		*to_variable;
	t_priorities	*to_prioritet;
	t_wildcards		*to_wildcards;
	t_command_type	command_type;
	t_error_type	to_error;
}	t_control;

#endif