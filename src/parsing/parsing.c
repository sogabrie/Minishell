#include "minishell.h"
#include "struct.h"

// void	control_exec(t_shell	*my_shell)
// {
// }

void	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
		i = 0;
}

void	main_parsing(t_shell	*my_shell)
{
	t_error_type	error;

	// error = control_pars(&my_shell->double_list, my_shell->line);
		//write(1, "main_1\n", 7);
	//my_shell->line = malloc (100);
	//write(1, "main_2\n", 7);
	//ft_strcpy(my_shell->line,"\"     \'\"     $a\"\'\"");
	//write(1, "main_3\n", 7);
	//printf("%s\n", my_shell->line);
	control_pars(my_shell);
	//write(1, "main_4\n", 7);
	int i = 0;
	while (my_shell->double_list[i])
	{
		//write(1, "main_5\n", 7);
		printf("%s|\n", my_shell->double_list[i]);
		++i;
	}
	// if (error != NO_ERROR)
	// 	quote_error(erroe);
	//control_exec(my_shell);
}