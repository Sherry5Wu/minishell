/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/07 11:23:30 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static inline void	ft_execve_failed(char **shellcmd, char *path)
{
	char	*message;

	if (!access(shellcmd[0], F_OK) && !access(shellcmd[0], X_OK))
	{
		if (path)
			free(path);
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
	free(message);
	if (path)
		free(path);
}

static int	builtin(char **cmd)
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
		ft_exit(cmd);
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

static pid_t	exe_heart(int i, t_cmd *cm, int *prev_fd)
{
	pid_t	pipeid;

	pipeid = 0;
	if (i)
	{
		if (cm->herenum > 0)
			pipeid = type_hdoc(cm);
		if (ms()->exit == 130 && ms()->hstatus == 1)
			return (pipeid);
		if (cm->outype == TK_PIPE)
			pipeid = type_outpipe(cm, prev_fd);
		else if ((cm->intype == TK_IN_RE || cm->intype == TK_NONE)
			&& (cm->outype == TK_OUT_RE || cm->outype == TK_NONE
				|| cm->outype == TK_APPEND))
			pipeid = exe_pipe2(cm);
		else if (cm->intype == TK_PIPE && (cm->outype == TK_OUT_RE
				|| cm->outype == TK_NONE || cm->outype == TK_APPEND))
		{
			pipeid = exe_pipe3(cm);
			close(ms()->fd[0]);
		}
	}
	return (pipeid);
}

void	exe(t_cmd *cm)
{
	int		prev_fd;
	int		i;
	int		b;

	prev_fd = -1;
	b = count_cm(cm);
	while (cm)
	{
		i = set_fd(cm);
		if (!cm->cmd)
			break ;
		if (b == 1 && cm->outype == TK_NONE)
			if (ft_strncmp(cm->cmd[0], "echo", 4) && ft_strncmp(cm->cmd[0],
					"pwd", 3) && builtin(cm->cmd))
				break ;
		exe_heart(i, cm, &prev_fd);
		if (ms()->exit == 130 && ms()->hstatus == 1)
			break ;
		cm = cm->next;
	}
	close_all(prev_fd);
	exe_final();
}
