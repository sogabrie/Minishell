#include "minishell.h"

int ft_export(char *str, char ***envp)
{
    if (ft_strlen(str) == 0)
        return (ft_env(*envp, 1));
    
    return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
//     char **my_envp = replace_envp(envp);
//     // ft_env(my_envp, 0);
//     ft_export("", &my_envp);
// }