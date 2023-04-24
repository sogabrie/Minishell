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
