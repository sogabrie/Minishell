// #include "minishell.h"

// // 0 ameninch normala
// // -1 ete sxala

// int ft_cd(char *dir, char **envp)
// {
    
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
//     if(chdir(argv[1]) < 0)
//         printf("error\n");
//     if(getcwd(buf, sizeof(buf)) != NULL) {
// 		  printf("Текущая рабочая директория: %s\n", buf);
// 	} else {
// 		  printf("Ошибка получения текущей рабочей директории\n");
// 	}
// 	return 0;
// }