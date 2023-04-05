#include "minishell.h"

void	two_dimensional_mas(char ***str)
{
	size_t	i;

	i = 0;
	if (*str != NULL)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}

int	free_tmp_stars(char **stars, char **tmp_object_name, int exit)
{
	if (*tmp_object_name != NULL)
	{
		free(*tmp_object_name);
		*tmp_object_name = NULL;
	}
	two_dimensional_mas(&stars);
	return (exit);
}

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

char	*creat_object_name(size_t end, size_t start, char *object_name)
{
	char	*tmp_object_name;
	size_t	i;

	i = 0;
	tmp_object_name = malloc(sizeof(char) * ((end - start) + 1));
	if (tmp_object_name == NULL)
		malloc_error();
	while (start != end)
		tmp_object_name[i++] = object_name[start++];
	tmp_object_name[i] = '\0';
	return (tmp_object_name);
}

char	*replace_wild_string(size_t start, size_t end, char *wild_string)
{
	char	*replace_wild_string;
	size_t	i;

	i = 0;
	replace_wild_string = malloc(sizeof(char) * ((end - start) + 1));
	if (replace_wild_string == NULL)
		malloc_error();
	while (start != end)
		replace_wild_string[i++] = wild_string[start++];
	replace_wild_string[i] = '\0';
	return (replace_wild_string);
}

char	**split_tmp_wild_string(char *wild_string, \
				size_t i_wild_start, size_t i_wild_end)
{
	char	**stars;
	char	*tmp_wild_string;

	stars = NULL;
	tmp_wild_string = NULL;
	tmp_wild_string = replace_wild_string(i_wild_start, \
									i_wild_end + 1, wild_string);
	stars = ft_split(tmp_wild_string, '*');
	free(tmp_wild_string);
	return (stars);
}

int	check_suitable(char *object_name, char *wild_string, \
						char **stars, char *tmp_object_name)
{
	size_t	i_wild_start;
	size_t	i_wild_end;
	size_t	i_object_start;
	size_t	i_object_end;

	if(object_name[0] == '.' && wild_string[0] != '.')
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

char	**creat_found_objects(char **found_objects, char *name)
{
	char	**replace_found_objects;
	size_t	count;

	count = 0;
	replace_found_objects = NULL;
	if (found_objects == NULL)
	{
		found_objects = malloc(sizeof(char *) * 2);
		found_objects[0] = ft_strdup(name);
		found_objects[1] = NULL;
		return (found_objects);
	}
	while (found_objects[count])
		count++;
	replace_found_objects = malloc(sizeof(char *) * (count + 2));
	count = 0;
	while (found_objects[count])
	{
		replace_found_objects[count] = ft_strdup(found_objects[count]);
		count++;
	}
	two_dimensional_mas(&found_objects);
	replace_found_objects[count++] = ft_strdup(name);
	replace_found_objects[count] = NULL;
	return (replace_found_objects);
}

char	**wildcards(char *wild_string)
{
	struct dirent	*entry;
	char			**found_objects;
	DIR				*directory;

	directory = opendir(".");
	found_objects = NULL;
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

int main()
{
	char *str = ft_strdup(".*gi****");
	char **ptr = NULL;
	ptr = wildcards(str);
	system("leaks minishell");
	if(ptr != NULL)
		for(int i = 0; ptr[i]; i++)
			printf("%s\n", ptr[i]);
	else
		printf("clear null\n");	
}