#include "minishell.h"

int	red_out(char *filename)
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
	file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00755);
	if (file < 0)
	{
		char *a = strerror(error);
		//printf("%s\n", a);
		perror("a");
	}
	return (file);
}