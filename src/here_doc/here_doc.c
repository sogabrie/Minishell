#include "minishell.h"

char	*here_doc(char *end, int *count, char *path_t)
{
	char	*file_name;
	char	*buffer;
	int		fd_write;

	file_name = creat_name(*count, path_t, 0, "tmp_file");
	fd_write = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd_write <= 0)
		return (error_here_doc(file_name));
	while (1)
	{
		write(0, "> ", 2);
		buffer = get_next_line(0);
		if (buffer == NULL || !ft_strcmp_flag(buffer, end, 1))
			break ;
		ft_putstr_fd(buffer, fd_write);
		free(buffer);
	}
	free(buffer);
	close(fd_write);
	(*count)++;
	return (file_name);
}
