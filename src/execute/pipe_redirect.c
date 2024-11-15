/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:54:18 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/15 10:07:53 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms()->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		ms()->exit = 128 + WTERMSIG(status);
		if (ms()->exit == 139)
			ft_putstr_fd("Segmentation fault (core dumped)\n", 1);
	}
}

pid_t	exe_pipe(t_cmd *cm)
{
	pid_t	pid;

	signal_ignore();
	pid = fork();
	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();
		check_infile(cm);
		dup2(ms()->in_fd, STDIN_FILENO);
		dup2(ms()->fd[1], STDOUT_FILENO);
		close(ms()->fd[0]);
		close(ms()->fd[1]);
		real_execute(cm);
	}
	get_status(pid);
	return (pid);
}

pid_t	exe_pipe2(t_cmd *cm)
{
	pid_t	pid;

	signal_ignore();
	pid = fork();
	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();
		check_infile(cm);
		if (dup2(ms()->out_fd, STDOUT_FILENO) == -1 || dup2(ms()->in_fd,
				STDIN_FILENO) == -1)
		{
			close_inout();
			exit(1);
		}
		close_inout();
		real_execute(cm);
	}
	get_status(pid);
	if (ms()->exit == 130)
		ms()->hstatus = 1;
	return (pid);
}

pid_t	exe_pipe3(t_cmd *cm)
{
	pid_t	pid;

	signal_ignore();
	pid = fork();
	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();
		dup2(ms()->fd[0], STDIN_FILENO);
		if (dup2(ms()->out_fd, STDOUT_FILENO) == -1)
		{
			close(ms()->fd[1]);
			close(ms()->fd[0]);
			exit(1);
		}
		close(ms()->fd[1]);
		close(ms()->fd[0]);
		real_execute(cm);
	}
	get_status(pid);
	return (pid);
}

void	exe_final(void)
{
	signal_ignore();
	signal_default();
}
