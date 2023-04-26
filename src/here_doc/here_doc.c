#include "minishell.h"

char	*dol_lar(char *buffer, size_t *i, char **envp)
{
	char	*var;
	char	*line;
	size_t	start;

	start = *i;
	(*i)++;
	while (buffer[*i] && \
		!ft_strchr("@#%^$*}]{+=$? \n\t.,-[|/>\'\"<;:~\\", buffer[*i]))
		(*i)++;
	var = ft_substr(buffer, start, *i - start);
	if (var == NULL)
		malloc_error();
	line = echo_line(var, envp, NULL, 0);
	free(var);
	return (line);
}

size_t	count_variable_doc(char *buffer, char **envp)
{
	size_t	i;
	size_t	count;
	char	*line;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$')
		{
			line = dol_lar(buffer, &i, envp);
			count += ft_strlen(line);
			free(line);
		}	
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

size_t	do_here_doc(size_t *i, char *buffer, \
		char *new_buffer, t_shell *my_shell)
{
	char	*line;
	size_t	k;
	size_t	j;

	k = 0;
	j = 0;
	if (buffer[(*i)] == '$' && buffer[(*i) + 1] == '?')
	{
		here_doc_1(my_shell, &k, new_buffer, &j);
		(*i) += 2;
	}
	else if (buffer[(*i)] == '$')
	{
		line = dol_lar(buffer, i, my_shell->my_envp);
		while (line[k])
			new_buffer[j++] = line[k++];
		free(line);
	}
	else
		new_buffer[j++] = buffer[(*i)++];
	return (j);
}

char	*open_variable_doc(char *buffer, t_shell *my_shell)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	j = 0;
	new_buffer = malloc(sizeof(char) * \
		count_variable_doc(buffer, my_shell->my_envp) + 2);
	if (new_buffer == NULL)
		malloc_error();
	while (buffer[i])
		j = do_here_doc(&i, buffer, new_buffer, my_shell);
	new_buffer[j++] = '\n';
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*here_doc(char *end, int count, char *path_t, t_shell *my_shell)
{
	char	*file_name;
	char	*buffer;
	int		fd_write;

	file_name = creat_name(count, path_t, 0, "tmp_file");
	fd_write = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd_write <= 0)
		return (error_here_doc(file_name));
	while (1)
	{
		buffer = readline("> ");
		buffer = open_variable_doc(buffer, my_shell);
		if (buffer == NULL || !ft_strcmp_flag(buffer, end, 1))
			break ;
		ft_putstr_fd(buffer, fd_write);
		free(buffer);
	}
	free(buffer);
	close(fd_write);
	return (file_name);
}
