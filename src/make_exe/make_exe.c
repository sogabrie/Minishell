#include "minishell.h"
#include "struct.h"

void	sigint_pars_exe(int sig)
{
	// signal(SIGINT, SIG_IGN);
	write(1, "\n", 1);
	// signal(SIGINT, SIG_IGN);
	(void)sig;
}

void	sigquit_pars_exe(int sig)
{
	write(1, "Quit: 3\n", 9);
	(void)sig;
}

int	control_type_exe(t_shell *my_shell, int i)
{
	if ((!ft_strcmp(my_shell->control[i]->exe->full_name, "echo") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "cd") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "pwd") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "export") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "unset") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "env") || \
	!ft_strcmp(my_shell->control[i]->exe->full_name, "exit")))
		return (1);
	return (0);
}


int	chek_and_or(t_shell *my_shell, t_mas_pid *my_pid, int *i, int j)
{
	int	i2;
	int	error;

	i2 = 0;
	if ((*i) > 0 && (my_shell->control[(*i) - 1]->command_type == LOGIC_AND || my_shell->control[(*i) - 1]->command_type == LOGIC_OR))
	{
		// printf("end_2 = %d\n", my_shell->my_error);
		while (i2 < my_pid->count)
		{
			if (my_pid->my_pid[i2] == -1)
			{
				waitpid(my_pid->pid[i2], &error, 0);
				my_shell->error_status = error;
			}
			else
				my_shell->error_status = my_pid->my_pid[i2];
			++i2;
		}
		free(my_pid->pid);
		free(my_pid->my_pid);
		my_pid->count = 0;
		my_pid->pid = 0;
		my_pid->my_pid = 0;
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_AND)
		{
			if (my_shell->error_status)
			{
				(*i) = j;
				// my_shell->my_error = NO_ERROR;
				return (1);
			}
		}
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_OR)
		{
			if (!my_shell->error_status)
			{
				(*i) = j;
				// my_shell->my_error = NO_ERROR;
				return (1);
			}
		}
	}
	return (0);
}

int	do_my_exe(t_shell *my_shell, int i)
{
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "echo"))
	{
		return(ft_echo(my_shell->control[i]->exe->options, my_shell->my_envp, my_shell->error_status));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "cd"))
	{
		if (my_shell->control[i]->exe->options)
			return (ft_cd(my_shell->control[i]->exe->options[0], &my_shell->my_envp, NULL, NULL));
		return (ft_cd(NULL, &my_shell->my_envp, NULL, NULL));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "pwd"))
	{
		return(ft_pwd());
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "export"))
	{
		return(ft_export(my_shell->control[i]->exe->options, &my_shell->my_envp, -1, NULL));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "unset"))
	{
		ft_unset(my_shell->control[i]->exe->options, &my_shell->my_envp);
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "env"))
	{
		return(ft_env(my_shell->my_envp, 0));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "exit"))
	{
		ft_exit(my_shell->control[i]->exe->options, 0);
	}
	return (0);
}

