// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

// t_error_type	
void	control_pars(char ** double_list, char *list)
{
	char	**cp_list;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	while (list[i])
	{
		if (list[i] == "'")
		{
			cp_list = malloc(size_list(double_list) + 2);
			cp_free(&double_list, cp_list);
			double_list[n] = my_cat(list, j, i);
			j = i;
			while ()
		}
		if ((list[i] == '|' && list[i + 1] == '|') || (list[i] == '&' && list[i + 1] == '&') || \
		(list[i] == '<' && list[i + 1] == '<') || (list[i] == '>' && list[i + 1] == '>'))
		{
			cp_list = malloc(size_list(double_list) + 2);
			cp_free(&double_list, cp_list);
			double_list[n] = my_cat(list, j, i);
			cp_list = malloc(size_list(double_list) + 2);
			cp_free(&double_list, cp_list);
			double_list[n] = my_cat(list, i, i + 2);
			i += 2;
			j = i;
		}

	}
	// return (NO_ERROR);
}

void	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
		i = 0;
}

int main()
{
	char *a = malloc (10 * sizeof(char *));
	ft_strcpy(a, "asdasdasdasdasd");
	pars_quote(&a);
	return (0);
}