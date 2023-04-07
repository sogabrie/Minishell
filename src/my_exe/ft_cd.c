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

// char *search_oldpwd(char **envp)
// {
//     size_t  i;
//     char    *old_pwd;

//     i = 0;
//     while(envp[i])
//     {
//         if(!ft_strncmp("OLDPWD=", envp[i], 7))
//         {
//             old_pwd = ft_strdup(envp[i] + 7);
//             printf("old_pwd = %s\n", old_pwd);
//             return (old_pwd);
//         }
//         i++;
//     }
//     return (NULL);
// }

// void    old_new_pwd(char *old_pwd, char *home, char **envp)
// {
//     size_t  i;

//     i = 0;
//     while(envp[i])
//     {
//         if()
//         i++;
//     }
// }

// int ft_cd(char *dir, char ***envp)
// {
// 	char    *home;
// 	char    *old_pwd;

//     old_pwd = search_oldpwd(*envp);
//     home = search_home(*envp);
// 	if (ft_strlen(dir) == 0)
// 	{
// 		if(chdir(home) < 0);
// 		{
// 			write(2, "minishell: cd: adsa: No such file or directory\n", 47);
// 			free(home);
// 			return (-1);
// 		}
//         envp = old_new_pwd(old_pwd, home, envp);
// 		free(home);
// 		return (0);
// 	}
// 	if (!ft_strcmp("-", dir))
// 	{
//         if(old_pwd == NULL)
//         {
//             write(2, "minishell: cd: OLDPWD not set\n", 30);
//             return (-1);
//         }
//         exit = chdir(old_pwd);
//         free(old_pwd);
//         return (0);
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