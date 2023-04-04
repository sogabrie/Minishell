#include "minishell.h"

char	*ft_strnstr_strlen(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	l;
	size_t	f;
	char	*bi;

	bi = (char *)big;
	l = ft_strlen(lit);
	if (bi == lit || l == 0)
		return (bi);
	if (!len)
		return (0);
	i = 0;
	while (bi[i] != 0 && i < len)
	{
		f = 0;
		while (bi[i + f] != 0 && bi[i + f] == lit[f] && \
				lit[f] != 0 && (i + f) < len)
			++f;
		if (f == l)
		{
			// printf("%zu\n", i + ft_strlen(lit));
			return (bi + i + ft_strlen(lit));
		}
		++i;
	}
	return (0);
}


int	free_tmp_stars(char ***stars, char **tmp_object_name, \
						char **tmp_wild_string, int exit)
{
	size_t	i;

	i = 0;
	// if (*tmp_object_name != NULL)
	// {
	// 	free(*tmp_object_name);
	// 	*tmp_object_name = NULL;
	// }
	// if (*tmp_wild_string != NULL)
	// {
	// 	free(*tmp_wild_string);
	// 	*tmp_wild_string = NULL;
	// }
	// if (*stars != NULL)
	// {
	// 	while ((*stars)[i])
	// 	{
	// 		free((*stars)[i]);
	// 		i++;
	// 	}
	// 	free(*stars);
	// 	*stars = NULL;
	// }
	return (exit);
}

int	check_mid(char **stars, size_t i_object, char *object_name)
{
	size_t	count;
	char	*addres;

	count = 0;
	// printf("%s\n", object_name);
	while (stars[count])
	{
		object_name = ft_strnstr_strlen(object_name, stars[count], i_object);
		// printf("object = %s\n", object_name);
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
	free(wild_string);
	wild_string = NULL;
	return (replace_wild_string);
}

int	check_suitable(char *object_name, char *wild_string, \
						char **stars, char *tmp_object_name)
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
	tmp_object_name = creat_object_name(i_object_end + 1, \
									i_object_start, object_name);
	wild_string = replace_wild_string(i_wild_start, \
									i_wild_end + 1, wild_string);
	stars = ft_split(wild_string, '*');
	// for(int i = 0; stars[i]; i++)
	// 	printf("%s\n", stars[i]);
	if (stars == NULL)
		malloc_error();
	if (check_mid(stars, ft_strlen(tmp_object_name), tmp_object_name))
		return (free_tmp_stars(&stars, &tmp_object_name, &wild_string, 1));
	return (free_tmp_stars(&stars, &tmp_object_name, &wild_string, 0));
}

char	**wildcards(char *wild_string)
{
	struct dirent	*entry;
	char			**found_objects;
	DIR				*directory;
	char			*tmp_wild_string;

	directory = opendir(".");
	found_objects = NULL;
	while (1)
	{
		entry = readdir(directory);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.')
			continue ;
		// if (tmp_wild_string != NULL)
			// free(tmp_wild_string);
		tmp_wild_string = ft_strdup(wild_string);
		if(tmp_wild_string == NULL)
			malloc_error();
		if (!check_suitable(entry->d_name, tmp_wild_string, NULL, NULL))
		{
			printf("%s\n", entry->d_name);
			// found_objects = creat_found_objects(found_objects, entry->d_name);
		}
		// system("leaks minishell");
	}
	free(tmp_wild_string);
	closedir(directory);
	return (NULL);
}

int main()
{
	char *str = ft_strdup("file**t.*.txt");
	wildcards(str);
	// system("leaks minishell");
	// for(int i = 0; ptr[i]; i++)
	// 	printf("%s\n", ptr[i]);
}