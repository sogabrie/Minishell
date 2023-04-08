#include "struct.h"
#include "minishell.h"

int	creat_struct_pip(t_shell	*my_shell)
{
	if (chreat_cont(my_shell))
		return (7);
	my_shell->control[my_shell->count - 1]->command_type = PIPE;
	pipe(my_shell->control[my_shell->count - 1]->pip);
	return (0);
}

int	creat_struct_and(t_shell	*my_shell)
{
	if (chreat_cont(my_shell))
		return (7);
	my_shell->control[my_shell->count - 1]->command_type = LOGIC_AND;
	my_shell->control[my_shell->count - 1]->logic_and = -1;
	return (0);
}

int	creat_struct_or(t_shell	*my_shell)
{
	if (chreat_cont(my_shell))
		return (7);
	my_shell->control[my_shell->count - 1]->command_type = LOGIC_OR;
	my_shell->control[my_shell->count - 1]->logic_or = -1;
	return (6);
}

int	creat_struct_prioritet_start(t_shell	*my_shell)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = PRIORITET_START;
	my_shell->control[my_shell->count - 1]->prioritet_start = malloc(sizeof(t_priorities));
	if (!my_shell->control[my_shell->count - 1]->prioritet_start)
		return (8);
	my_shell->control[my_shell->count - 1]->prioritet_start->start = my_shell->count - 1;
	my_shell->control[my_shell->count - 1]->prioritet_start->end = -1;
	my_shell->control[my_shell->count - 1]->prioritet_start->status = 0;
	return (0);
}