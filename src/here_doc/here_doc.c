/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:50:53 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 21:37:17 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dol_lar(char *buffer, size_t *i, char **envp)
{
	char	*var;
	char	*line;
	size_t	start;

	start = (*i);
	(*i)++;
	while (buffer[(*i)] && \
		!ft_strchr("@#%^$*}]{+=$? \n\t.,-[|/>\'\"<;:~\\", buffer[(*i)]))
		(*i)++;
	var = ft_substr(buffer, start, (*i) - start);
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

void	do_here_doc(size_t *i, char *buffer, \
		char *new_buffer, t_shell *my_shell)
{
	char	*line;
	size_t	k;

	k = 0;
	if (buffer[i[0]] == '$' && buffer[i[0] + 1] == '?')
	{
		here_doc_1(my_shell, &k, new_buffer, &i[1]);
		i[0] += 2;
	}
	else if (buffer[i[0]] == '$')
	{
		line = dol_lar(buffer, &i[0], my_shell->my_envp);
		while (line[k])
			new_buffer[i[1]++] = line[k++];
		free(line);
	}
	else
		new_buffer[i[1]++] = buffer[i[0]++];
}

char	*open_variable_doc(char *buffer, t_shell *my_shell)
{
	size_t	i[2];
	char	*new_buffer;

	i[0] = 0;
	i[1] = 0;
	new_buffer = malloc(sizeof(char) * \
		count_variable_doc(buffer, my_shell->my_envp) + 2);
	if (new_buffer == NULL)
		malloc_error();
	while (buffer[i[0]])
		do_here_doc(i, buffer, new_buffer, my_shell);
	new_buffer[i[1]++] = '\n';
	new_buffer[i[1]] = '\0';
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
		if (buffer == NULL)
			break ;
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
