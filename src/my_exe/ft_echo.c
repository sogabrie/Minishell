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
	jik.ptr = NULL;
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
			free(jik.ptr);
		}
		else
			new_line[jik.j++] = (jik.str)[jik.i++];
		jik.k = 0;
	}
	new_line[jik.j] = '\0';
	return (free_return(jik.str, new_line));
}

void	execute_echo(char **args, char **envp, int error, size_t *flag_n)
{
	char	*line;
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (args[++i])
	{
		if (ft_strlen(args[i]) == 0)
			printf(" ");
		line = parse_line(args[i], envp, error, 0);
		line = parse_wild(line);
		if (line == NULL)
			continue ;
		if (flag == 0 && line[0] == '-' && check_flag(line + 1, flag_n))
		{
			free(line);
			continue ;
		}
		printf("%s", line);
		if (args[i + 1] != NULL)
			printf(" ");
		flag = 1;
		free(line);
	}
}

int	ft_echo(char **args, char **envp, int error)
{
	char	*line;
	size_t	flag_n;

	flag_n = 0;
	if (args == NULL || args[0] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	execute_echo(args, envp, error, &flag_n);
	if (flag_n == 0)
		printf("\n");
	return (0);
}
