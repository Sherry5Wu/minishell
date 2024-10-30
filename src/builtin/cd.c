
#include "minishell.h"

char	*get_env(char	*name)
{
	int	i;

	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, ft_strlen(name)))
			i++;
	if(!ms()->env[i])
		return(NULL);
	return(ms()->env[i]);
}
void	update_dir(char *dir, char *name, int size)
{
	t_list	*head;
	int		i;

	head = ms()->env_list;

	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, size))
		i++;
	while(head)
	{
		if (!ft_strnstr(head->content, "OLDPWD", 6))
			break;
		head = head->next;
	}

	ms()->env[i] = ft_strdup(dir);
	head->content = ft_strdup(dir);

}
void	cddir(char	*path)
{
	char	*dir;

	if (!ft_strcmp(path, ""))
		ex_error(" cd: ",HOME, 2);
	dir = ft_strjoin("OLDPWD=",ms()->cwd);
	update_dir(dir, "OLDPWD", 6);
	free(dir);
	chdir(path);
	free(ms()->cwd);
	(
		ms()->cwd) = getcwd(NULL, 2048);
		if (!(ms()->cwd))
		{
			ft_putstr_fd("minishell: cd: error retrieving current directory\n",2);
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
int	checkcd(char	**cmd)
{
	int	i;

	i = 0;
	while(cmd[i])
		i++;
	if(i > 2)
		ex_error(cmd[0], TOOMUCH , 1);
	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], "HOME", 4))
		i++;
	return(i);
}

int	ft_cd(char **cmd)
{
	struct stat	cur_stat;
	int			i;

	i = checkcd(cmd);
	if(!ft_strcmp(cmd[1], "~"))
		cddir(ms()->env[i] + 5);
	else if(!cmd[1])
		cddir(ms()->env[i]);
	else if(cmd[1])
	{
		stat(cmd[1],&cur_stat);
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
	return (1);
}
