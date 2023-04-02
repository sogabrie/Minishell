#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_command_type
{
	EXE,
	MY_EXE,
	PIPE,
	PRIORITET,
	LOGIC_AND,
	LOGIC_OR
}	t_command_type;

typedef enum s_error_type
{
	NO_ERROR = 0
}	t_error_type;

typedef struct s_exe
{
	int				status;
	char			*full_name;
	char			**options;
	char			**ptr_envp;
	int				fd_output;
	int				fd_input;
}	t_exe;

typedef struct s_my_exe
{
	int				staatus;
	char			*name;
	char			*options;
	int				fd_output;
	int				fd_input;
}	t_my_exe;

typedef struct s_pipe
{
	int				fd_pip[2];
}	t_pipe;

typedef struct s_priorities
{
	int				status;
	int				start;
	int				end;
}	t_priorities;

typedef struct s_control
{
	t_exe			*exe;
	t_my_exe		*my_exe;
	t_pipe			*pipe;
	t_priorities	*prioritet;
	int				logic_and;
	int				logic_or;
	t_command_type	command_type;
	t_error_type	error;
}					t_control;

typedef struct s_shell
{
	char			*line;
	char			**double_list;
	char			**my_envp;
	t_control		*control;
	size_t			count;
}					t_shell;

#endif