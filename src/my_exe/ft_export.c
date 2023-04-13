// #include "minishell.h"

// int valid_variable(char *str)
// {
//     size_t  i;

//     i = 0;
//     if(ft_strchr("0123456789", str[0]))
//     {
//         exe_error(str, 98, " export: ");
//         return (1);
//     }

// }

// int ft_export(char **str, char ***envp)
// {
//     int  i;

//     i = -1;
//     if (str[0] == NULL)
//         return (ft_env(*envp, 1));
//     while (str[++i])
//     {
//         if (valid_variable(str[i]))
//             continue ;
//         printf("%s\n", str[i]);
//     }
//     return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
//     char **my_envp = replace_envp(envp);
//     char **str = ft_split("2a123", ' ');
//     ft_export(str, &my_envp);
// }