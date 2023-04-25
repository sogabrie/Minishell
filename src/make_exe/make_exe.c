#include "minishell.h"
#include "struct.h"
#include <signal.h>

void	sigint_pars_exe(int sig)
{
	write(1, "\n", 1);
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
				return (1);
			}
		}
		if (my_shell->control[(*i) - 1]->command_type == LOGIC_OR)
		{
			if (!my_shell->error_status)
			{
				(*i) = j;
				return (1);
			}
		}
	}
	return (0);
}

int	do_my_exe(t_shell *my_shell, int i)
{
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "echo"))
		return (ft_echo(my_shell->control[i]->exe->options, \
		my_shell->my_envp, my_shell->error_status));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "cd"))
	{
		if (my_shell->control[i]->exe->options)
			return (ft_cd(my_shell->control[i]->exe->options[0] \
			, &my_shell->my_envp, NULL, NULL));
		return (ft_cd(NULL, &my_shell->my_envp, NULL, NULL));
	}
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "export"))
		return (ft_export(my_shell->control[i]->exe->options, \
		&my_shell->my_envp, -1, NULL));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "unset"))
		return (ft_unset(my_shell->control[i]->exe->options, \
		&my_shell->my_envp));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "env"))
		return (ft_env(my_shell->my_envp, 0));
	if (!ft_strcmp(my_shell->control[i]->exe->full_name, "exit"))
		ft_exit(my_shell->control[i]->exe->options, 0);
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

	my_shell->control[i]->exe->cpy_fd_input = dup(my_shell->fd_input);
	dup2(my_shell->control[i]->exe->fd_input, my_shell->fd_input);
	my_shell->control[i]->exe->cpy_fd_output = dup(my_shell->fd_output);
	dup2(my_shell->control[i]->exe->fd_output, my_shell->fd_output);
	new_name = parse_line(my_shell->control[i]->exe->full_name, my_shell->my_envp, my_shell->my_error, 0);
	if (new_name)
	{
		free(my_shell->control[i]->exe->full_name);
		my_shell->control[i]->exe->full_name = new_name;
	}
	if (ft_strcmp(my_shell->control[i]->exe->full_name, "echo"))
	{
		j = 0;
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
			cp_dubl = wildcards(ft_strdup(my_shell->control[i]->exe->options[j]));
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
				free(cp_dubl);
				my_shell->control[i]->exe->options = new_dubl;
			}
			++j;
		}
	}
	if (!control_type_exe(my_shell, i))
	{
		if (chreat_process(my_shell, i))
		{
			write (2, "minishell: ", 12);
			write (2, my_shell->control[i]->exe->options[0], ft_strlen(my_shell->control[i]->exe->options[0]));
			if (my_shell->control[i]->exe->error == 127)
				write (2, ": command not found\n", 21);
			else if (my_shell->control[i]->exe->error == 126)
				write (2, ": No such file or directory\n", 29);
			else
				write (2, ": Permission denied\n", 21);
			my_shell->error_status = 127;
			return ;
		}
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
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (my_shell->control[i]->error == NO_ERROR)
				exit(execve(my_shell->control[i]->exe->full_name, my_shell->control[i]->exe->options, my_shell->my_envp));
			exit(my_shell->control[i]->error);
		}
	}
	else
	{
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
	}
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
		if (my_shell->control[i]->command_type == PRIORITET_START)
		{
			if (chek_and_or(my_shell, &my_pid, &i, my_shell->control[i]->prioritet_start->end + 1))
				continue ;
			if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
			{
				my_shell->cpy_fd_input = dup(my_shell->fd_input);
				dup2(my_shell->control[i - 1]->pip[0], my_shell->fd_input);
			}
			if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
			my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
			{
				my_shell->cpy_fd_output = dup(my_shell->fd_output);
				dup2(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1], my_shell->fd_output);
			}
			add_pid(&my_pid);
			my_pid.pid[my_pid.count - 1] = fork();
			if (my_pid.pid[my_pid.count - 1])
			{
				i2 = i;
				while (i2 < my_shell->control[i]->prioritet_start->end)
				{
					if (my_shell->control[i2]->command_type == PIPE)
					{
						close(my_shell->control[i2]->pip[0]);
						close(my_shell->control[i2]->pip[1]);
					}
					++i2;
				}
				if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
				my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
				{
					close(my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->pip[1]);
				}
				if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
				{
					dup2(my_shell->cpy_fd_input, my_shell->fd_input);
					close(my_shell->cpy_fd_input);
				}
				if (my_shell->control[i]->prioritet_start->end + 1 < my_shell->count && \
				my_shell->control[my_shell->control[i]->prioritet_start->end + 1]->command_type == PIPE)
				{
					dup2(my_shell->cpy_fd_output, my_shell->fd_output);
					close(my_shell->cpy_fd_output);
				}
				i = my_shell->control[i]->prioritet_start->end;
			}
			else
			{
				if (i > 0 && my_shell->control[i - 1]->command_type == PIPE)
				{
					close(my_shell->control[i - 1]->pip[0]);
				}
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
				exit(make_exe(my_shell, i + 1, my_shell->control[i]->prioritet_start->end + 1));
			}
		}
		else if (my_shell->control[i]->command_type == EXE)
		{
			re_co = 0;
			while (re_co < my_shell->control[i]->count_redir && my_shell->control[i]->exe->error == NO_ERROR)
			{
				a = 0;
				if (my_shell->control[i]->redirect[re_co]->error == NO_ERROR)
				{
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
					fd = red_input(a);
					if (fd >= 0)
					{
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
			if (my_shell->control[i]->exe->error == NO_ERROR)
			{
				do_exe(my_shell, &my_pid, i);
				dup2(my_shell->control[i]->exe->cpy_fd_input, my_shell->fd_input);
				close(my_shell->control[i]->exe->cpy_fd_input);
				dup2(my_shell->control[i]->exe->cpy_fd_output, my_shell->fd_output);
				close(my_shell->control[i]->exe->cpy_fd_output);
			}
		}
		++i;
	}
	i2 = 0;
	while (i2 < my_pid.count)
	{
		if (my_pid.my_pid[i2] == -1)
		{
			waitpid(my_pid.pid[i2], &error, 0);
			my_shell->error_status = error;
		}
		else
			my_shell->error_status = my_pid.my_pid[i2];
		++i2;
	}
	free(my_pid.pid);
	free(my_pid.my_pid);
	my_pid.count = 0;
	my_pid.pid = 0;
	my_pid.my_pid = 0;
	return (my_shell->error_status);
}
