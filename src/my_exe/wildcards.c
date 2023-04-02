#include "minishell.h"

int	check_suitable(char *object_name, char *wild_string)
{
	// size_t	i;
	// size_t	j;
	// size_t	wild_flag;

	// i = 0;
	// j = 0;
	// wild_flag = 0;
	// while(wild_string[i] != '*' && wild_string[i] != '\0')
	// {
	// 	if(object_name[j] != wild_string[i])
	// 		return (1);
	// 	i++;
	// 	j++;
	// }
	// while(wild_string[i] != '\0')
	// {
	// 	if(wild_string[i] == '*')
	// 		i++;
	// 	else
	// 	{
	// 		wild_flag = 1;
	// 		while(object_name[j] != '\0' && wild_string[i] != '\0')
	// 		{
	// 			if(wild_string[i] == '*')
	// 				break;
	// 			if(object_name[j] == wild_string[i])
	// 				i++;
	// 			j++;
	// 		}
	// 		while(wild_string[i] == '*')
	// 			i++;
	// 		if(object_name[j] == '\0' && wild_string[i] != '\0')
	// 			return (1);
	// 	}
	// }
	// if(object_name[j] != '\0' && wild_string[i] == '\0' && wild_flag == 1)
	// 	return (1);
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

int main()
{
	char **ptr = wildcards("***file*");
	// for(int i = 0; ptr[i]; i++)
	// 	printf("%s\n", ptr[i]);
}