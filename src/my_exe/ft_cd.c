#include "minishell.h"

char	**old_new_pwd(char *old_pwd, char *pwd, char **envp, char *dir)
{
	size_t	i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	if (old_pwd == NULL)
		i++;
	new_envp = ft_calloc((i + 1), sizeof(char *));
	if (new_envp == NULL)
		malloc_error();
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PWD=", envp[i], 4))
			new_envp[i] = ft_strjoin("PWD=", dir);
		else if (!ft_strncmp("OLDPWD", envp[i], 6))
			new_envp[i] = ft_strjoin("OLDPWD=", pwd);
		else
			new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
			malloc_error();
	}
	two_dimensional_mas(&envp);
	return (new_envp);
}

int	check_home(char *home, char *new_dir, char *old_pwd, char *pwd)
{
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (-1);
	}
	if (check_dir(home))
	{
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	if (check_access(home, 1) == -1)
	{
		exe_error(home, 13, " cd: ");
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	if (chdir(home) < 0)
	{
		exe_error(home, 2, " cd: ");
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	return (0);
}

int	check_past_dir(char *old_pwd, char *home, char *pwd, char *new_dir)
{
	if (check_dir(old_pwd))
	{
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	if (check_access(old_pwd, 1) == -1)
	{
		exe_error(old_pwd, 13, " cd: ");
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	if (old_pwd == NULL)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	if (chdir(old_pwd) < 0)
	{
		exe_error(old_pwd, 2, " cd: ");
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	return (0);
}

int	check_new_dir(char *home, char *dir, char *old_pwd, char *pwd)
{
	char	*new_dir;

	new_dir = valid_dir(dir, home);
	if (check_dir(new_dir))
	{
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	if (check_access(new_dir, 1) == -1)
	{
		exe_error(new_dir, 13, " cd: ");
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	if (chdir(new_dir) < 0)
	{
		exe_error(dir, 2, " cd: ");
		free_object_cd(new_dir, home, old_pwd, pwd);
		return (-1);
	}
	free(new_dir);
	return (0);
}

int	ft_cd(char *dir, char ***envp, char *new_dir, char *pwd)
{
	char	*home;
	char	*old_pwd;
	char	buf[256];

	adding_dir(&old_pwd, &home, &pwd, envp);
	if (ft_strlen(dir) == 0)
	{
		if (check_home(home, new_dir, old_pwd, pwd) == -1)
			return (-1);
		*envp = old_new_pwd(old_pwd, pwd, *envp, home);
	}
	else if (!ft_strcmp("-", dir))
	{
		if (check_past_dir(old_pwd, home, pwd, new_dir) == -1)
			return (-1);
		ft_putendl_fd(old_pwd, 1);
		*envp = old_new_pwd(old_pwd, pwd, *envp, old_pwd);
	}
	else
	{
		if (check_new_dir(home, dir, old_pwd, pwd) == -1)
			return (-1);
		*envp = old_new_pwd(old_pwd, pwd, *envp, getcwd(buf, sizeof(buf)));
	}
	return (free_object_cd(new_dir, home, old_pwd, pwd));
}
