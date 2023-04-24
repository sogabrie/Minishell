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
	free(tmp_p);
	return (dir);
}

int count_tmp_files(char *path_t)
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
