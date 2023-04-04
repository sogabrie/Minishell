#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "struct.h"
# include "libft.h"
# include <string.h>

t_error_type	control_pars(t_shell *my_shell, int i, int j, int n);
void			main_parsing(t_shell *my_shell);

t_error_type	control_pars_3(t_shell *my_shell, int *i, int *j, int *n);
t_error_type	control_pars_4(t_shell *my_shell, int *i, int *j, int *n);
t_error_type	control_pars_5(t_shell *my_shell, int *i, int *j, int *n);

void			cp_free(char ***list, char ***cp);
char			*my_cat(char *list, int start, int end);
int				size_list(char **list);

//echo.c

int				ft_echo(char *line, int fd);
char			*echo_line(char *line);

#endif