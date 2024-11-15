/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/14 11:39:22 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exe_signal_check(int b)
{
	if (ms()->exit == 130 && b > 1)
		printf("\n");
	if (ms()->exit == 130 && b == 1)
		restart(0);
}

static int	exe_heart(int i, t_cmd *cm, int *prev_fd, int b)
{
	if (cm->herenum > 0)
		type_hdoc(cm);
	if (i)
	{
		if (!cm->cmd)
			return (1);
		if (ms()->exit == 130 && ms()->hstatus == 1)
			return (1);
		if (cm->outype == TK_PIPE)
			type_outpipe(cm, prev_fd);
		else if ((cm->intype == TK_IN_RE || cm->intype == TK_NONE)
			&& (cm->outype == TK_OUT_RE || cm->outype == TK_NONE
				|| cm->outype == TK_APPEND))
			exe_pipe2(cm);
		else if (cm->intype == TK_PIPE && (cm->outype == TK_OUT_RE
				|| cm->outype == TK_NONE || cm->outype == TK_APPEND))
		{
			exe_pipe3(cm);
			close(ms()->fd[0]);
		}
		exe_signal_check(b);
	}
	return (1);
}

int	exe_check(t_cmd *cm, int i)
{
	if (i == 1)
	{
		if (ft_strncmp(cm->cmd[0], "echo", 4)
			&& ft_strncmp(cm->cmd[0], "pwd", 3) && builtin(cm->cmd))
			return (1);
	}
	else if (i == 2)
	{
		if (!ft_strncmp(cm->cmd[0], "cat", 3)
			|| !ft_strncmp(cm->cmd[0], "grep", 4))
			return (1);
	}
	else if (i == 3)
	{
		if (cm && !ft_strncmp(cm->cmd[0], "cat", 3) && cm->intype == TK_PIPE)
			return (1);
	}
	return (0);
}

void	exe_loop(int i, int b, int *prev_fd, t_cmd *cm)
{
	t_cmd *temp;
	temp = cm;
	while (temp)
	{
		i = set_fd(temp);
		if (!i && exe_check(cm, 2) && temp->herenum == 0)
		{
			temp = temp->next;
			if (exe_check(temp, 3))
			{
				ms()->exit = 0;
				break ;
			}
			continue ;
		}
		if (!temp->cmd && temp->intype != TK_HDOC)
			break ;
		if (b == 1 && temp->outype == TK_NONE && temp->intype != TK_HDOC)
			if (exe_check(temp, 1))
				break ;
		exe_heart(i, temp, prev_fd, b);
		if ((ms()->exit == 130 && ms()->hstatus == 1))
			break ;
		temp = temp->next;
	}
}

void	exe(t_cmd *cm)
{
	int	prev_fd;
	int	i;
	int	b;

	prev_fd = -1;
	i = 0;
	b = count_cm(cm);
	exe_loop(i, b, &prev_fd, cm);
	close_all(prev_fd);
	exe_final();
}
