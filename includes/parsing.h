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
int				check_metachar(t_shell	*my_shell);

//delimiter
int				creat_delimiter(t_shell	*my_shell);

#endif