#include "minishell.h"
#include "struct.h"

t_error_type	errors_print_sintexs(t_shell *my_shell, \
char *a, t_error_type err)
{
	write (2, "minishell: syntax error near unexpected token `", 48);
	write (2, a, ft_strlen(a));
	write (2, "\'\n", 3);
	my_shell->my_error = SYNT_ERROR;
	return (err);
}
