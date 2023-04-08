// #include "minishell.h"

// // 0 ameninch normala
// // -1 ete sxala

// char *search_podh(char **envp, char *name, size_t count)
// {
// 	size_t  i;
// 	char    *home;

// 	i = 0;
// 	while(envp[i])
// 	{
// 		if(!ft_strncmp(name, envp[i], count))
// 		{
// 			home = ft_strdup(envp[i] + count);
// 			return home;
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char	**old_new_pwd(char *old_pwd, char *pwd, char **envp, char *dir)
// {
// 	size_t  i;
// 	char **new_envp;

// 	i = 0;
// 	while(envp[i])
// 		i++;
// 	if(old_pwd == NULL)
// 		i++;
// 	new_envp = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while(envp[i])
// 	{
// 		if(!ft_strncmp("PWD=", envp[i], 4))
// 			new_envp[i] = ft_strjoin("PWD=", dir);
// 		else if(!ft_strncmp("OLDPWD=", envp[i], 7))
// 			new_envp[i] = ft_strjoin("OLDPWD=", pwd);
// 		else
// 			new_envp[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	if(old_pwd == NULL)
// 		new_envp[i++] = ft_strjoin("OLDPWD=", pwd);
// 	new_envp[i] = NULL;
// 	two_dimensional_mas(&envp);
// 	return (new_envp);
// }

// int ft_cd(char *dir, char ***envp)
// {
// 	char    *home;
// 	char    *old_pwd;
// 	char	*pwd;
// 	char buf[256];

// 	old_pwd = search_podh(*envp, "OLDPWD=", 7);
// 	home = search_podh(*envp, "HOME=", 5);
// 	pwd = search_podh(*envp, "PWD=", 4);
// 	printf("old_pwd = %s\npwd = %s\nhome = %s\n", old_pwd, pwd, home);
// 	if (ft_strlen(dir) == 0)
// 	{
// 		if(chdir(home) < 0)
// 		{
// 			write(2, "minishell: cd: adsa: No such file or directory\n", 47);
// 			free(pwd);
// 			free(old_pwd);
// 			free(home);
// 			return (-1);
// 		}
// 		*envp = old_new_pwd(old_pwd, pwd, *envp, home);
// 	}
// 	else if (!ft_strcmp("-", dir))
// 	{
// 		if(old_pwd == NULL)
// 		{
// 			write(2, "minishell: cd: OLDPWD not set\n", 30);
// 			free(pwd);
// 			free(old_pwd);
// 			free(home);
// 			return (-1);
// 		}
// 		chdir(old_pwd);
// 		*envp = old_new_pwd(old_pwd, pwd, *envp, old_pwd);
// 	}
// 	else
// 	{
// 		if(chdir(dir) < 0)
// 		{
// 			write(2, "minishell: cd: adsa: No such file or directory\n", 47);
// 			free(pwd);
// 			free(old_pwd);
// 			free(home);
// 			return (-1);
// 		}
// 		*envp = old_new_pwd(old_pwd, pwd, *envp, getcwd(buf, sizeof(buf)));
// 	}
// 	free(pwd);
// 	free(old_pwd);
// 	free(home);
// 	return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	char buf[256];
// 	char **my_envp = replace_envp(envp);
// 	ft_cd(argv[1], &my_envp);
// 	// system("leaks minishell");
// 	// for(int i = 0; my_envp[i]; i++)
// 	// 	printf("%s\n", my_envp[i]);
// 	return 0;
// }