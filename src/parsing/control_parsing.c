#include "struct.h"
#include "minishell.h"

int	control_pars_exe(t_shell *my_shell, int start, int end)
{
	int	i;

	write(1, "aa_11\n",6);
	while (!ft_strcmp(my_shell->double_list[start], " ") || \
	!ft_strcmp(my_shell->double_list[start], "("))
	{
		write(1, "aa_12\n",6);
		if (!ft_strcmp(my_shell->double_list[start], "("))
		{
			// write(1, "aa_13\n",6);
			if (creat_struct_prioritet_start(my_shell))
				return (9);
		}
		write(1, "aa_14\n",6);
		++start;
	}
	write(1, "aa_15\n",6);
	i = start;
	while (i < end && my_shell->double_list[i]  && ft_strcmp(my_shell->double_list[i], ")"))
	{
		write(1, "aa_16\n",6);
		if ((!ft_strcmp(my_shell->double_list[i], "echo") || \
		!ft_strcmp(my_shell->double_list[i], "cd") || \
		!ft_strcmp(my_shell->double_list[i], "pwd") || \
		!ft_strcmp(my_shell->double_list[i], "export") || \
		!ft_strcmp(my_shell->double_list[i], "unset") || \
		!ft_strcmp(my_shell->double_list[i], "env") || \
		!ft_strcmp(my_shell->double_list[i], "exit")) \
		&& my_shell->check_exe == -1)
		{
			write(1, "aa_17\n",6);
			if (creat_my_exe(my_shell, my_shell->double_list[i++]))
				return (7);
			write(1, "aa_18\n",6);
		}
		else if (!ft_strcmp(my_shell->double_list[i], "<") || \
		!ft_strcmp(my_shell->double_list[i], "<<") || \
		!ft_strcmp(my_shell->double_list[i], ">") || \
		!ft_strcmp(my_shell->double_list[i], ">>"))
		{
			write(1, "aa_19\n",6);
			creat_redirect(my_shell, &i);
			// if (creat_redirect(my_shell, &i))
				// return (8);
			printf("my_shell->double_list[i] = %s\n",my_shell->double_list[i]);
			write(1, "aa_20\n",6);
		}
		else if (i == start || my_shell->check_exe == -1)
		{
			write(1, "aa_21\n",6);
			if (creat_exe(my_shell, my_shell->double_list[i++]))
				return (7);
			write(1, "aa_22\n",6);
		}
		else if (ft_strcmp(my_shell->double_list[i], " "))
		{
			write(1, "aa_23\n",6);
			add_option(my_shell, my_shell->double_list[i++]);
			write(1, "aa_24\n",6);
		}
		else
			++i;
		write(1, "aa_25\n",6);
		printf("i = %d end = %d\n", i, end);
		printf("my_shell->double_list[i] = %s\n",my_shell->double_list[i]);
	}
	printf("i = %d end = %d\n", i, end);
	write(1, "aa_25.5\n",8);
	while (i < end && my_shell->double_list[i] && (!ft_strcmp(my_shell->double_list[i], " ") || \
	!ft_strcmp(my_shell->double_list[i], ")")))
	{
		write(1, "aa_26\n",6);
		if (!ft_strcmp(my_shell->double_list[i], ")"))
		{
			write(1, "aa_27\n",6);
			if (creat_struct_prioritet_end(my_shell))
				return (9);
		}
		++i;
		write(1, "aa_28\n",6);
	}
	write(1, "aa_29\n",6);
	my_shell->check_exe = -1;
	return (0);
}

int	control_parsing(t_shell	*my_shell)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i <= my_shell->delimiter_count)
	{
		write(1, "aa_2\n",5);
		start = end;
		if (i < my_shell->delimiter_count)
		{
			write(1, "aa_3\n",5);
			end = my_shell->delimiter[i];
		}
		else
		{
			write(1, "aa_4\n",5);
			while(my_shell->double_list[end])
				++end;
			++end;
		}
		write(1, "aa_5\n",5);
		control_pars_exe(my_shell, start, end);
		write(1, "aa_6\n",5);
		if (i < my_shell->delimiter_count && \
		(start || my_shell->double_list[end]))
		{
			write(1, "aaaaaaaaaaaaaaaaaa_7\n",20);
			if (!ft_strcmp(my_shell->double_list[end], "|"))
				creat_struct_pip(my_shell);
			else if (!ft_strcmp(my_shell->double_list[end], "||"))
				creat_struct_or(my_shell);
			else if (!ft_strcmp(my_shell->double_list[end], "&&"))
				creat_struct_and(my_shell);
			write(1, "aa_7\n",6);
		}
		++i;
		++end;
		write(1, "aa_10\n",6);
	}
	return (0);
}
