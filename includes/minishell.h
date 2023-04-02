#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "struct.h"
# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

//Utils
char			*update_shlvl(char *envp);
char			**replace_envp(char **envp);

//Here_Doc
int				here_doc(char *end, int flag_check);
char			*creat_tmp_file(int last_number, char *tmp_file);

//Errors
void			malloc_error(void);

#endif