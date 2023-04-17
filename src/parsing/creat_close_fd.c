#include "struct.h"
#include "minishell.h"

void	creat_mas_int(t_shell *my_shell, int fd)
{
	my_shell->close_fd = malloc (sizeof(int) * 1);
	if (!my_shell->close_fd)
		malloc_error();
	my_shell->close_fd[0] = fd;
	++my_shell->close_fd_count;
}

void	creat_close_fd(t_shell *my_shell, int fd)
{
	int	*a;
	int	i;

	i = -1;
	if (!my_shell->close_fd_count)
	{
		creat_mas_int(my_shell, fd);
		return ;
	}
	a = malloc (sizeof(int) * (my_shell->close_fd_count + 1));
	if (!a)
		malloc_error();
	while (++i < my_shell->close_fd_count)
		a[i] = my_shell->close_fd[i];
	a[i] = fd;
	++my_shell->close_fd_count;
	free(my_shell->close_fd);
	my_shell->close_fd = a;
}
