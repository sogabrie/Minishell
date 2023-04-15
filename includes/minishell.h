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
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

//Utils
int				check_access(char *directory, int check_number);
char			*update_shlvl(char *envp, int lvl, int flag_z);
char			**replace_envp(char **envp);
int				lvl_check(char *envp, int *flag_z);
char			*search_envp_in(char **envp, char *obj, int count);
char			**fill_envp(char **envp, char **new_envp);

//cd_utils
int				check_dir(char *dir);
char			*search_podh(char **envp, char *name, size_t count);
void			adding_dir(char **old_pwd, char **home, \
								char **pwd, char ***envp);
char			*valid_dir(char *dir, char *home);

//export_utils
int				valid_variable(char *str, char **envp);
int				first_char(char *str, char **envp);
int				check_inside(char *str, size_t start);

//Here_Doc
int				here_doc(char *end, int fd_write, char **envp, char *buffer);
char			*creat_tmp_file(int last_number, char *tmp_file, \
									char *shlvl, char *number_file);

//My_exe
int				ft_pwd(void);
int				ft_cd(char *dir, char ***envp, char *new_dir, char *pwd);
int				ft_env(char **envp, int f_export);
int				ft_export(char **str, char ***envp);

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
char			**creat_more_objects(char **found_objects, char *name);

//Errors
void			malloc_error(void);
int				error_here_doc(void);
void			exe_error(char *dir, int number, char *my_exe);

//Free
void			two_dimensional_mas(char ***str);
int				free_tmp_stars(char **stars, char **tmp_object_name, int exit);
int				free_object_cd(char *new_dir, char *home, \
								char *old_pwd, char *pwd);

#endif