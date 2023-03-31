#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

//Utils
char			*update_shlvl(char *envp);
char			**replace_envp(char **envp);

//Main
void			main_parsing(char *line, char **envp);
t_error_type	pars_quote(char ***double_list);

//Errors
void			malloc_error(void);

#endif