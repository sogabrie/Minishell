#include "minishell.h"
#include "struct.h"

void	add_pid(t_mas_pid	*my_pid)
{
	pid_t	*pid;
	int		i;

	i = -1;
	pid = malloc(sizeof(pid_t) * my_pid->count);
	if (!pid)
		malloc_error();
	while (++i < my_pid->count)
		pid[i] = my_pid->pid[i];
	free(my_pid->pid);
	my_pid->pid = pid;
	++my_pid->count;
}