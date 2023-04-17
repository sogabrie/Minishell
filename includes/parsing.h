#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "struct.h"
# include "libft.h"
# include <string.h>


void			init_shell(t_shell *my_shell);

//parsing.c
t_error_type	control_pars(t_shell *my_shell, int i, int j, int n);
void			main_parsing(t_shell *my_shell);

//pars_quote
t_error_type	control_pars_2(t_shell *my_shell, int *i, int *j, int *n);
t_error_type	control_pars_3(t_shell *my_shell, int *i, int *j, int *n);
t_error_type	control_pars_4(t_shell *my_shell, int *i, int *j, int *n);
t_error_type	control_pars_5(t_shell *my_shell, int *i, int *j, int *n);

//pars_quote_utils.c
void			cp_free(char ***list, char ***cp);
char			*my_cat(char *list, int start, int end);
int				size_list(char **list);

//pars_util.c
int				check_redirect(char *name);
int				check_my_exe(char *name);
int				check_end(char *name);

//echo.c
int				ft_echo(char *line, int fd);
char			*echo_line(char *line);

//pars_env_and_access.c
long			check_procces(char **pro, char **path, int size, int size_p);
char			**get_path(char **avp);

//check_parenthesis.c
int				check_paren(t_shell	*my_shell);

//check_metacharacters.c
int				check_metachar_and_redirect(char *c);
t_error_type	check_metachar(t_shell	*my_shell);

//delimiter
int				creat_delimiter(t_shell	*my_shell);

// inicalization.c
void			chreat_cont(t_shell *my_shell);

// creat_main_struct.c
void			creat_struct_pip(t_shell *my_shell);
void			creat_struct_and(t_shell *my_shell);
void			creat_struct_or(t_shell	*my_shell);
void			creat_struct_prioritet_start(t_shell *my_shell);
void			creat_struct_prioritet_end(t_shell *my_shell);

//creat_my_exe.c
void			creat_my_exe(t_shell *my_shell, char *name);
t_error_type	creat_redirect(t_shell *my_shell, int *i);
void			add_option(t_shell *my_shell, char *name);
void			creat_exe(t_shell *my_shell, char *name);

//here_doc
int				red_input(char *filename);
int				red_out_append(char *filename);
int				red_out(char *filename);

//constrol_parsing.c
void			control_parsing(t_shell	*my_shell);

//free_struct.c
void			free_struct(t_shell *my_shell);

//creat_close_fd.c
void			creat_close_fd(t_shell *my_shell, int fd);

#endif