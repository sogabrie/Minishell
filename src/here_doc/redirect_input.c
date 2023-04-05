#include "minishell.h"

int	red_input(char *filename)
{
	int	file;

	if (access(filename, F_OK))
	{
		printf("file chka\n");
	}
	else if (access(filename, R_OK))
	{
		printf("file chem karm kardam\n");
	}
	else
	{
		file = open(filename, O_RDONLY);
		return (file);
	}
	return (-1);
}