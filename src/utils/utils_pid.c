#include "minishell.h"
#include "struct.h"

void	add_pid(t_mas_pid	*my_pid)
{
	pid_t	*pid;
	int		*int_pid;
	int		i;

	i = -1;
	pid = malloc(sizeof(pid_t) * my_pid->count);
	int_pid = malloc(sizeof(int) * my_pid->count);
	if (!pid || !int_pid)
		malloc_error();
	while (++i < my_pid->count)
	{
		pid[i] = my_pid->pid[i];
		int_pid[i] = my_pid->my_pid[i];
	}
	free(my_pid->pid);
	free(my_pid->my_pid);
	my_pid->pid = pid;
	my_pid->my_pid = int_pid;
	++my_pid->count;
	my_pid->my_pid[my_pid->count - 1] = -1;
}