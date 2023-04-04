#include "minishell.h"

int	red_out_append(char *filename)
{
	int	file;

	if (!access(av[ac - 1], F_OK))
	{
		if (access(av[ac - 1], W_OK))
		{
			char *a = strerror(error);
			//printf("%s\n", a);
			perror("a");
			return (-1);
		}
	}
	file = open(filename, O_CREAT | O_WRONLY | O_APPEND, 00755);
	if (file < 0)
	{
		char *b = strerror(error);
		//printf("%s\n", b);
		perror("a");
	}
	return (file);
}