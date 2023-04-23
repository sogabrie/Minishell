#include "minishell.h"

char	*creat_tmp_file(int last_number, char *tmp_file, \
							char *shlvl, char *number_file)
{
	char	*name_file;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	number_file = ft_itoa(last_number);
	if (number_file == NULL)
		malloc_error();
	name_file = malloc(sizeof(char) * \
			(ft_strlen(number_file) + ft_strlen(shlvl) + 33));
	if (number_file == NULL)
		malloc_error();
	while (tmp_file[i] != '\0')
		name_file[j++] = tmp_file[i++];
	i = 0;
	while (shlvl[i] != '\0')
		name_file[j++] = shlvl[i++];
	i = 0;
	while (number_file[i] != '\0')
		name_file[j++] = number_file[i++];
	name_file[j] = '\0';
	free(number_file);
	number_file = NULL;
	return (name_file);
}

int	here_doc(char *end, int fd_write, char **envp, char *buffer)
{
	static int	last_number;
	char		*file_name;

	if (fd_write == 1)
		return (last_number);
	file_name = creat_tmp_file(last_number, "src/here_doc/tmp_file", \
						search_envp_in(envp, "SHLVL", 5), NULL);
	fd_write = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd_write < 0)
		return (error_here_doc());
	while (1)
	{
		write(0, "> ", 2);
		buffer = readline(NULL);
		if (buffer == NULL || !ft_strcmp_flag(buffer, end, 1))
			break ;
		ft_putstr_fd(buffer, fd_write);
		free(buffer);
	}
	free(buffer);
	close(fd_write);
	fd_write = open(file_name, O_RDONLY);
	free(file_name);
	last_number++;
	return (fd_write);
}

// int	count_tmp_file(void)
// {
// 	int		count;
// 	DIR		*dir;
// 	char	**files;

// 	count = 0;
// 	dir = opendir("/tmp/Minishell_tmp");
// 	if (dir == NULL)
// 	{
// 		printf("ERROR DIR\n");
// 		exit(1);
// 	}
// 	files = wildcards(ft_strdup("tmp_file*"));
// 	printf("%s\n", files);
// 	if (files == NULL)
// 		return (count);
// 	while (files[count])
// 		count++;
// 	return (count);
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	int count = count_tmp_file();
// 	printf("%d\n", count);
// }