#include "minishell.h"

int		check_suitable(char *name, char *wild_string)
{
	int	i;
	int	j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	if(i == 0 && wild_string[i] != '*')
	{
		while(wild_string[i] != '*')
			if(name[j++] != wild_string[i++])
				return (1);
		if(name[j] == '\0' && wild_string[i + 1] != '\0')
			return (1);
		if(name[j] != '\0' && wild_string[i + 1] == '\0')
			return (0);
	}
	while(wild_string[i] != '\0')
	{
		while(wild_string[i] == '*' && wild_string[i] != '\0')
			i++;
		if(name[j] != '\0' && wild_string[i] == '\0')
			break;
		while(name[j] != '\0')
		{
			if(wild_string[i] == name[j])
				break;
			j++;
		}
		if(name[j] == '\0' && wild_string[i] != '\0')
			return (1);
		i++;
	}
	while(wild_string[i] != '*')
		if(name[len--] != wild_string[i--])
			return (1);
	return 0;
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
			printf("%s\n", entry->d_name);
	}
	return NULL;
}

int main()
{
	char **ptr = wildcards("****hell*");
	// for(int i = 0; ptr[i]; i++)
	// 	printf("%s\n", ptr[i]);
}