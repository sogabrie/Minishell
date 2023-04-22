#include "minishell.h"

int	check_mid(char **stars, size_t i_object, char *object_name)
{
	size_t	count;
	char	*addres;

	count = 0;
	while (stars[count])
	{
		object_name = ft_strnstr_strlen(object_name, stars[count], i_object);
		if (object_name == NULL)
			return (1);
		count++;
	}
	return (0);
}

int	check_suitable(char *object_name, char *wild_string, \
						char **stars, char *tmp_object_name)
{
	size_t	i_wild_start;
	size_t	i_wild_end;
	size_t	i_object_start;
	size_t	i_object_end;

	if (object_name[0] == '.' && wild_string[0] != '.')
		return (1);
	i_object_end = ft_strlen(object_name) - 1;
	i_wild_end = ft_strlen(wild_string) - 1;
	while (wild_string[i_wild_end] != '*')
		if (wild_string[i_wild_end--] != object_name[i_object_end--])
			return (1);
	i_wild_start = 0;
	i_object_start = 0;
	while (wild_string[i_wild_start] != '*')
		if (wild_string[i_wild_start++] != object_name[i_object_start++])
			return (1);
	tmp_object_name = creat_object_name(i_object_end + 1, \
									i_object_start, object_name);
	stars = split_tmp_wild_string(wild_string, i_wild_start, i_wild_end);
	if (stars == NULL)
		malloc_error();
	if (check_mid(stars, ft_strlen(tmp_object_name), tmp_object_name))
		return (free_tmp_stars(stars, &tmp_object_name, 1));
	return (free_tmp_stars(stars, &tmp_object_name, 0));
}

char	**wildcards(char *wild_string)
{
	struct dirent	*entry;
	char			**found_objects;
	DIR				*directory;

	directory = opendir(".");
	found_objects = NULL;
	if (wild_string == NULL)
		return (NULL);
	while (1)
	{
		entry = readdir(directory);
		if (entry == NULL)
			break ;
		if (!check_suitable(entry->d_name, wild_string, NULL, NULL))
			found_objects = creat_found_objects(found_objects, entry->d_name);
	}
	closedir(directory);
	if (found_objects == NULL)
		return (NULL);
	free(wild_string);
	return (found_objects);
}
