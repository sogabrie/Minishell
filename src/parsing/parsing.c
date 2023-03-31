#include "minishell.h"

// void	control_pars(char **double_list, char **envp)
// {
// 	t_control		*control;
// }

void	main_parsing(char *line, char **envp)
{
	char			**double_list;
	t_error_type	error;

	double_list = ft_split(line);
	// error = pars_quote(&double_list);
	// if (error != NO_ERROR)
	// 	quote_error(erroe);
	//control_pars(double_list, envp);
}