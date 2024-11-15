/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:12:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/15 10:04:51 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static inline void	ft_execve_failed(char **shellcmd, char *path)
{
	char	*message;

	if (!access(shellcmd[0], F_OK) && !access(shellcmd[0], X_OK))
	{
		if (path)
			ft_free_str(path);
		if (ft_strchr(shellcmd[0], '/'))
			ex_error(shellcmd[0], DIRECTORY, 126);
		else
			ex_error(shellcmd[0], COMMAND, 127);
	}
	message = ft_strjoin(shellcmd[0], " : ");
	if (errno == 13)
		ex_error(message, ERR, 126);
	else if (errno == 2)
		ex_error(message, ERR, 127);
	ex_error(message, ERR, 1);
	ft_free_str(message);
	if (path)
		ft_free_str(path);
}

int	builtin(char **cmd)
{
	int	size;

	size = ft_strlen(cmd[0]);
	if (size == 3 && !ft_strncmp(cmd[0], "env", 3))
		return (ft_env());
	else if (size == 2 && !ft_strncmp(cmd[0], "cd", 2))
		return (ft_cd(cmd));
	else if (size == 4 && !ft_strncmp(cmd[0], "echo", 4))
		return (ft_echo(cmd));
	else if (size == 3 && !ft_strncmp(cmd[0], "pwd", 3))
	{
		ft_printf("%s\n", ms()->cwd);
		return (1);
	}
	else if (size == 5 && !ft_strncmp(cmd[0], "unset", 5))
		return (ft_unset(cmd));
	else if (size == 6 && !ft_strncmp(cmd[0], "export", 6))
		return (ft_export(cmd));
	else if (size == 4 && !ft_strncmp(cmd[0], "exit", 4))
		return(ft_exit(cmd));
	return (0);
}

void	real_execute(t_cmd *cm)
{
	char	*path;

	if (!builtin(cm->cmd))
	{
		path = findvalidcmd(cm->cmd);
		if (!path)
			ex_error(cm->cmd[0], COMMAND, 127);
		execve(path, cm->cmd, ms()->env);
		ft_execve_failed(cm->cmd, path);
	}
	exit(ms()->exit);
}
