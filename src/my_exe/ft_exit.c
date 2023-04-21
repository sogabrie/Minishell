// #include "minishell.h"

// int	overflow_or_not(char *str)
// {
// 	int					minus;
// 	int					i;
// 	unsigned long long	oper;

// 	oper = 0;
// 	i = 0;
// 	minus = 1;
// 	if (str[i] == '-')
// 	{
// 		minus = -1;
// 		i++;
// 	}
// 	else if (str[i] == '+')
// 		i++;
// 	while (str[i] != '\0')
// 	{
// 		oper = oper * 10 + str[i] - '0';
// 		i++;
// 	}
// 	if (minus == -1 && oper > LONG_MIN * -1)
// 		return (1);
// 	if (oper > LONG_MAX)
// 		return (1);
// 	return (0);	
// }

// int ft_exit(char **args)
// {
// 	size_t			count;
// 	unsigned char	exit_code;

// 	count = 0;
// 	if (overflow_or_not(args[0]))
// 	{
// 		exe_error(args[0], 276, " exit: ");
// 		exit(1);
// 	}
// 	exit_code = (unsigned char)(ft_atoi(args[0]));
// 	printf("%d\n", exit_code);
// 	// while (args[count])
// 	// 	count++;
// 	// if(count != 1)
// 	// {
// 	// 	write(2, "minishell: exit: too many arguments\n", 36);
// 	// 	return (1);
// 	// }


// }

// int main()
// {	
// 	size_t count = 0;
// 	char **str = ft_split("-9223372036854775808", ' ');
// 	int code = ft_exit(str);
// 	printf("code = %d\n", code);
// 	return (0);
// }

// //<20