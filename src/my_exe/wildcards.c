#include "minishell.h"

int	check_mid(char **stars, size_t i_object, char *object_name)
{
	size_t	count;
	size_t	end;
	char	*addres;

	count = 0;
	while (stars[count])
	{
		if ((object_name = ft_strnstr(object_name, stars[count], i_object)) == NULL)
			return (1);
		count++;
	}
	return (0);
}

char *creat_object_name(size_t end, size_t start, char *object_name)
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

char *replace_wild_string(size_t start, size_t end, char *wild_string)
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
	// free(wild_string);
	return (replace_wild_string);
}

int	check_suitable(char *object_name, char *wild_string, char **stars, char *tmp_object_name)
{
	size_t	i_wild_start;
	size_t	i_wild_end;
	size_t	i_object_start;
	size_t	i_object_end;
	
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
	tmp_object_name = creat_object_name(i_object_end + 1, i_object_start, object_name);
	wild_string = replace_wild_string(i_wild_start, i_wild_end + 1, wild_string);
	stars = ft_split(wild_string, '*');
	if (stars == NULL)
		malloc_error();
	if (check_mid(stars, ft_strlen(tmp_object_name), tmp_object_name))
		return (1);
	return (0);
}

char	**wildcards(char *wild_string)
{
	struct dirent	*entry;
	char 			**found_objects;
	DIR				*directory;

	directory = opendir(".");
	found_objects = NULL;
	entry = readdir(directory);
	while ((entry = readdir(directory)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue ;
		if (!check_suitable(entry->d_name, wild_string, NULL, NULL))
		{
			printf("%s\n", entry->d_name);
			// found_objects = creat_found_objects(found_objects, entry->d_name);
		}
	}
	return (NULL);
}

int main()
{
	char **ptr = wildcards("Make**");
	// for(int i = 0; ptr[i]; i++)
	// 	printf("%s\n", ptr[i]);
}