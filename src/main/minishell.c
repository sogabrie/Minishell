#include "minishell.h"

int main()
{
    while(1)
        printf("%s\n", readline("test> "));
    return 0;
}