void	do_exe(t_shell *my_shell, t_mas_pid	*my_pid, int i)
{
	int		error;
	char	*new_name;
	char	**new_dubl;
	char	**cp_dubl;
	int		j;
	int		j2;
	int		j3;
	int		mas_count;

	// write(2,"ttttt_1\n", 9);
	my_shell->control[i]->exe->cpy_fd_input = dup(my_shell->fd_input);
	dup2(my_shell->control[i]->exe->fd_input, my_shell->fd_input);
	my_shell->control[i]->exe->cpy_fd_output = dup(my_shell->fd_output);
	dup2(my_shell->control[i]->exe->fd_output, my_shell->fd_output);
	// write(2,"ttttt_2\n", 9);

	// printf("my_shell->control[i]->exe->full_name = %s\n", my_shell->control[i]->exe->full_name);
	new_name = parse_line(my_shell->control[i]->exe->full_name, my_shell->my_envp, my_shell->my_error, 0);
	if (new_name)
	{
		free(my_shell->control[i]->exe->full_name);
		my_shell->control[i]->exe->full_name = new_name;
	}
	
	// printf("my_shell->control[i]->exe->full_name = %s\n", my_shell->control[i]->exe->full_name);
	if (ft_strcmp(my_shell->control[i]->exe->full_name, "echo"))
	{
		j = 0;
		// write(1, "exexex_1\n",10);
		// printf("my_shell->control[i]->exe->options ==== %p\n", my_shell->control[i]->exe->options);
		while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j])
		{
			new_name = parse_line(my_shell->control[i]->exe->options[j], my_shell->my_envp, my_shell->my_error, 0);
			if (new_name)
			{
				free(my_shell->control[i]->exe->options[j]);
				my_shell->control[i]->exe->options[j] = new_name;
			}
			++j;
		}
		j = 0;
		while (my_shell->control[i]->exe->options && my_shell->control[i]->exe->options[j])
		{
			j2 = -1;
			j3 = 0;
			cp_dubl =  wildcards(ft_strdup(my_shell->control[i]->exe->options[j]));
			if (cp_dubl)
			{
				mas_count = size_list(my_shell->control[i]->exe->options) + size_list(cp_dubl);
				new_dubl = malloc(mas_count * sizeof(char *));
				while (++j2 < j)
					new_dubl[j2] = my_shell->control[i]->exe->options[j2];
				j3 = 0;
				while (cp_dubl[j3])
					new_dubl[j2++] = cp_dubl[j3++];
				free(my_shell->control[i]->exe->options[j]);
				j3 = j;
				j = j2 - 1;
				while (j2 < mas_count - 1)
					new_dubl[j2++] = my_shell->control[i]->exe->options[++j3];
				new_dubl[j2] = 0;
				free(my_shell->control[i]->exe->options);
				my_shell->control[i]->exe->options = new_dubl;
			}
			++j;
		}
	}
	if (!control_type_exe(my_shell, i))
	{
		// write(2,"ttttt_3\n", 9);
		// printf("my_shell->control[i]->exe->full_nam1 = %s\n", my_shell->control[i]->exe->full_name);
		if (chreat_process(my_shell, i))
		{
			// write(2,"ttttt_4\n", 9);
			write (2, "minishell: ", 12);
			write (2, my_shell->control[i]->exe->options[0], ft_strlen(my_shell->control[i]->exe->options[0]));
			write (2, ": command not found\n", 21);
			my_shell->error_status = 127;
		}
		// printf("my_shell->control[i]->exe->full_nam2 = %s\n", my_shell->control[i]->exe->full_name);
		// write(2,"ttttt_5\n", 9);
		add_pid(my_pid);
		my_pid->pid[my_pid->count - 1] = fork();
		if (my_pid->pid[my_pid->count - 1])
		{
			// write(2,"ttttt_6\n", 9);
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
				close(my_shell->control[i + 1]->pip[1]);
			}
			// signal(SIGINT, SIG_IGN);
			// signal(SIGQUIT, SIG_IGN);
			// waitpid(pid, &error, 0);
			// my_shell->my_error = error;
		}
		else
		{
			// write(2,"ttttt_7\n", 9);
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				close(my_shell->control[i - 1]->pip[0]);
			}
			// signal(SIGINT, sigint_pars_exe);
			// signal(SIGQUIT, sigquit_pars_exe);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (my_shell->control[i]->error == NO_ERROR)
				exit(execve(my_shell->control[i]->exe->full_name, my_shell->control[i]->exe->options, my_shell->my_envp));
			exit(my_shell->control[i]->error);
		}
		// write(2,"ttttt_8\n", 9);
	}
	else //if (my_shell->control[i]->command_type == MY_EXE)
	{
		// write(2,"ttttt_9\n", 9);
		if ((i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE) || \
		(i > 0 && my_shell->control[i - 1]->command_type == PIPE))
		{		
			add_pid(my_pid);
			my_pid->pid[my_pid->count - 1] = fork();
			if (my_pid->pid[my_pid->count - 1])
			{
				if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
				{
					close(my_shell->control[i + 1]->pip[1]);
				}
			}
			else
			{
				if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
				{
					close(my_shell->control[i - 1]->pip[0]);
				}
				if (my_shell->control[i]->error == NO_ERROR)
					exit(do_my_exe(my_shell, i));
				exit(my_shell->control[i]->error);
			}
		}
		else
		{
			add_pid(my_pid);
			my_pid->my_pid[my_pid->count - 1] = do_my_exe(my_shell, i);
		}
		// write(2,"tttt_10\n", 9);
	}
	// write(2,"tttt_11\n", 9);
}

