#include "minishell.h"

typedef struct s_oper {
	size_t	i;
	size_t	k;
	size_t	j;
	char	*ptr;
	char	*str;
}	t_oper;

char	*new_line_creat(char *line)
{
	char	*new_line;

	new_line = ft_strtrim(line, "\'");
	if (new_line == NULL)
		malloc_error();
	return (new_line);
}

char	*echo_line(char *line, char **envp, char *new_line, int error)
{
	t_oper	jik;

	jik.i = 0;
	jik.j = 0;
	jik.k = 0;
	if (line[jik.i] == '\'')
		return (new_line_creat(line));
	jik.str = ft_strtrim(line, "\"");
	new_line = creat_new_line((jik.str), envp, -1, 0);
	while ((jik.str)[jik.i])
	{
		if ((jik.str)[jik.i] == '$' && (jik.str)[jik.i + 1] != '\0')
		{
			jik.ptr = variable((jik.str) + jik.i + 1, &(jik.i), envp, error);
			while ((jik.ptr) && (jik.ptr)[jik.k])
				new_line[jik.j++] = (jik.ptr)[jik.k++];
		}
		else
			new_line[jik.j++] = (jik.str)[jik.i++];
		jik.k = 0;
	}
	new_line[jik.j] = '\0';
	free(jik.str);
	return (new_line);
}

int	ft_echo(char **args, char **envp, int error, int i)
{
	char	*line;
	size_t	flag_n;

	flag_n = 0;
	if (args == NULL || args[0] == NULL || args[0][0] == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[++i])
	{
		line = echo_line(args[i], envp, NULL, error);
		if (line[0] == '-' && check_flag(line + 1, &flag_n))
		{
			free(line);
			continue ;
		}
		printf("%s", line);
		if (args[i + 1] != NULL)
			printf(" ");
		free(line);
	}
	if (flag_n == 0)
		printf("\n");
	return (0);
}
