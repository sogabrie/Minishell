#include "minishell.h"

char	*creat_tmp_file(int last_number, char *tmp_file)
{
	char	*name_file;
	char	*number_file;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	number_file = ft_itoa(last_number);
	if (number_file == NULL)
		malloc_error();
	name_file = malloc(sizeof(char) * (ft_strlen(number_file) + 33));
	if (number_file == NULL)
		malloc_error();
	while (tmp_file[i] != '\0')
		name_file[j++] = tmp_file[i++];
	i = 0;
	while (number_file[i] != '\0')
		name_file[j++] = number_file[i++];
	name_file[j] = '\0';
	free(number_file);
	number_file = NULL;
	return (name_file);
}

int	here_doc(char *end, int flag_check)
{
	static int	last_number;
	int			fd_write;
	char		*file_name;
	char		*buffer;

	if (flag_check == 1)
		return (last_number);
	file_name = creat_tmp_file(last_number, "src/here_doc/tmp_file");
	fd_write = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd_write < 0)
		return (error_here_doc(fd_write));
	while (1)
	{
		write(0, "> ", 2);
		buffer = get_next_line(0);
		if (!ft_strcmp_flag(buffer, end, 1))
			break ;
		ft_putstr_fd(buffer, fd_write);
		free(buffer);
	}
	free(buffer);
	free(file_name);
	last_number++;
	return (fd_write);
}
