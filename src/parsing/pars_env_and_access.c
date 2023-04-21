#include "struct.h"
#include "minishell.h"

// int	free_mas(char **mas)
// {
// 	free(*mas);
// 	*mas = 0;
// 	return (0);
// }

char	**get_path(char **avp)
{
	char	**new_path;
	char	*path;
	int		i;

	i = 0;
	// write(2,"lllll_1\n", 9);
	while (avp[i])
	{
		if (!ft_strncmp("PATH=", avp[i], 5))
			break ;
		else
			++i;
	}
	// write(2,"lllll_1\n", 9);
	if (!avp[i])
	{
		// write(2,"lllll_2\n", 9);
		new_path = malloc(sizeof(char *) * 2);
		if (!new_path)
			malloc_error();
		new_path[0] = ft_strdup(".");
		if (!new_path[0])
			malloc_error();
		new_path[1] = 0;
		return (new_path);
		// write(2,"lllll_3\n", 9);
	}
	path = ft_strdup(avp[i]);
	// write(2,"lllll_4\n", 9);
	if (!path)
		malloc_error();
	path[3] = '.';
	path[4] = ':';
	// printf("path = %s\n", path + 3);
	// write(2,"lllll_5\n", 9);
	new_path = ft_split(path + 3, ':');
	// write(2,"lllll_6\n", 9);
	if (!new_path)
		malloc_error();
	// write(2,"lllll_7\n", 9);
	free(path);
	return (new_path);
}

// long	check_valid_procces(char *mas, int i)
// {
// 	if (!access(mas, 1))
// 	{
// 		return (0);
// 	}
// 	return (1);
// }

char	*check_procces(t_shell *my_shell, int si, int size, int size_p)
{
	int		i;
	char	*mas;

	i = 0;
	mas = my_shell->control[si]->exe->full_name;
	while (my_shell->full_path[i])
	{
		if (!access(mas, 1))
			return (mas);
		if (*mas != *(my_shell->control[si]->exe->full_name))
			free(mas);
		size_p = ft_strlen(my_shell->control[si]->exe->full_name);
		size = ft_strlen(my_shell->full_path[i]);
		mas = ft_calloc(size + size_p + 2, sizeof(char));
		if (!mas)
			malloc_error();
		ft_strlcat(mas, my_shell->full_path[i], size + 1);
		ft_strlcat(mas, "/", size + 2);
		ft_strlcat(mas, my_shell->control[si]->exe->full_name, size + size_p + 2);
		++i;
	}
	if (access(mas, 1))
		my_shell->control[si]->exe->error = 127;
	return (mas);
}

int	chreat_process(t_shell *my_shell, int i)
{
	char	**cp_option;
	int		j;
	int		j2;

	j = 0;
	j2 = 0;
	// write(2,"zzzzz_1\n", 9);
	my_shell->full_path = get_path(my_shell->my_envp);
	// write(2,"zzzzz_2\n", 9);
	cp_option = malloc(sizeof(char *) * (size_list(my_shell->control[i]->exe->options) + 2));
	// write(2,"zzzzz_3\n", 9);
	if (!cp_option)
		malloc_error();
	// write(2,"zzzzz_4\n", 9);
	cp_option[j++] = my_shell->control[i]->exe->full_name;
	// write(2,"zzzzz_5\n", 9);
	while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j2])
		cp_option[j++] = my_shell->control[i]->exe->options[j2++];
	// write(2,"zzzzz_6\n", 9);
	cp_option[j] = 0;
	free(my_shell->control[i]->exe->options);
	// write(2,"zzzzz_7\n", 9);
	my_shell->control[i]->exe->options = cp_option;
	// write(2,"zzzzz_8\n", 9);
	my_shell->control[i]->exe->full_name = check_procces(my_shell, i, 0, 0);
	// write(2,"zzzzz_9\n", 9);
	two_dimensional_mas(&my_shell->full_path);
	// write(2,"zzzz_10\n", 9);
	return (my_shell->control[i]->exe->error);
}
