#include "minishell.h"

int	check_mid(char **stars, size_t i_object, char *object_name)
{
	size_t	count;
	char 	*addres;

	count = 0;
	while(stars[count])
	{
		if((object_name = ft_strnstr(object_name, stars[count], i_object)) == NULL)
			return (1);
		count++;
	}
	return (0);
}

int	check_suitable(char *object_name, char *wild_string)
{
	size_t	i_wild;
	size_t	i_object;
	char	**stars;
	
	i_object = ft_strlen(object_name) - 1;
	i_wild = ft_strlen(wild_string) - 1;
	while(wild_string[i_wild] != '*')
		if(wild_string[i_wild--] != object_name[i_object--])
			return (1);
	i_wild = 0;
	i_object = 0;
	while(wild_string[i_wild] != '*')
		if(wild_string[i_wild++] != object_name[i_object++])
			return (1);
	stars = ft_split(wild_string + i_wild, '*');
	if(check_mid(stars, ft_strlen(object_name), object_name))
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
		if (!check_suitable(entry->d_name, wild_string))
		{
			printf("%s ", entry->d_name);
		}
	}
	printf("\n");
	return NULL;
}

// int main()
// {
// 	char **ptr = wildcards("*li**");
// 	// for(int i = 0; ptr[i]; i++)
// 	// 	printf("%s\n", ptr[i]);
// }