#include "minishell.h"

//0 ameninch normala
//-1 ete sxala

// char *search_home_dir(char **envp)
// {
// 	size_t	i;
// 	char	*home_dir;

// 	i = 0;
// 	while(envp[i])
// 	{
// 		if(!ft_strncmp("HOME", envp[i], 4))
// 		{
// 			home_dir

// 		}
// 		i++;
// 	}
// }

// int fd_cd(char *dir, char **envp)
// {
// 	static char		*past_dir;
// 	char			*home_dir;
// 	char			buf[256];
	
// 	if (ft_strlen(dir) == 0 || !ft_strcmp("$HOME", dir) || !ft_strcmp("~", dir))
// 	{
// 		home_dir = search_home_dir(envp);
// 		return (0);
// 	}
// 	return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	char buf[256];
// 	char **my_envp = replace_envp(envp);
// 	// fd_cd("$HOME", my_envp);
// 	if(getcwd(buf, sizeof(buf)) != NULL) {
// 		  printf("Текущая рабочая директория: %s\n", buf);
// 	} else {
// 		  printf("Ошибка получения текущей рабочей директории\n");
// 	}
// 	return 0;
// }