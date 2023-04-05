#include "minishell.h"
#include "struct.h"

void	cat_char(char *line, int i)
{
	while (line[i])
	{
		line[i] = line[i + 1];
		++i;
	}
}

void	remov_quote(char *line, int i, char a)
{
	cat_char(line, i);
	while (line[i])
	{
		if (line[i] == a)
		{
			cat_char(line, i);
			return ;
		}
		++i;
	}
}

char	*echo_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\'')
		{
			remov_quote(line, i, '\'');
			return (line);
		}
		if (line[i] == '\"')
		{
			remov_quote(line, i, '\"');
			return (line);
		}
		++i;
	}
	return (line);
}

int	ft_echo(char *line, int fd)
{
	int	i;
	int	error;

	i = 0;
	line = echo_line(line);
	while (line[i])
	{
		error = write(fd, &(line[i++]), 1);
		if (error != 1)
		{
			char *a = strerror(error);
			//printf("%s\n", a);
			perror("a");
			return (error);
		}
	}
	return (0);
}
