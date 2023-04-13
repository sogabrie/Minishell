#include "minishell.h"

int ft_export(char **str, char ***envp)
{
    if (str == NULL)
        return (ft_env(*envp, 1));
    
    return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
//     char **my_envp = replace_envp(envp);
//     char **str = ft_split("", ' ');
//     // ft_env(my_envp, 0);
//     ft_export(NULL, &my_envp);
// }