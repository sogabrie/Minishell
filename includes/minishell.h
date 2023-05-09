/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:51:03 by sogabrie          #+#    #+#             */
/*   Updated: 2023/05/09 17:27:41 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <limits.h> 
# include <readline/readline.h>
# include <readline/history.h>

//Utils
int				check_access(char *directory, int check_number);
char			*update_shlvl(char *envp, int lvl, int flag_z, int *flag_shlvl);
char			**replace_envp(char **envp);
int				lvl_check(char *envp, int *flag_z);
char			*search_envp_in(char **envp, char *obj, int count);
char			**fill_envp(char **envp, char **new_envp, size_t j, size_t i);
void			new_fill_envp(int flag_shlvl, char **new_envp, \
							char **envp, size_t i);

//cd_utils
int				check_dir(char *dir);
char			*search_podh(char **envp, char *name, size_t count);
void			adding_dir(char **old_pwd, char **home, \
								char **pwd, char ***envp);
char			*valid_dir(char *dir, char *home);

//export_utils
int				valid_variable(char *str);
int				first_char(char *str);
int				check_inside(char *str, size_t start);
char			*variable_name(char *str);
char			*variable_add(char *str, char *ptr);

//echo_utils
size_t			do_scop(char *str, size_t *i, char **envp);
char			*creat_new_line(char *str, char **envp, size_t i, size_t count);
int				check_flag(char *str, size_t *flag);
char			*echo_line(char *line, char **envp, char *new_line, int error);
char			*variable(char *str, size_t *i, char **envp, int error);
char			*scop_one(char *args, char end, size_t *i);
char			*var_in(char *variable_in, char **envp, size_t j, char *str);
char			*parse_scop(char *args, size_t *i, size_t count, size_t start);
char			*parse_line(char *args, char **envp, int error, size_t i);
char			*parse_wild(char *line);

//unset_utils
int				valid_unset(char *arg, int *error_code, char **envp, size_t i);
int				check_exists(char **envp, char *str);

//Here_Doc
char			*here_doc(char *end, int count, \
				char *path_t, t_shell *my_shell);
char			*creat_name(int count, char *path_t, size_t	i, char *name);
char			*path_tmp(void);
void			here_doc_1(t_shell *my_shell, \
				size_t *k, char *new_buffer, size_t *j);
int				del_tmp_files(int index, char *path_h, \
									char *suc_path, char *del_path);
int				count_tmp_files(char *path_t);

//My_exe
int				ft_pwd(void);
int				ft_cd(char *dir, char ***envp, char *new_dir, char *pwd);
int				ft_env(char **envp, int f_export);
int				ft_echo(char **args, char **envp, int error);
int				ft_export(char **str, char ***envp, int i, char *name);
int				ft_unset(char **args, char ***envp);
int				ft_exit(char **args, size_t	count, int error_code);

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
char			*error_here_doc(char *name);
void			exe_error(char *dir, int number, char *my_exe);

//Free
void			two_dimensional_mas(char ***str);
char			*free_return(char *str, char *new_line);
int				free_tmp_stars(char **stars, char **tmp_object_name, int exit);
int				free_object_cd(char *new_dir, char *home, \
								char *old_pwd, char *pwd);

#endif