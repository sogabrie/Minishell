#include "minishell.h"
#include "struct.h"

void	cp_free(char ***list, char ***cp)
{
	int i;

	i = 0;
	while ((*list) && (*list)[i])
	{
		(*cp)[i] = (*list)[i];
		++i;
	}
	free(*list);
	*list = *cp;
	*cp = 0;

}

char	*my_cat(char *list, int start, int end)
{
	char	*resul;
	int		i;

	i = 0;
	resul = malloc((end - start + 1) * sizeof(char));
	while (start < end)
	{
		resul[i] = list[start];
		++i;
		++start;
	}
	resul[i] = 0;
	return (resul);
}

int	size_list(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list[i])
		++i;
	return (i);
}


// void	control_pars(char ***double_list, char *list)
t_error_type	control_pars(t_shell *my_shell)
{
	char	**cp_list;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	my_shell->double_list = 0;
	while (my_shell->line[i])
	{
		if (my_shell->line[i] == '\'')
		{
			if (j != i)
			{
				cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
				cp_free(&my_shell->double_list, &cp_list);
				my_shell->double_list[n++] = my_cat(my_shell->line, j, i);
				my_shell->double_list[n] = 0;
				j = i;
			}
			++i;
			while (my_shell->line[i] != '\'' && my_shell->line[i] != 0)
				++i;
			if (!my_shell->line[i])
			{
				printf("ERROR");
				exit(5);
			}
			else
			{
				++i;
				cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
				cp_free(&my_shell->double_list, &cp_list);
				my_shell->double_list[n++] = my_cat(my_shell->line, j, i);
				my_shell->double_list[n] = 0;
				j = i;
			}
		}
		else if (my_shell->line[i] == '"')
		{
			if (j != i)
			{
				cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
				cp_free(&my_shell->double_list, &cp_list);
				my_shell->double_list[n++] = my_cat(my_shell->line, j, i);
				my_shell->double_list[n] = 0;
				j = i;
			}
			++i;
			while (my_shell->line[i] != '"' && my_shell->line[i] != 0)
				++i;
			if (!my_shell->line[i])
			{
				printf("ERROR");
				exit(5);
			}
			else
			{
				++i;
				cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
				cp_free(&my_shell->double_list, &cp_list);
				my_shell->double_list[n++] = my_cat(my_shell->line, j, i);
				my_shell->double_list[n] = 0;
				j = i;
			}
		}
		else if ((my_shell->line[i] == '|' &&  my_shell->line[i + 1] == '|') || (my_shell->line[i] == '&' && my_shell->line[i + 1] == '&') || \
		(my_shell->line[i] == '<' && my_shell->line[i + 1] == '<') || (my_shell->line[i] == '>' && my_shell->line[i + 1] == '>'))
		{
			if (j != i)
			{
				cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
				cp_free(&my_shell->double_list, &cp_list);
				my_shell->double_list[n++] = my_cat(my_shell->line, j, i);
				my_shell->double_list[n] = 0;
			}
			cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
			cp_free(&my_shell->double_list, &cp_list);
			my_shell->double_list[n++] = my_cat(my_shell->line, i, i + 2);
			i += 2;
			j = i;
		}
		else if (my_shell->line[i] == '|' || my_shell->line[i] == '<'|| my_shell->line[i] == '>' || my_shell->line[i] == ')' \
		|| my_shell->line[i] == '(' || my_shell->line[i] == ' ')
		{
			if (j != i)
			{
				cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
				cp_free(&my_shell->double_list, &cp_list);
				my_shell->double_list[n++] = my_cat(my_shell->line, j, i);
				my_shell->double_list[n] = 0;
			}
			cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
			cp_free(&my_shell->double_list, &cp_list);
			my_shell->double_list[n++] = my_cat(my_shell->line, i, i + 1);
			my_shell->double_list[n] = 0;
			++i;
			j = i;
		}
		// else if (list[i] == ' ')
		// {
		// 	if (j != i)
		// 	{
		// 		cp_list = malloc((size_list((*double_list)) + 2) * sizeof(char *));
		// 		cp_free(double_list, &cp_list);
		// 		(*double_list)[n++] = my_cat(list, j, i);
		// 		(*double_list)[n] = 0;
		// 	}
		// 	while (list[i] == ' ' || list[i] == 0)
		// 		++i;
		// 	j = i;
		// }
		else if (my_shell->line[i + 1] == 0)
		{
			++i;
			cp_list = malloc((size_list(my_shell->double_list) + 2) * sizeof(char *));
			cp_free(&my_shell->double_list, &cp_list);
			my_shell->double_list[n++] = my_cat(my_shell->line, j, i);
			my_shell->double_list[n] = 0;
		}
		else 
		{
			++i;
		}
	}
	return (NO_ERROR);
}