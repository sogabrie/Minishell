// #include "minishell.h"

// // 0 ameninch normala
// // -1 ete sxala

// char *search_home(char **envp)
// {
// 	size_t  i;
// 	char    *home;

// 	i = 0;
// 	while(envp[i])
// 	{
// 		if(!ft_strncmp("HOME=", envp[i], 5))
// 		{
// 			home = ft_strdup(envp[i] + 5);
// 			printf("home = %s\n", home);
// 			return home;
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char *search_oldpwd(char *)

// int ft_cd(char *dir, char ***envp)
// {
// 	int     exit;
// 	char    *home;
// 	char	*old_pwd;

// 	if (ft_strlen(dir) == 0)
// 	{
// 		home = search_home(*envp);
// 		exit = chdir(home);
// 		if (exit == -1)
// 		{
// 			write(2, "minishell: cd: adsa: No such file or directory\n", 47);
// 			free(home);
// 			return (-1);
// 		}
// 		free(home);
// 		return (0);
// 	}
// 	if (!ft_strcmp("-", dir))
// 	{
// 		old_pwd = search_oldpwd(envp)
// 	}
// 	chdir(dir);
// 	return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	char buf[256];
// 	char **my_envp = replace_envp(envp);
// 	if(getcwd(buf, sizeof(buf)) != NULL) {
// 		  printf("Текущая рабочая директория: %s\n", buf);
// 	} else {
// 		  printf("Ошибка получения текущей рабочей директории\n");
// 	}
// 	ft_cd(argv[1], &envp);
// 	if(getcwd(buf, sizeof(buf)) != NULL) {
// 		  printf("Текущая рабочая директория: %s\n", buf);
// 	} else {
// 		  printf("Ошибка получения текущей рабочей директории\n");
// 	}
// 	return 0;
// }