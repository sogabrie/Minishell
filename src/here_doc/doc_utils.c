#include "minishell.h"

char	*path_tmp(void)
{
	char	buf[256];
	char	*tmp_p;
	char	*dir;

	dir = getcwd(buf, sizeof(buf));
	tmp_p = ft_strdup("/src/here_doc/tmp");
	if (tmp_p == NULL)
		malloc_error();
	dir = ft_strjoin(dir, tmp_p);
	if (dir == NULL)
		malloc_error();
	free(tmp_p);
	return (dir);
}

int	count_tmp_files(char *path_t)
{
	int				count;
	DIR				*directory;
	struct dirent	*entry;

	count = 0;
	directory = opendir(path_t);
	while (1)
	{
		entry = readdir(directory);
		if (entry == NULL)
			break ;
		if (!ft_strncmp(entry->d_name, "tmp_file", 8))
			count++;
	}
	closedir(directory);
	return (count);
}

int	del_tmp_files(int index, char *path_h, char *suc_path, char *del_path)
{
	DIR				*directory;
	struct dirent	*entry;

	directory = opendir(path_h);
	while (1)
	{
		entry = readdir(directory);
		if (entry == NULL)
			break ;
		if (ft_atoi(entry->d_name + 8) >= index)
		{
			suc_path = ft_strjoin("/", entry->d_name);
			if (suc_path == NULL)
				malloc_error();
			del_path = ft_strjoin(path_h, suc_path);
			if (del_path == NULL)
				malloc_error();
			unlink(del_path);
			free(suc_path);
			free(del_path);
		}
	}
	closedir(directory);
	return (count_tmp_files(path_h));
}

char	*creat_name(int count, char *path_t, size_t	i, char *name)
{
	char	*name_file;
	char	*number_file;
	size_t	j;

	j = 0;
	number_file = ft_itoa(count);
	if (number_file == NULL)
		malloc_error();
	name_file = malloc(sizeof(char) * \
		(ft_strlen(path_t) + ft_strlen(number_file) + 10));
	if (name_file == NULL)
		malloc_error();
	while (path_t[i])
		name_file[j++] = path_t[i++];
	i = 0;
	name_file[j++] = '/';
	while (name[i])
		name_file[j++] = name[i++];
	i = 0;
	while (number_file[i])
		name_file[j++] = number_file[i++];
	name_file[j] = '\0';
	free(number_file);
	return (name_file);
}
