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
	while (avp[i])
	{
		if (!ft_strncmp("PATH=", avp[i], 5))
			break ;
		else
			++i;
	}
	if (!avp[i])
	{
		new_path = malloc(sizeof(char *) * 2);
		if (!new_path)
			malloc_error();
		new_path[0] = ft_strdup(".");
		if (!new_path[0])
			malloc_error();
		new_path[1] = 0;
		return (new_path);
	}
	path = ft_strdup(avp[i]);
	if (!path)
		malloc_error();
	path[3] = '.';
	path[4] = ':';
	new_path = ft_split(path + 3, ':');
	if (!new_path)
		malloc_error();
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

char	*check_procces(char *pro, char **path, int size, int size_p)
{
	int		i;
	char	*mas;

	i = 0;
	mas = pro;
	while (path[i])
	{
		if (!access(mas, 1))
			return (mas);
		if (*mas != *pro)
			free(mas);
		size_p = ft_strlen(pro);
		size = ft_strlen(path[i]);
		mas = ft_calloc(size + size_p + 2, sizeof(char));
		if (!mas)
			malloc_error();
		ft_strlcat(mas, path[i], size + 1);
		ft_strlcat(mas, "/", size + 2);
		ft_strlcat(mas, pro, size + size_p + 2);
		++i;
	}
	return (mas);
}

void	chreat_process(t_shell *my_shell, int i)
{
	char	**cp_option;
	int		j;
	int		j2;

	j = 0;
	j2 = 0;
	my_shell->full_path = get_path(my_shell->my_envp);
	cp_option = malloc(sizeof(char *) * (size_list(my_shell->control[i]->exe->options) + 2));
	if (!cp_option)
		malloc_error();
	cp_option[j++] = my_shell->control[i]->exe->full_name;
	while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j2])
		cp_option[j++] = my_shell->control[i]->exe->options[j2++];
	cp_option[j] = 0;
	free(my_shell->control[i]->exe->options);
	my_shell->control[i]->exe->options = cp_option;
	my_shell->control[i]->exe->full_name = check_procces(my_shell->control[i]->exe->full_name, my_shell->full_path, 0, 0);
	two_dimensional_mas(&my_shell->full_path);
}
