#include "minishell.h"

char	*get_env(char	*name)
{
	int	i;

	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, ft_strlen(name)))
		i++;
	if (!ms()->env[i])
		return (NULL);
	return (ms()->env[i]);
}

void	update_dir(char *dir, char *name, int size)
{
	t_list	*head;
	int		i;
	t_env	*env;

	head = ms()->env_list;
	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, size))
		i++;
	while (head)
	{
		env = (t_env *)(head->content);
		if (!ft_strcmp(env->name, name))
			break ;
		head = head->next;
	}
	ms()->env[i] = ft_strdup(dir);
	env->value = ft_strdup(ms()->cwd);
}

void	cddir(char	*path)
{
	char	*dir;

	if (!ft_strcmp(path, ""))
		ex_error(" cd: ", HOME, 2);
	dir = ft_strjoin("OLDPWD=", ms()->cwd);
	update_dir(dir, "OLDPWD", 6);
	free(dir);
	chdir(path);
	free(ms()->cwd);
	(ms()->cwd) = getcwd(NULL, 2048);
	if (!(ms()->cwd))
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory\n", 2);
		ms()->exit = 1;
		dir = get_env("OLDPWD");
		(ms()->cwd) = ft_strjoin(dir, "/..");
		free(dir);
	}
	dir = "PWD=";
	dir = ft_strjoin(dir, ms()->cwd);
	update_dir(dir, "PWD", 3);
	free(dir);
}

void	checkcd(char	**cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		ex_error(cmd[0], TOOMUCH, 1);
}

int	ft_cd(char **cmd)
{
	struct stat	cur_stat;

	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
		cddir(getenv("HOME"));
	else
	{
		stat(cmd[1], &cur_stat);
		if (S_ISDIR(cur_stat.st_mode))
			cddir(cmd[1]);
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ms()->exit = 1;
		}
	}
	printf ("After update the pwd:\n");// for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	print_env("PWD", 3); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	print_env("OLDPWD", 6); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	return (1);
}