int	make_exe(t_shell *my_shell, int i, int j)
{
	t_mas_pid	my_pid;
	int			error;
	int			i2;
	int			re_co;
	int			fd;
	char		*a;

	error = 0;
	my_pid.count = 0;
	my_pid.pid = 0;
	my_pid.my_pid = 0;


	while (i < j)
	{
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
		// signal(SIGINT, sigint_pars_exe);
		// signal(SIGQUIT, sigquit_pars_exe);
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{

			// printf("i  === %d prioritet_start->end = %d\n", i, my_shell->control[i]->prioritet_start->end);
			// write(2, "fffffff_1\n",11);
			if (chek_and_or(my_shell, &my_pid, &i, my_shell->control[i]->prioritet_start->end + 1))
				continue ;
			// signal(SIGINT, SIG_IGN);
			// signal(SIGQUIT, SIG_IGN);
			// write(2, "fffffff_2\n",11);
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				// write(2, "fffffff_3\n",11);
				my_shell->cpy_fd_input = dup(my_shell->fd_input);
				dup2(my_shell->control[i - 1]->pip[0], my_shell->fd_input);
			}
			if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
			my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
			{
				// write(2, "fffffff_4\n",11);
				my_shell->cpy_fd_output = dup(my_shell->fd_output);
				dup2(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1], my_shell->fd_output);
			}
			add_pid(&my_pid);
			my_pid.pid[my_pid.count - 1] = fork();
			if (my_pid.pid[my_pid.count - 1])
			{
				// write(2, "fffffff_5\n",11);
				i2 = i;
				while (i2 < my_shell->control[i]->prioritet_start->end)
				{
					// write(2, "fffffff_6\n",11);
					if (my_shell->control[i2]->command_type == PIPE)
					{
						// write(2, "fffffff_7\n",11);
						close(my_shell->control[i2]->pip[0]);
						close(my_shell->control[i2]->pip[1]);
					}
					++i2;
				}
				if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
				my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
				{
					// write(2, "fffffff_8\n",11);
					close(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1]);
				}
				if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
				{
					// write(2, "fffffff_9\n",11);
					dup2(my_shell->cpy_fd_input, my_shell->fd_input);
					close(my_shell->cpy_fd_input);
				}
				if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
				my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
				{
					// write(2, "ffffff_10\n",11);
					dup2(my_shell->cpy_fd_output, my_shell->fd_output);
					close(my_shell->cpy_fd_output);
				}
				// write(2, "ffffff_11\n",11);
				// printf("i  === %d  my_shell->control[i]->prioritet_start->end = %d\n", i, my_shell->control[i]->prioritet_start->end);
				i = my_shell->control[i]->prioritet_start->end;
				// printf("i  2=== %d\n", i);

			}
			else
			{
				// write(2, "ffffff_12\n",11);
				if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
				{
					close(my_shell->control[i - 1]->pip[0]);
				}
				// write(2, "ffffff_13\n",11);
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
				exit(make_exe(my_shell, i + 1, my_shell->control[i]->prioritet_start->end + 1));
				// write(2, "ffffff_14\n",11);
			}
			// signal(SIGINT, sigint_pars_exe);
			// signal(SIGQUIT, sigquit_pars_exe);
		 }
		 else if (my_shell->control[i]->command_type == EXE)
		 {
			// signal(SIGINT, sigint_pars_exe);
			// signal(SIGQUIT, sigquit_pars_exe);
			// write(1,"ttttttttt_1\n", 13);
			re_co = 0;
			while (re_co < my_shell->control[i]->count_redir && my_shell->control[i]->exe->error == NO_ERROR)
			{
				// signal(SIGINT, sigint_pars_exe);
				// signal(SIGQUIT, sigquit_pars_exe);
				a = 0;
				printf("my_shell->control[i]->count_redir = %d\n", my_shell->control[i]->count_redir);
				if (my_shell->control[i]->redirect[re_co]->error == NO_ERROR)
				{
					printf("my_shell->control[i]->redirect[re_co]->filename = %s\n", my_shell->control[i]->redirect[re_co]->filename);
					a = parse_line(my_shell->control[i]->redirect[re_co]->filename, my_shell->my_envp, my_shell->my_error, 0);
					if (!a)
						a = ft_strdup(my_shell->control[i]->redirect[re_co]->filename);
				}
				if (my_shell->control[i]->redirect[re_co]->type == INPUT && my_shell->control[i]->redirect[re_co]->error == NO_ERROR)
				{
					fd = red_input(a);
					if (fd >= 0)
					{
						my_shell->control[i]->exe->flag_input = 0;
						my_shell->control[i]->exe->fd_input = fd;
					}
					else
						my_shell->control[i]->exe->error = 127;
				}
				else if (my_shell->control[i]->redirect[re_co]->type == OUTPT && my_shell->control[i]->redirect[re_co]->error == NO_ERROR)
				{
					fd = red_out(a);
					if (fd >= 0)
					{
						my_shell->control[i]->exe->flag_output = 0;
						my_shell->control[i]->exe->fd_output = fd;
					}
					else
						my_shell->control[i]->exe->error = 127;
				}
				else if (my_shell->control[i]->redirect[re_co]->type == HERE_DOC && my_shell->control[i]->redirect[re_co]->error == NO_ERROR)
				{
					// write(1,"ttttttttt_2\n", 13);
					fd = red_input(a);
					printf("a = %s\n", a);
					if (fd >= 0)
					{
						// write(1,"ttttttttt_3\n", 13);
						my_shell->control[i]->exe->flag_input = 0;
						my_shell->control[i]->exe->fd_input = fd;
					}
					else
						my_shell->control[i]->exe->error = 127;
				}
				else if (my_shell->control[i]->redirect[re_co]->type == OUTPUT_APP && my_shell->control[i]->redirect[re_co]->error == NO_ERROR)
				{
					fd = red_out(a);
					if (fd >= 0)
					{
						my_shell->control[i]->exe->flag_output = 0;
						my_shell->control[i]->exe->fd_output = fd;
					}
					else
						my_shell->control[i]->exe->error = 127;
				}
				else if (my_shell->control[i]->redirect[re_co]->error != NO_ERROR)
				{
					my_shell->control[i]->exe->error = my_shell->control[i]->redirect[re_co]->error;
				}
				free(a);
				// write(2, "exe_pp_1\n",10);
				creat_close_fd(my_shell, fd);
				++re_co;
			}
			if (chek_and_or(my_shell, &my_pid, &i, i + 1))
				continue ;
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
					if (my_shell->control[i]->exe->flag_input)
						my_shell->control[i]->exe->fd_input = my_shell->control[i - 1]->pip[0];
			}
			if (i + 1 < my_shell->count && my_shell->control[i + 1]->command_type == PIPE)
			{
					if (my_shell->control[i]->exe->flag_output)
						my_shell->control[i]->exe->fd_output = my_shell->control[i + 1]->pip[1];
			}
			// write(2, "exe_pp_2\n",10);
			if (my_shell->control[i]->exe->error == NO_ERROR)
			{
				// write(2, "exe_pp_3\n",10);
				// signal(SIGINT, sigint_pars_exe);
				// signal(SIGQUIT, sigquit_pars_exe);
				do_exe(my_shell, &my_pid, i);
				// write(2, "exe_pp_4\n",10);
				dup2(my_shell->control[i]->exe->cpy_fd_input, my_shell->fd_input);
				close(my_shell->control[i]->exe->cpy_fd_input);
				dup2(my_shell->control[i]->exe->cpy_fd_output, my_shell->fd_output);
				close(my_shell->control[i]->exe->cpy_fd_output);
				// signal(SIGINT, SIG_IGN);
				// signal(SIGQUIT, SIG_IGN);
			}
			// write(2,"ccccc_4\n", 9);
		 }
		//  write(2,"bbbbb_4\n", 9);
		 ++i;
		// signal(SIGINT, SIG_IGN);
		// signal(SIGQUIT, SIG_IGN);
	}
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	i2 = 0;
	// write(2, "exe_pp_5\n",10);
	while (i2 < my_pid.count)
	{
		// write(2, "exe_pp_6\n",10);
		if (my_pid.my_pid[i2] == -1)
		{
			// write(2, "exe_pp_7\n",10);
			waitpid(my_pid.pid[i2], &error, 0);
			my_shell->error_status = error;
		}
		else
			my_shell->error_status = my_pid.my_pid[i2];
		// write(2, "exe_pp_8\n",10);
		// printf("my_shell->error_status = %d\n", my_shell->error_status);
		++i2;
	}
	// write(2, "exe_tt_1\n",10);
	free(my_pid.pid);
	// write(2, "exe_tt_2\n",10);
	free(my_pid.my_pid);
	// write(2, "exe_tt_3\n",10);
	my_pid.count = 0;
	my_pid.pid = 0;
	my_pid.my_pid = 0;
	// write(2, "exe_tt_4\n",10);
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	return(my_shell->error_status);
}
