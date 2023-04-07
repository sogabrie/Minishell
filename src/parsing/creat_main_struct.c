#include "struct.h"
#include "minishell.h"

void	creat_struct_pip(t_shell	*my_shell)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = PIPE;
	pipe(my_shell->control[my_shell->count - 1]->pip);
}

void	creat_struct_and(t_shell	*my_shell)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = LOGIC_AND;
	my_shell->control[my_shell->count - 1]->logic_and = -1;
}

void	creat_struct_or(t_shell	*my_shell)
{
	chreat_cont(my_shell);
	my_shell->control[my_shell->count - 1]->command_type = LOGIC_OR;
	my_shell->control[my_shell->count - 1]->logic_or = -1;
}