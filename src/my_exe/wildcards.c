#include "minishell.h"

int	check_suitable(char *object_name, char *wild_string)
{
	size_t	i;
	size_t	j;
	size_t	flag_exit;

	i = 0;
	j = 0;
	while(wild_string[i] != '*')
		if(object_name[j++] != wild_string[i++])
			return (1);
	while(wild_string[i] != '\0')
	{
		while(wild_string[i] == '*' && wild_string[i] != '\0')
			i++;
		if(wild_string[i] == '\0' && flag_exit != 0)
			break;
		if((object_name[j] == '\0' && wild_string[i] != '\0') || flag_exit == 0)
			return (1);
		flag_exit = 0;
		while(object_name[j] != '\0')
		{
			if(object_name[j] == wild_string[i])
			{
				flag_exit = 1;
				break;
			}
			j++;
		}
		i++;
	}
	i = ft_strlen(wild_string) - 1;
	j = ft_strlen(object_name) - 1;
	while(wild_string[i] != '*')
		if(wild_string[i--] != object_name[j--])
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
			printf("%s ", entry->d_name);
	}
	printf("\n");
	return NULL;
}

// int main()
// {
// 	char **ptr = wildcards("f*el*");
// 	// for(int i = 0; ptr[i]; i++)
// 	// 	printf("%s\n", ptr[i]);
// }