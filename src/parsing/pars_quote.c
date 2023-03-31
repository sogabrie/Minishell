// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

// t_error_type	
void	pars_quote(char ***double_list)
{
	int i = 0;
	while ((*double_list)[i])
		printf("%s\n",(*double_list)[i++]);
		
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
	char **a = malloc (10 * sizeof(char *));
	int i = 0;
	while (i < 9)
		a[i++] = malloc(50);
	a[i] = 0;
	ft_strcpy(a[0], "asdasdasdasdasd");
	ft_strcpy(a[1], "asdasdasdasdasd");
	ft_strcpy(a[2], "asdasdasdasdasd");
	ft_strcpy(a[3], "asdasdasdasdasd");
	ft_strcpy(a[4], "asdasdasdasdasd");
	ft_strcpy(a[5], "asdasdasdasdasd");
	ft_strcpy(a[6], "asdasdasdasdasd");
	ft_strcpy(a[7], "asdasdasdasdasd");
	ft_strcpy(a[8], "asdasdasdasdasd");
	pars_quote(&a);
	return (0);
}