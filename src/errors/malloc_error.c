#include "minishell.h"

void	malloc_error(void)
{
	write(1, "Memory allocation error!!\n", 26);
	exit(1);
}
