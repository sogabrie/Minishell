// #include "minishell.h"

// int export_number_error(char *str)
// {
//     ft_putstr_fd("minishell: export: ", 2);
//     write(2, "`", 1);
//     ft_putstr_fd(str, 2);
//     write(2, "'", 1);
//     ft_putendl_fd(": not a valid identifier", 2);
//     return (1);
// }

// int valid_variable(char *str)
// {
//     size_t  i;

//     i = 0;
//     if(ft_strchr("0123456789", str[0]))
//         return (export_number_error(str));
//     return (0);
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