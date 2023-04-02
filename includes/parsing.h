#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "struct.h"
# include "libft.h"

t_error_type	control_pars(t_shell *my_shell);
void			main_parsing(t_shell *my_shell);

#endif