/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:03:35 by sogabrie          #+#    #+#             */
/*   Updated: 2023/04/26 20:03:36 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**creat_more_objects(char **found_objects, char *name)
{
	char	**replace_found_objects;
	size_t	count;

	count = 0;
	replace_found_objects = NULL;
	while (found_objects[count])
		count++;
	replace_found_objects = malloc(sizeof(char *) * (count + 2));
	if (replace_found_objects == NULL)
		malloc_error();
	count = 0;
	while (found_objects[count])
	{
		replace_found_objects[count] = ft_strdup(found_objects[count]);
		if (replace_found_objects[count] == NULL)
			malloc_error();
		count++;
	}
	two_dimensional_mas(&found_objects);
	replace_found_objects[count] = ft_strdup(name);
	if (replace_found_objects[count++] == NULL)
		malloc_error();
	replace_found_objects[count] = NULL;
	return (replace_found_objects);
}

char	**creat_found_objects(char **found_objects, char *name)
{
	if (found_objects == NULL)
	{
		found_objects = malloc(sizeof(char *) * 2);
		if (found_objects == NULL)
			malloc_error();
		found_objects[0] = ft_strdup(name);
		if (found_objects[0] == NULL)
			malloc_error();
		found_objects[1] = NULL;
		return (found_objects);
	}
	return (creat_more_objects(found_objects, name));
}
