#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

typedef enum s_command_type
{
	MY_NULL = 0,
	EXE,
	MY_EXE,
	PIPE,
	PRIORITET,
	LOGIC_AND,
	LOGIC_OR
}	t_command_type;

typedef enum s_error_type
{
	NO_ERROR = 0,
	C_N_F =		404
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

// typedef struct s_pipe
// {
// 	int				fd_pip[2];
// }	t_pipe;

typedef struct s_priorities
{
	int				status;
	int				start;
	int				end;
	int				fd_output;
	int				fd_input;
}	t_priorities;

typedef struct s_control
{
	t_exe			*exe;
	t_my_exe		*my_exe;
	int				pip[2];
	// t_pipe			*pipe;
	t_priorities	*prioritet;
	int				logic_and;
	int				logic_or;
	int				fd_output;
	int				fd_input;
	t_command_type	command_type;
	t_error_type	error;
}					t_control;

typedef struct s_shell
{
	char			*line;
	char			**double_list;
	char			**my_envp;
	char			**full_path;
	int				*delimiter;
	int				delimiter_count;
	t_control		**control;
	unsigned int	count;
	t_error_type	my_error;
}					t_shell;

#endif