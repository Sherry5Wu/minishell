/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/23 13:39:40 by yzheng           ###   ########.fr       */
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
			ex_error(shellcmd[0],DIRECTORY,126);
		else
			ex_error(shellcmd[0],COMMAND,127);
	}
	message = ft_strjoin(shellcmd[0]," : ");
	if (errno == 13)
		ex_error(message,ERR,126);
	else if (errno == 2)
		ex_error(message,ERR,127);
	ex_error(message,ERR,1);
	free(message);
	if (path)
		free(path);
}
/*
	For example,
	export: the input might be "expor" or "exporta"
*/
int		builtin(char **cmd)
{
	int	size;

	size = ft_strlen(cmd[0]);
	if (size == 2)
	{
		if (!ft_strncmp(cmd[0], "cd",size))
			return(ft_cd(cmd));
	}
	else if (size == 3)
	{
		if (!ft_strncmp(cmd[0], "env",size))
			return(ft_env());
		else if (!ft_strncmp(cmd[0], "pwd",size))
		{
			ft_printf("%s\n",getcwd(NULL,2048));
			return (1);
		}
	}
	else if (size == 4)
	{
		if (!ft_strncmp(cmd[0], "echo",size))
			return(ft_echo(cmd));
		else if (!ft_strncmp(cmd[0], "exit",size))
			ft_exit(cmd);
	}
	else if (size == 5)
	{
		if (!ft_strncmp(cmd[0], "unset",size))
			return(ft_unset(cmd));
	}
	else if (size == 6)
	{
		if (!ft_strncmp(cmd[0], "export",size))
			return(ft_export(cmd));
	}
	return(0);
}

void	real_execute(t_cmd *cm)
{
	char	*path;
	if(!builtin(cm->cmd))
	{
		path = findvalidcmd(cm->cmd);
		if (!path)
			ex_error(cm->cmd[0],COMMAND,127);

		execve(path, cm->cmd, ms()->env);
		ft_execve_failed(cm->cmd, path);
	}
	// printf ("In Real_execute:\n");// for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	// print_env("PWD", 3); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	// print_env("OLDPWD", 6); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	exit(ms()->exit);
}

void exe(t_cmd *cm)
{
	pid_t	pipeid;
	int		prev_fd;

	prev_fd = -1;
	while (cm)
	{
		set_fd(cm);
		if(cm->herenum > 0)
			type_hdoc(cm);
		if (cm->outype == TK_PIPE)
			pipeid = type_outpipe(cm,&prev_fd);
		else if((cm->intype == TK_IN_RE || cm->intype == TK_NONE)
		&& (cm->outype == TK_OUT_RE || cm->outype == TK_NONE))
			pipeid = exe_pipe2(cm);
		else if (cm->intype == TK_PIPE && (cm->outype == TK_OUT_RE
		|| cm->outype == TK_NONE || cm->outype == TK_APPEND))
		{
			pipeid = exe_pipe3(cm);
			close(ms()->fd[0]);
		}

		cm = cm->next;
	}

	close_all(prev_fd);
	while (wait(NULL) > 0);
	signal_default();

	// printf ("In exe:\n");// for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	// print_env("PWD", 3); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	// print_env("OLDPWD", 6); // for testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

}

