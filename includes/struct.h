#ifndef STRUCT_H
# define STRUCT_H

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
	char	**ptr_envp;
}	t_exe;

typedef struct s_my_exe
{
	char	*name;
	char	*options;
}	t_my_exe;

typedef struct s_redir_output
{
	
}	t_redir_output;

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
	t_exe			*exe;
	t_my_exe		*my_exe;
	t_redir_output	*redir_output;
	t_pipe			*pipe;
	t_variables		*variable;
	t_priorities	*prioritet;
	t_wildcards		*wildcards;
	t_command_type	command_type;
	t_error_type	error;
}	t_control;

#endif