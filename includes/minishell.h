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
int				check_access(char *directory, int check_number);
char			*update_shlvl(char *envp, int lvl);
char			**replace_envp(char **envp);
int				lvl_check(char *envp);
char			**fill_envp(char **envp, char **new_envp);
//cd_utils
char			*search_podh(char **envp, char *name, size_t count);
void			adding_dir(char **old_pwd, char **home, \
								char **pwd, char ***envp);
char			*valid_dir(char *dir, char *home);

//Here_Doc
int				here_doc(char *end, int fd_write);
char			*creat_tmp_file(int last_number, char *tmp_file);

//My_exe
int				ft_pwd(void);

//Wildcards
char			**wildcards(char *wild_string);
int				check_mid(char **stars, size_t i_object, char *object_name);
int				check_suitable(char *object_name, char *wild_string, \
						char **stars, char *tmp_object_name);
char			*creat_object_name(size_t end, size_t start, char *object_name);
char			*replace_wild_string(size_t start, \
							size_t end, char *wild_string);
char			**split_tmp_wild_string(char *wild_string, \
						size_t i_wild_start, size_t i_wild_end);
char			**creat_found_objects(char **found_objects, char *name);

//Errors
void			malloc_error(void);
int				error_here_doc(void);
void			cd_error(char *dir, int number);

//Free
void			two_dimensional_mas(char ***str);
int				free_tmp_stars(char **stars, char **tmp_object_name, int exit);
int				free_object_cd(char *new_dir, char *home, \
								char *old_pwd, char *pwd);

#endif